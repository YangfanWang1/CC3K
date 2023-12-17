#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Chamber.h"
#include "Cell.h"
#include "Entity.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Goblin.h"
#include "Merchant.h"
#include "Dragon.h"
#include "Phoenix.h"
#include "Troll.h"
#include "RH.h"
#include "BA.h"
#include "BD.h"
#include "PH.h"
#include "WA.h"
#include "WD.h"
#include "Normal_horde.h"
#include "Small_horde.h"
#include "Merchant_horde.h"
#include "Dragon_horde.h"
#include "Floor.h"
using namespace std;

Floor::Floor() : stairsCell{nullptr} {}

vector<shared_ptr<Chamber>> Floor::getChambers() const {
    return chambers;
}

vector<shared_ptr<Cell>> Floor::getCells() const {
    return cells;
}

std::shared_ptr<Cell> Floor::getStairs() const {
    return stairsCell;
}

void Floor::setStairs(std::shared_ptr<Cell> newStairs) {
    stairsCell = newStairs;
}

Cell * Floor::generate(int floorNum, string filename) {
    std::vector<std::shared_ptr<Cell>> tempCells;
    Cell *playerLoc = nullptr;
    char inp = ' ';
    ifstream layout {filename};
    // Discard any input from previous floors and get to current floor.
    for (int i = 0; i < board_height * board_width * floorNum; ++i) {
        layout >> inp;
    }
    // Read in input from given file and add Cells accordingly.
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            layout >> inp;
            int cellType = OPEN;                           // By default, Cells are OPEN (A regular cell).
            bool occupied = true;                          // Check if Entity exists on Cell.
            for (int k = 0; k < cellDisplay.size(); ++k) { // Check input Cell type.
                if (inp == cellDisplay[k]) {
                    cellType = k;
                    occupied = false;
                }
            }
            tempCells.emplace_back(make_shared<Cell>(j, i, cellType));
            shared_ptr<Cell> currentCell = tempCells[i * board_width + j];
            // If the current cell is the stairs cell, save it to the stairsCell field.
            if (cellType == STAIRS) {
                stairsCell = currentCell;
            }
            // If there is an Entity on the tile, generate and bind it.
            if (occupied) {
                if (inp == '@') {
                    playerLoc = currentCell.get();
                    // Don't do anything else for player. Race is picked and player is created
                    //   in Interpreter.init(), we just retrieve the Cell location for now.
                } else if (inp == 'V') {
                    currentCell->setEntity(make_shared<Vampire>(false, currentCell.get()));
                } else if (inp == 'W') {
                    currentCell->setEntity(make_shared<Werewolf>(false, currentCell.get()));
                } else if (inp == 'N') {
                    currentCell->setEntity(make_shared<Goblin>(false, currentCell.get()));
                } else if (inp == 'M') {
                    currentCell->setEntity(make_shared<Merchant>(false, currentCell.get()));
                } else if (inp == 'D') {
                    currentCell->setEntity(make_shared<Dragon>(false, currentCell.get()));
                } else if (inp == 'X') {
                    currentCell->setEntity(make_shared<Phoenix>(false, currentCell.get()));
                } else if (inp == 'T') {
                    currentCell->setEntity(make_shared<Troll>(false, currentCell.get()));
                } else if (inp == '0') {
                    currentCell->setEntity(make_shared<RH>());
                } else if (inp == '1') {
                    currentCell->setEntity(make_shared<BA>());
                } else if (inp == '2') {
                    currentCell->setEntity(make_shared<BD>());
                } else if (inp == '3') {
                    currentCell->setEntity(make_shared<PH>());
                } else if (inp == '4') {
                    currentCell->setEntity(make_shared<WA>());
                } else if (inp == '5') {
                    currentCell->setEntity(make_shared<WD>());
                } else if (inp == '6') {
                    currentCell->setEntity(make_shared<Normal>(nullptr, false, currentCell.get()));
                } else if (inp == '7') {
                    currentCell->setEntity(make_shared<Small>(nullptr, false, currentCell.get()));
                } else if (inp == '8') {
                    currentCell->setEntity(make_shared<Merchant_horde>(nullptr, false, currentCell.get()));
                } else if (inp == '9') {
                    currentCell->setEntity(make_shared<Dragon_horde>(nullptr, false, currentCell.get()));
                    // Constructor for dragon_horde checks for any dragons nearby to set as protector.
                }
            }
        }
    }
    cells = tempCells;
    // For each cell, construct list of all cells in block and attach it to Cell.
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            std::vector<Cell *> newBlock{};
            for (int k = i - 1; k < i + 2; ++k) {
                for (int l = j - 1; l < j + 2; ++l) {
                    // If neighbouring cell is in bounds, add as a neighbour.
                    if (!(i == k && j == l) && k >= 0 && k < board_height && l >= 0 && l < board_width && 
                        cells[k * board_width + l]->getType() != SOLID && 
                        cells[k * board_width + l]->getType() != H_WALL && 
                        cells[k * board_width + l]->getType() != V_WALL) {
                        newBlock.emplace_back(cells[k * board_width + l].get());
                    }
                }
            }
            cells[i * board_width + j]->setBlock(newBlock);
        }
    }
    // Create list of chambers and link cells.
    std::vector<std::shared_ptr<Chamber>> tempChambers;
    for (int i = 0; i < board_height * board_width; ++i) {
        Cell *c = cells.at(i).get();
        bool counted = false;
        if (c->getType() != OPEN || c->getType() != STAIRS) {
            continue;
        }
        for (int j = 0; j < tempChambers.size(); ++j) {
            for (int k = 0; k < tempChambers.at(j)->getCells().size(); ++k) {
                if (c == tempChambers.at(j)->getCells().at(k).get()) {
                    counted = true;
                }
            }
        }
        if (!counted) {
            tempChambers.emplace_back(make_shared<Chamber>(tempChambers.size()));
            vector<shared_ptr<Cell>> tempChamberCells;
            

            c->generateChamber(&tempChamberCells);  // Recursively figures out all cells in the chamber.
            tempChambers.at(tempChambers.size() - 1)->setCells(tempChamberCells);
        }
    }
    chambers = tempChambers;
    // Lastly, just return the Player Cell we found prior (if one exists).
    return playerLoc;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INCOMPLETE
void Floor::populate(int seed) {
    //generations of enemy(total number of 20)
    for(int i =0; i < 20 ; i++){
        srand(seed);
        int check = 0+rand()%17;
        seed++;
        //get available position;
        Cell* location=nullptr;
        //79 col, 25 row
        int x;
        int y;
        while(true){
            //not generation of enemy, so not using default seed
            std::default_random_engine rng{seed};
            srand(rng);
            y = 0+rand()%24;
            srand(rng);
            x = 0 + rand()%78;
            //if pos is available 
            if(cells.at(y*board_width+x).getType()==1){
                break;
            }
            else{
                continue;
        }
        }
        //werewolf 4/18
        if(0<=check<=3){
            cells.at(y*board_width+x).setEntity(make_shared<Werewolf>(false,currentCell.get()));
        //Vampire 3/18
        }else if(4<=check<=6){
            cells.at(y*board_width+x).setEntity(make_shared<Vampire>(false,currentCell.get()));
        }else if(7<=check<=11){
            cells.at(y*board_width+x).setEntity(make_shared<Goblin>(false,currentCell.get()));
        }else if(12<=check<=13){
            cells.at(y*board_width+x).setEntity(make_shared<Troll>(false,currentCell.get()));
        }else if(14<=check<=15){
            cells.at(y*board_width+x).setEntity(make_shared<Phoenix>(false,currentCell.get()));
        }else{
            cells.at(y*board_width+x).setEntity(make_shared<Merchant>(false,currentCell.get()));
        }
    }


            void Floor::update() {
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {:wq

            Entity *ent = cells[i * board_width + j]->getEntity().get();
            if (ent) {
                ent->update();
            }
        }
    }
}

Floor::~Floor() {}

ostream &operator<<(ostream &out, const Floor &f) {
    // Display each cell in the floor one-by one.
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            out << f.cells[i * board_width + j];
        }
        out << endl;
    }
    return out;
}
