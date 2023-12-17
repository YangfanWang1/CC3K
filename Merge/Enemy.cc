#include "Enemy.h"

#include <math.h>

#include <algorithm>
#include <memory>
#include <sstream>
#include <iostream>
#include "Compass.h"
#include "Entity.h"
#include "Player.h"

using namespace std;

Enemy::Enemy(int HP, int ATK, int DEF, Entity* protector, bool hard, Cell* currentCell, Cell* stair) : Entity(HP, ATK, DEF, protector, hard, currentCell), stair{stair} {}

void Enemy::setStair(Cell* newStair) {
    stair = newStair;
}

void Enemy::moveRandom() {
    // check if all block is full,if full, return
    for (int i = 0; i < currentCell->getWalkableBlock().size(); i++) {
        if (currentCell->getWalkableBlock().at(i)->getEntity() == nullptr) {
            break;
        }
        if (i == currentCell->getWalkableBlock().size() - 1) {
            return;
        }
    }
    // have an avilable spot to move
    vector<Cell*> block = currentCell->getWalkableBlock();
    srand(Entity::seed);
    int dir = rand() % block.size();
    seed++;
    srand(Entity::seed);
    // pick a direction and try to move first
    Cell* next_cell = block[dir];
    // if that direction is occupied, pick another direction
    while (next_cell->getEntity() != nullptr) {
        dir = rand() % block.size();
        // dir=rand(seed)%v.size();
        next_cell = block[dir];
    }
    currentCell->transferEntity(next_cell);
}

// dragon should override, merchant check hostile
// 50 percent chance of missing
bool Enemy::attackPlayer(Player* pc) {
    // choose a number, 0 or 1
    seed++;
    srand(seed);
    int status = rand() % 2;
    // attack if 0
    if (status == 0) {
        int player_damage = 0;
        int player_HP_before = pc->getHP();
        // if player has no barrier
        if (!pc->getBarrier()) {
            player_damage = ceil((100.0 / (100.0 + pc->getDEF())) * ATK);

        } else {
            player_damage = ceil(ceil((100.0 / (100.0 + pc->getDEF())) * ATK) / 2);
        }
        if (player_HP_before - player_damage <= 0) {
            pc->setHP(0);
        } else {
            pc->setHP(player_HP_before - player_damage);
        }
        return true;
    } else {
        return false;
    }
}

// we check is player within the range or not first, if so then attack directly, and not move. otherwise randome moving
string Enemy::update() {
    Entity::seed++;
    for (int i = 0; i < currentCell->getBlock().size(); i++) {
        std::shared_ptr<Player> PC = std::dynamic_pointer_cast<Player>(currentCell->getBlock().at(i)->getEntity());
        if (PC != nullptr) {
            if (PC->getType() == "Human" || PC->getType() == "Elf" ||
                PC->getType() == "Dwarf" || PC->getType() == "Orc") {
                ostringstream result;
                // shared pointer and pointer?
                // if enemy dies or not
                if (HP <= 0) {
                    kill(PC.get());
                    result << display_char() << " dies. ";
                } else {
                    int prevHP = PC->getHP();
                    bool attack_success = attackPlayer(PC.get());
                    if (attack_success) {
                        result << display_char() << " deals " << prevHP - PC->getHP() << " damage to PC";
                        if (PC->getBarrier()) {
                            result << " (Barrier suit equipped). ";
                        } else {
                            result << ". ";
                        }
                    } else {
                        result << display_char() << " attacks, but misses. ";
                    }
                }
                return result.str();
            }
        }
    }
    moveRandom();
    return string();
}

void Enemy::kill(Player* PC) {
    if (this->getHP() <= 0) {
        setHP(0);
        // 1 gold per enemy dead
        PC->addGold(1);
        // unbind myself from cell
        currentCell->setEntity(nullptr);
        // if I'm compass holder:
        if (stair != nullptr) {
            currentCell->setEntity(std::make_shared<Compass>(currentCell, stair));
            currentCell->reveal();
        }
    } else {
        return;
    }
};
