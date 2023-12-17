#include "Interpreter.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "BA.h"
#include "BD.h"
#include "Barrier.h"
#include "Cell.h"
#include "Chamber.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Floor.h"
#include "Human.h"
#include "Item.h"
#include "Merchant.h"
#include "Orc.h"
#include "PH.h"
#include "Player.h"
#include "Potion.h"
#include "RH.h"
#include "Vampire.h"
#include "WA.h"
#include "WD.h"
using namespace std;

bool Interpreter::barrier_noinput = false;
Interpreter::Interpreter(std::string filename, int seed) : filename{filename}, floorNum{0}, player{nullptr}, seed{seed} {
    level = make_unique<Floor>();
    dlc_enabled = false;
}

void Interpreter::init() {
    // Ask user if they want to enable DLC.
    if (floorNum == 0) {
        cout << "Would you like to enable DLC features? (y - Yes, n = No)" << endl;
        string inp = string();
        cin >> inp;
        while (inp != "y" && inp != "n") {
            cout << "Invalid option selected." << endl;
            cin >> inp;
        }
        if (inp == "y") {
            dlc_enabled = true;
        } else {
            dlc_enabled = false;
        }
    }

    Cell *PC = nullptr;
    Cell *location = nullptr;
    int chamber_num = 0;
    cout << "Generating floor..." << endl;

    if (filename.length() != 0) {
        PC = level->generate(floorNum, filename);

    } else {
        PC = level->generate(floorNum);
    }
    Cell *stair = level->getStairs();
    // If Floor layout is not pre-populated, generate player & stairs location and populate.
    if (PC == nullptr) {
        seed++;
        srand(seed);
        // Randomly generate PC location.
        chamber_num = 0 + rand() % level->getChambers().size();
        location = level->get_available_cell(chamber_num, seed);
        PC = location;
        int player_chamber = chamber_num;
        // Randomly generate Stairs cell.
        while (chamber_num == player_chamber) {
            // Keep randomly generating chamber_num until we get a different chamber.
            seed++;
            srand(seed);
            chamber_num = 0 + rand() % level->getChambers().size();
        }
        location = level->get_available_cell(chamber_num, seed);
        location->setType(STAIRS);
        stair = location;
        //std::cout << "Stair: " << stair->getX() << " " << stair->getY() << std::endl;
        level->setStairs(location);
        // Generates potions, gold, and enemies.
        seed++;
        level->populate(seed);
    }
    // If floorNum is 0 (We are starting a new game), get Player race.
    if (floorNum == 0) {
        std::cout << "Enter your race (h - Human, e - Elf, d - Dwarf, o - Orc): " << std::endl;
        string inp = string();
        cin >> inp;
        while (inp != "h" && inp != "e" && inp != "d" && inp != "o") {
            cout << "Invalid race selected." << endl;
            cin >> inp;
        }
        if (inp == "h") {
            player = make_shared<Human>(false, PC);
        } else if (inp == "e") {
            player = make_shared<Elf>(false, PC);
        } else if (inp == "d") {
            player = make_shared<Dwarf>(false, PC);
        } else if (inp == "o") {
            player = make_shared<Orc>(false, PC);
        }
    }
    // Bind player to new cell.
    PC->setEntity(player);
    player->setCurrentCell(PC);
    //std::cout << "Player: " << PC->getX() << " " << PC->getY() << std::endl;

    Cell *barrier_loc = nullptr;
    // generation of barrier
    srand(b_seed);
    int barrier_floor = rand() % 5;
    //std::cout << "Barrier floor: " << barrier_floor;
    while (true) {
        if ((Interpreter::barrier_noinput == true) || (barrier_floor != floorNum)) {
            break;
        }
        seed++;
        srand(seed);
        int b_chamber = rand() % level->getChambers().size();
        for (int i = 0; i < level->getChambers().at(b_chamber)->getCells().size(); i++) {
            if (level->getChambers().at(b_chamber)->getCells().at(i)->getEntity() != nullptr) {
                if (level->getChambers().at(b_chamber)->getCells().at(i)->getEntity()->getType() == "Dragon") {
                    int pos = rand() % level->getChambers().at(b_chamber)->getCells().at(i)->getWalkableBlock().size();

                    if ((level->getChambers().at(b_chamber)->getCells().at(i)->getWalkableBlock().at(pos)->getType() == OPEN) && 
                        (level->getChambers().at(b_chamber)->getCells().at(i)->getWalkableBlock().at(pos)->getEntity() == nullptr)) {
                        barrier_loc = level->getChambers().at(b_chamber)->getCells().at(i)->getWalkableBlock().at(pos);
                        Interpreter::barrier_noinput = true;
                        //std::cout << "Barrier: " << barrier_loc << std::endl;
                        barrier_loc->setEntity(make_shared<Barrier>(barrier_loc));
                        break;
                    }
                }
            }
        }
    }

    // generation of compass at each floor
    std::string enemies[7] = {"Vampire", "Werewolf", "Troll", "Goblin", "Merchant", "Dragon", "Phoenix"};
    string *enemy_check;
    int compass_check = 0;
    while (compass_check == 0) {
        seed++;
        srand(seed);
        int rand_chamber = rand() % level->getChambers().size();
        for (int j = 0; j < level->getChambers().at(rand_chamber)->getCells().size(); j++) {
            if (compass_check == 1) {
                break;
            }
            if (level->getChambers().at(rand_chamber)->getCells().at(j)->getEntity() != nullptr) {
                enemy_check = std::find(enemies, enemies + 7, level->getChambers().at(rand_chamber)->getCells().at(j)->getEntity()->getType());
                //cout << "Stair ptr4: " << level->getChambers().at(rand_chamber)->getCells().at(j)->getEntity()->getType() << endl;

                if (enemy_check != enemies + 7) {
                    //std::cout << "Enemy attached here: " << level->getChambers().at(rand_chamber)->getCells().at(j)->getEntity()->getType() << std::endl;
                    level->set_compass(level->getChambers().at(rand_chamber)->getCells().at(j));
                    //std::cout << "compass here: " << level->getChambers().at(rand_chamber)->getCells().at(j)->getX() << " " << level->getChambers().at(rand_chamber)->getCells().at(j)->getY();
                    compass_check = 1;
                }
            }
        }
    }
    seed++;
    srand(seed);
    chamber_num = 0 + rand() % level->getChambers().size();

    level->addProtectors();
    // If new game, display board and a message indicating player spawn.
    // If not a new game, display board and message indicating you are on the next floor.
    if (floorNum == 0) {
        display("Player character has spawned.");
    } else {
        display("Moved to the next floor.");
    }
}

void Interpreter::command(string cmd) {
    // This method calls other Interpreter methods.
    // When action is completed, also calls display() and then outputs what just occured due to the current command.

    // If game is over (HP = 0 or floorNum >= 5), output message prompting restart.
    if (cmd != "r" && (player->getHP() <= 0 || floorNum >= 5)) {
        cout << "GAME OVER: ";
        if (player->getHP() <= 0) {
            cout << "Your player died!" << endl;
        } else if (floorNum >= 5) {
            cout << "You beat the game!" << endl;
        }
        cout << "FINAL SCORE: " << player->getScore() << endl;
        cout << "Please input r to restart the game, or q to quit." << endl;
        return;
    }

    ostringstream action;
    string direction = string();
    Cell *target = nullptr;
    shared_ptr<Entity> ent = nullptr;
    if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" ||
        cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
        // MOVE COMMAND:
        target = getCellInDir(cmd);
        // Check if target cell is a valid cell.
        if (target && target->getType() != SOLID &&
            target->getType() != H_WALL && target->getType() != V_WALL) {
            ent = target->getEntity();
            if (ent == nullptr) {
                // If nothing is on the cell, move there.
                movePlayer(target);
                action << "PC moves " << directionName(cmd);
            } else if ((ent->getType() == "Normal" || ent->getType() == "Small" ||
                        ent->getType() == "Merchant_horde" || ent->getType() == "Dragon_horde") &&
                       ent->getProtector() == nullptr) {
                // If Treasure items are on the cell, acquire and move there.
                shared_ptr<Treasure> treasure = dynamic_pointer_cast<Treasure>(ent);
                player->addGold(treasure->getValue());
                treasure->kill();
                movePlayer(target);
                action << "PC moves " << directionName(cmd) << " and acquires " << treasure->getValue() << " gold";
            } else if ((ent->getType() == "Compass" || ent->getType() == "Barrier") && ent->getProtector() == nullptr) {
                // If Major items are on the cell, acquire and move there.
                shared_ptr<Item> item = dynamic_pointer_cast<Item>(ent);
                item->acquire(player.get());
                movePlayer(target);
                action << "PC moves " << directionName(cmd) << " and acquires the " << item->getType();
            } else {
                action << "PC is unable to move " << directionName(cmd) << " (the cell is currently occupied)";
            }
            // Output special message if player encounters a Potion in that direction.
            target = getCellInDir(cmd);
            if (target && target->getEntity().get() &&
                (target->getEntity()->getType() == "BA" || target->getEntity()->getType() == "WA" ||
                 target->getEntity()->getType() == "BD" || target->getEntity()->getType() == "WD" ||
                 target->getEntity()->getType() == "RH" || target->getEntity()->getType() == "PH")) {
                action << " and sees ";
                shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(target->getEntity());
                if (potion->get_used()) {
                    action << "a known potion (" << potion->getType() << "). ";
                } else {
                    action << "an unknown potion. ";
                }
            } else {
                action << ". ";
            }
            // Move to next floor if we are on the stairs, and stop any further updates.
            if (player->getCurrentCell() == level->getStairs()) {
                nextFloor();
                return;
            }
        } else {
            action << "Unable to move " << directionName(cmd) << " (the cell is a wall or out-of-bounds). ";
        }

    } else if (cmd == "u") {
        // USE POTION COMMAND:
        cin >> direction;
        target = getCellInDir(direction);
        if (target && target->getEntity().get() &&
            (target->getEntity()->getType() == "BA" || target->getEntity()->getType() == "WA" ||
             target->getEntity()->getType() == "BD" || target->getEntity()->getType() == "WD" ||
             target->getEntity()->getType() == "RH" || target->getEntity()->getType() == "PH")) {
            shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(target->getEntity());
            usePotion(potion.get());
            action << "PC uses " << potion->getType() << ". ";
        } else {
            action << "No potion exists in the " << directionName(direction) << " direction. ";
        }

    } else if (cmd == "a") {
        // ATTACK ENEMY COMMAND:
        cin >> direction;
        target = getCellInDir(direction);
        if (target && target->getEntity().get()) {
            ent = target->getEntity();
            if (ent->getType() == "Vampire" || ent->getType() == "Werewolf" ||
                ent->getType() == "Goblin" || ent->getType() == "Merchant" ||
                ent->getType() == "Dragon" || ent->getType() == "Phoenix" ||
                ent->getType() == "Troll") {
                bool merchantHostility = false;
                if (ent->getType() == "Merchant" && !Merchant::get_hostile()) {
                    merchantHostility = true;
                }

                shared_ptr<Enemy> enemy = dynamic_pointer_cast<Enemy>(target->getEntity());
                int prevHP = enemy->getHP();
                player->attackEnemy(enemy.get());
                action << "PC deals " << prevHP - enemy->getHP() << " damage to " << enemy->display_char() << " (" << enemy->getHP() << " HP)";
                if (enemy->getHP() <= 0) {
                    action << ", killing them. ";
                } else {
                    action << ". ";
                }
                if (merchantHostility) {
                    action << "All Merchants (M) are now hostile. ";
                }
            } else if (dlc_enabled && ent->getType() != "Compass" && ent->getType() != "Barrier") {  // DLC ADDITIONAL CONTENT ---------------
                ent->kill();
                action << "PC recklessly attacks " << ent->display_char() << ", destroying it. ";
            } else {
                action << "Nothing destroyable in the " << directionName(direction) << " direction. ";
            }
        } else if (dlc_enabled && target &&
                   (target->getType() == H_WALL || target->getType() == V_WALL || target->getType() == SOLID)) {
            if (target->getX() == 0 || target->getY() == 0 ||
                target->getX() == board_width - 1 || target->getY() == board_height - 1) {
                action << "Map boundaries cannot be destroyed. ";
            } else if (target->getType() == H_WALL || target->getType() == V_WALL) {
                target->setType(DOORWAY);
                action << "PC attacks a solid wall, breaking it down. ";
            } else if (target->getType() == SOLID) {
                target->setType(PASSAGE);
                action << "PC attacks a solid wall, breaking it down. ";
            }
            seed++;
            srand(seed);
            int gold_drop = rand() % 5;
            if (gold_drop == 1) {
                player->addGold(1);
                action << "PC dug up 1 gold in the wall! ";
            }  // ------------------------------------------------------------------------------------------------------------------------------
        } else {
            action << "Nothing to attack in the " << directionName(direction) << " direction. ";
        }

    } else if (cmd == "r") {
        // RESET GAME COMMAND:
        floorNum = 0;
        player = nullptr;
        Interpreter::barrier_noinput = false;
        level = make_unique<Floor>();
        // Reset all static variables.
        BA::reset_used();
        WA::reset_used();
        BD::reset_used();
        WD::reset_used();
        RH::reset_used();
        PH::reset_used();
        Merchant::set_hostile(false);
        // Re-call init().
        init();
        return;
    }

    // Tells the entire floor to update itself.
    string update_result = update();
    // Lastly, displays the current game board.
    display(action.str() + update_result);
    // If the player is dead, quickly recall command() to skip prompting input.
    if (player->getHP() <= 0) {
        command(" ");
    }
}

string Interpreter::update() {
    string update_result = level->update();
    return update_result;
}

void Interpreter::display(string action) {
    cout << *(level);
    cout << "Race: " << player->getType();
    cout << " Gold: " << player->getGold();
    cout << setw(board_width - 22) << right << "Floor " << floorNum + 1;
    cout << endl;
    cout << left << "HP: " << player->getHP() << endl;
    cout << left << "Atk: " << player->getATK() << endl;
    cout << left << "Def: " << player->getDEF() << endl;
    // cout << "Player: " << player->getCurrentCell()->getX() << " " << player->getCurrentCell()->getY() << std::endl;
    // cout << "Stairs: " << level->getStairs()->getX() << " " << level->getStairs()->getY() << endl;
    cout << "Action: " << action << endl;
}

Cell *Interpreter::getCellInDir(std::string direction) {
    int targetX = player->getCurrentCell()->getX();
    int targetY = player->getCurrentCell()->getY();
    if (direction == "no" || direction == "ne" || direction == "nw") {
        --targetY;
    } else if (direction == "so" || direction == "se" || direction == "sw") {
        ++targetY;
    }
    if (direction == "ea" || direction == "ne" || direction == "se") {
        ++targetX;
    } else if (direction == "we" || direction == "nw" || direction == "sw") {
        --targetX;
    }
    Cell *target = nullptr;
    std::vector<Cell *> playerBlock = player->getCurrentCell()->getBlock();
    for (int i = 0; i < playerBlock.size(); ++i) {
        if (playerBlock.at(i)->getX() == targetX && playerBlock.at(i)->getY() == targetY) {
            target = playerBlock.at(i);
        }
    }
    return target;
}

string Interpreter::directionName(string direction) {
    if (direction == "no") {
        return "North";
    } else if (direction == "so") {
        return "South";
    } else if (direction == "ea") {
        return "East";
    } else if (direction == "we") {
        return "West";
    } else if (direction == "ne") {
        return "Northeast";
    } else if (direction == "nw") {
        return "Northwest";
    } else if (direction == "se") {
        return "Southeast";
    } else if (direction == "sw") {
        return "Southwest";
    }
    return string();
}

void Interpreter::movePlayer(Cell *target) {
    player->getCurrentCell()->transferEntity(target);
}

void Interpreter::usePotion(Potion *p) {
    p->apply(player.get());
}

void Interpreter::nextFloor() {
    floorNum++;
    // Only reset stats and generate next floor if we have not beaten the game yet.
    if (floorNum <= 4) {
        // Unbind player from current cell.
        player->getCurrentCell()->setEntity(nullptr);
        player->setCurrentCell(nullptr);
        player->resetStats();
        init();
    } else {
        command(string());
    }
}

Interpreter::~Interpreter() {}
