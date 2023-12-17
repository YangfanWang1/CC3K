# include "Player.h"
# include "Enemy.h"
using namespace std;

void Player::collectTreasure(Treasure* t){
    gold += t->getGold();
};

void Player::setBarrier(bool a){
    barrier_suit = a;
};

int Player::getGold(){
    return gold;
};

void Player::setGold(int n){
    gold = n;
};

void Player::attackEnemy(Enemy* e){
    enemy_damage = ceil((100.0 / (100.0 + e->def)) * atk);
    enemy_HP_bef = e->getHP();
    e->setHP(enemy_HP_bef-enemy_damage);
};

void Player::kill(){};

Player::~Player(){};

