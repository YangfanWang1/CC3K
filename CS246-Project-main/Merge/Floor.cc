#include "Floor.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "BA.h"
#include "BD.h"
#include "Barrier.h"
#include "Cell.h"
#include "Chamber.h"
#include "Dragon.h"
#include "Dragon_horde.h"
#include "Entity.h"
#include "Goblin.h"
#include "Merchant.h"
#include "Merchant_horde.h"
#include "Normal_horde.h"
#include "PH.h"
#include "Phoenix.h"
#include "RH.h"
#include "Small_horde.h"
#include "Troll.h"
#include "Vampire.h"
#include "WA.h"
#include "WD.h"
#include "Werewolf.h"
using namespace std;

Floor::Floor() : stairsCell{nullptr} {}

vector<shared_ptr<Chamber>> Floor::getChambers() const {
    return chambers;
}

vector<shared_ptr<Cell>> Floor::getCells() const {
    return cells;
}

Cell *Floor::getStairs() const {
    return stairsCell;
}

void Floor::setStairs(Cell *newStairs) {
    stairsCell = newStairs;
}

Cell *Floor::generate(int floorNum, string filename) {
    std::vector<std::shared_ptr<Cell>> tempCells;
    Cell *playerLoc = nullptr;
    char inp = ' ';
    ifstream layout{filename};
    // Discard any input from previous floors and get to current floor.
    for (int i = 0; i < floorNum; ++i) {
        for (int j = 0; j < board_height; ++j) {
            for (int k = 0; k < board_width + 1; ++k) {
                inp = layout.get();
            }
        }
    }
    // Read in input from given file and add Cells accordingly.
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            inp = layout.get();
            int cellType = OPEN;                                 // By default, Cells are OPEN (A regular cell).
            bool occupied = true;                                // Check if Entity exists on Cell.
            for (int k = 0; k < (int)cellDisplay.size(); ++k) {  // Check input Cell type.
                if (inp == cellDisplay[k]) {
                    cellType = k;
                    occupied = false;
                }
            }
            tempCells.emplace_back(make_shared<Cell>(j, i, cellType));
            Cell *currentCell = tempCells[i * board_width + j].get();
            // If the current cell is the stairs cell, save it to the stairsCell field.
            if (cellType == STAIRS) {
                stairsCell = currentCell;
            }
            // If there is an Entity on the tile, generate and bind it.
            if (occupied) {
                if (inp == '@') {
                    playerLoc = currentCell;
                    // Don't do anything else for player. Race is picked and player is created
                    //   in Interpreter.init(), we just retrieve the Cell location for now.
                } else if (inp == 'V') {
                    currentCell->setEntity(make_shared<Vampire>(false, currentCell));

                } else if (inp == 'W') {
                    currentCell->setEntity(make_shared<Werewolf>(false, currentCell));
                } else if (inp == 'N') {
                    currentCell->setEntity(make_shared<Goblin>(false, currentCell));
                } else if (inp == 'M') {
                    currentCell->setEntity(make_shared<Merchant>(false, currentCell));
                } else if (inp == 'D') {
                    currentCell->setEntity(make_shared<Dragon>(false, currentCell));
                } else if (inp == 'X') {
                    currentCell->setEntity(make_shared<Phoenix>(false, currentCell));
                } else if (inp == 'T') {
                    currentCell->setEntity(make_shared<Troll>(false, currentCell));
                } else if (inp == '0') {
                    currentCell->setEntity(make_shared<RH>(false, currentCell));
                } else if (inp == '1') {
                    currentCell->setEntity(make_shared<BA>(false, currentCell));
                } else if (inp == '2') {
                    currentCell->setEntity(make_shared<BD>(false, currentCell));
                } else if (inp == '3') {
                    currentCell->setEntity(make_shared<PH>(false, currentCell));
                } else if (inp == '4') {
                    currentCell->setEntity(make_shared<WA>(false, currentCell));
                } else if (inp == '5') {
                    currentCell->setEntity(make_shared<WD>(false, currentCell));
                } else if (inp == '6') {
                    currentCell->setEntity(make_shared<Normal>(false, currentCell));
                } else if (inp == '7') {
                    currentCell->setEntity(make_shared<Small>(false, currentCell));
                } else if (inp == '8') {
                    currentCell->setEntity(make_shared<Merchant_horde>(false, currentCell));
                } else if (inp == '9') {
                    currentCell->setEntity(make_shared<Dragon_horde>(false, currentCell));
                    // Constructor for dragon_horde checks for any dragons nearby to set as protector.
                } else if (inp == 'B') {
                    currentCell->setEntity(make_shared<Barrier>(currentCell));
                }
            }
        }
        // To skip the newline.
        inp = layout.get();
    }
    cells = tempCells;
    // For each cell, construct list of all cells in block and attach it to Cell.
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            std::vector<Cell *> newBlock{};
            for (int k = i - 1; k < i + 2; ++k) {
                for (int l = j - 1; l < j + 2; ++l) {
                    // If neighbouring cell is in bounds, add as a neighbour.
                    if (!(i == k && j == l) && k >= 0 && k < board_height && l >= 0 && l < board_width) {
                        newBlock.emplace_back(cells[k * board_width + l].get());
                    }
                }
            }
            cells[i * board_width + j]->setBlock(newBlock);
        }
    }
    // Create list of chambers and link cells.
    std::vector<std::shared_ptr<Chamber>> tempChambers;
    vector<Cell *> allCells;
    for (int i = 0; i < board_height * board_width; ++i) {
        Cell *c = cells.at(i).get();
        bool counted = false;
        if (c->getType() != OPEN && c->getType() != STAIRS) {
            continue;
        }
        for (int j = 0; j < (int)tempChambers.size(); ++j) {
            for (int k = 0; k < (int)tempChambers.at(j)->getCells().size(); ++k) {
                if (c == tempChambers.at(j)->getCells().at(k)) {
                    counted = true;
                }
            }
        }
        if (!counted) {
            cout << "Detected a new chamber." << endl;
            tempChambers.emplace_back(make_shared<Chamber>(tempChambers.size()));
            vector<Cell *> tempChamberCells;
            c->generateChamber(&tempChamberCells, &allCells);  // Recursively figures out all cells in the chamber.
            tempChambers.at(tempChambers.size() - 1)->setCells(tempChamberCells);
        }
    }
    chambers = tempChambers;
    // Lastly, just return the Player Cell we found prior (if one exists).
    return playerLoc;
}

Cell *Floor::get_available_cell(int chamber_num, int seed) {
    Cell *location;
    while (true) {
        seed++;
        srand(seed);
        std::vector<Cell *> Cham_cells = chambers.at(chamber_num)->getCells();
        Cell *available_cell = Cham_cells.at(rand() % (Cham_cells.size() - 1));
        if ((available_cell->getType() == OPEN) && (available_cell->getEntity() == nullptr)) {
            location = available_cell;
            break;
        } else {
            seed++;
            continue;
        }
    }
    return location;
}

void Floor::populate(int seed) {
    Cell *location = nullptr;
    // generation of potion
    for (int i = 0; i < 10; i++) {
        seed++;
        srand(seed);

        int check = 0 + rand() % 6;
        // generation of chamber number
        int chamber_num = 0 + rand() % getChambers().size();
        seed++;
        location = get_available_cell(chamber_num, seed);
        // generation of Potions
        if (check == 0) {
            location->setEntity(make_shared<BA>(false, location));
        } else if (check == 1) {
            location->setEntity(make_shared<RH>(false, location));

        } else if (check == 2) {
            location->setEntity(make_shared<BD>(false, location));
        } else if (check >= 7 && check <= 11) {
            location->setEntity(make_shared<PH>(false, location));
        } else if (check >= 12 && check <= 13) {
            location->setEntity(make_shared<WA>(false, location));
        } else {
            location->setEntity(make_shared<WD>(false, location));
        }
    }
    // generation of Gold
    for (int i = 0; i < 10; i++) {
        seed++;
        srand(seed);

        int check = 0 + rand() % 8;

        // generation of chamber number
        int chamber_num = 0 + rand() % getChambers().size();
        seed++;
        location = get_available_cell(chamber_num, seed);
        // generation of Gold
        if (check >= 0 && check <= 4) {
            location->setEntity(make_shared<Normal>(false, location));
        } else if (check == 5) {
            location->setEntity(make_shared<Dragon_horde>(false, location));

            Cell *dragon_loc = nullptr;
            while (true) {
                int pos = rand() % location->getWalkableBlock().size();
                if ((location->getWalkableBlock().at(pos)->getType() == OPEN) && (location->getWalkableBlock().at(pos)->getEntity() == nullptr)) {
                    dragon_loc = location->getWalkableBlock().at(pos);
                    break;
                } else {
                    continue;
                }
            }
            dragon_loc->setEntity(make_shared<Dragon>(false, dragon_loc));
        }
        else if (check >= 6 && check <= 7) {
            location->setEntity(make_shared<Small>(false, location));
        }
    }

    // generations of enemy(total number of 20)
    for (int i = 0; i < 20; i++) {
        seed++;
        srand(seed);
        // generation of enemy type
        int check = 0 + rand() % 18;
        // compass add
        seed++;
        srand(seed);
        int compass_det = 0 + rand() % 18;
        // generation of chamber number
        int chamber_num = 0 + rand() % getChambers().size();
        seed++;
        location = get_available_cell(chamber_num, seed);
        // Enemy generation
        if (check >= 0 && check <= 3) {
            location->setEntity(make_shared<Werewolf>(false, location));
        } else if (check >= 4 && check <= 6) {
            location->setEntity(make_shared<Vampire>(false, location));
        } else if (check >= 7 && check <= 11) {
            location->setEntity(make_shared<Goblin>(false, location));
        } else if (check >= 12 && check <= 13) {
            location->setEntity(make_shared<Troll>(false, location));
        } else if (check >= 14 && check <= 15) {
            location->setEntity(make_shared<Phoenix>(false, location));
        } else {
            location->setEntity(make_shared<Merchant>(false, location));
        }
    }
}

void Floor::addProtectors() {
    // For each Entity, apply any protector relations if they exist.
    for (int i = 0; i < board_height * board_width; ++i) {
        Entity *ent = cells[i]->getEntity().get();
        if (ent) {
            ent->checkForProtectors();
        }
    }
}

string Floor::update() {
    string update_result = string();
    vector<Entity *> updatedList;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            Entity *ent = cells[i * board_width + j]->getEntity().get();
            bool already_updated = false;
            for (int k = 0; k < (int)updatedList.size(); ++k) {
                if (ent == updatedList.at(k)) {
                    already_updated = true;
                }
            }
            if (ent && !already_updated) {
                update_result += ent->update();
                updatedList.emplace_back(ent);
            }
        }
    }
    return update_result;
}

Floor::~Floor() {}

ostream &operator<<(ostream &out, const Floor &f) {
    // Display each cell in the floor one-by one.
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            out << *(f.cells[i * board_width + j]);
        }
        out << endl;
    }
    return out;
}

void Floor::set_compass(Cell *cell) {
    std::shared_ptr<Enemy> myenemy = dynamic_pointer_cast<Enemy>(cell->getEntity());
    myenemy->setStair(getStairs());
}
