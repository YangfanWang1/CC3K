#include "Enemy.h"

#include <algorithm>
#include <memory>

#include "Player.h"
using namespace std;

Enemy::Enemy(int HP, int ATK, int DEF, Entity* protector, bool hard, Cell* currentCell, bool compassHolder) : Entity(HP, ATK, DEF, protector, hard, currentCell), compassHolder{compass Holder} {}

// not finished, could be wrong
void Enemy::moveRandom() {
    // check if all block is full
    for (int i = 0; i < currentCell->getBlock().size(); i++) {
        if (currentCell->getBlock().at(i)->getEntity() != nullptr) {
            return;
        }
    }
    // have an avilable spot to move
    currentCell->setEntity(nullptr);
    vector<Cell*> block = currentCell->getBlock();
    int dir = rand(seed) % v.size();
    // pick a direction and try to move first
    Cell* next_cell = block[dir];
    // if that direction is occupied, picks another direction
    while (next_cell->getEntity() != nullptr) {
        dir = rand(seed) % v.size();
        next_cell = block[dir];
    }
    currentCell = next_cell;
    // currentCell->setEntity(shared_ptr<*this>);
};

void Enemy::attackPlayer(Player* PC) {
    PC->setHP(PC->getHP() - getATK());
};

// my thought on update
//  we check is player within the range or not first, if so then attack directly, and not move. otherwise randome moving
void Enemy::update() {
    Entity::seed++;
    for (int i = 0; i < currentCell->getBlock().size(); i++) {
        if (getType() == "Player") {
            attackPlayer(currentCell->getBlock().at(i));
            return;
        }
    }
    moveRandom();
};

void kill(Plyaer* PC) {
    if (getHP() <= 0) {
        // cant be less than 0;
        setHP = 0;
        PC->setGold(PC->getGold() + getGold());
        // unwind myself from cell;

        // if I'm compass holder:
        if (compassHolder) {
            // I don't think there will be full around the block, so this is an invariant
            for (int i = 0; i < currentCell->getBlock().size(); i++) {
                if (currentCell->getBlock().at(i) == nullptr) {
                    // call ctor for comapss and pass stair
                    break;
                }
            }
            // unwind myself
            currentCell->setEntity = nullptr;
            // Not heap allocation, so no worry on dtor callin
        } else {
            return;
        }
    }
}

