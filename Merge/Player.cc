#include "Player.h"

#include <math.h>
#include <memory>

#include "Enemy.h"
#include "Merchant.h"
#include "Treasure.h"
using namespace std;

Player::Player(int HP, int ATK, int DEF, Entity* protector, bool hard, Cell* currentCell) : Entity(HP, ATK, DEF, protector, hard, currentCell) {
    barrier_suit = false;
    gold = 0;
}

int Player::getMaxHP(){
    return maxhp;
}

void Player::collectTreasure(Treasure* t) {
    gold += t->getValue();
}

bool Player::getBarrier() {
    return barrier_suit;
}

void Player::setBarrier(bool a) {
    barrier_suit = a;
}

int Player::getGold() {
    return gold;
}

void Player::setGold(int n) {
    gold = n;
}

void Player::addGold(int g) {
    gold += g;
}

int Player::getScore() {
    return gold;
}

void Player::resetStats(){
    ATK = baseatk;
    DEF = basedef;
}

// if merchant, make merchant hostile
void Player::attackEnemy(Enemy* e) {
    if (e->getType() == "Merchant") {
        Merchant* merchant = dynamic_cast<Merchant*>(e);
        Merchant::set_hostile(true);
    }
    int enemy_damage = ceil((100.0 / (100.0 + e->getDEF())) * ATK);
    int enemy_HP_bef = e->getHP();
    if (enemy_HP_bef - enemy_damage <= 0) {
        e->setHP(0);
        e->kill(this);
    } else {
        e->setHP(enemy_HP_bef - enemy_damage);
    }
};

char Player::display_char(){
    return '@';
}
