#include "Merchant.h"

#include <iostream>
#include <sstream>
#include <memory>

#include "Merchant_horde.h"
#include "Player.h"

using namespace std;

bool Merchant::M_hostile = false;

Merchant::Merchant(bool hard, Cell* currentCell, Cell* stair) : Enemy{30, 70, 5, nullptr, hard, currentCell, stair} {};

std::string Merchant::getType() {
    return "Merchant";
}

bool Merchant::get_hostile() {
    return M_hostile;
}
void Merchant::set_hostile(bool hostile) {
    M_hostile = hostile;
}

char Merchant::display_char() {
    return 'M';
}

string Merchant::update() {
    Entity::seed++;
    if (M_hostile == true) {
        for (int i = 0; i < currentCell->getBlock().size(); i++) {
            Entity* temp_entity = (currentCell->getBlock().at(i)->getEntity().get());
            Player* PC = dynamic_cast<Player*>(temp_entity);
            if (PC != nullptr) {
                if (PC->getType() == "Human" || PC->getType() == "Elf" ||
                    PC->getType() == "Dwarf" || PC->getType() == "Orc") {
                    ostringstream result;
                    if (HP <= 0) {
                        kill(PC);
                        result << "M dies. ";
                    } else {
                        int prevHP = PC->getHP();
                        bool attack_success = attackPlayer(PC);
                        if (attack_success) {
                            result << "M deals " << prevHP - PC->getHP() << " damage to PC";
                            if (PC->getBarrier()) {
                                result << " (Barrier suit equipped). ";
                            } else {
                                result << ". ";
                            }
                        } else {
                            result << "M attacks, but misses. ";
                        }
                    }
                    return result.str();
                }
            }
        }
    }
    moveRandom();
    return string();
}


void Merchant::kill(Player *PC) {
    // unbind myself from cell and get it to horde

    if (stair != nullptr) {
        currentCell->setEntity(std::make_shared<Compass>(currentCell, stair));
    } else {
        currentCell->setEntity(std::make_shared<Merchant_horde>(hard, currentCell));
    }
}
