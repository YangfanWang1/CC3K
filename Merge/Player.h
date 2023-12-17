#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>

#include "Enemy.h"
#include "Entity.h"
#include "Treasure.h"

class Player : public Entity {
   protected:
   //stats of player
    bool barrier_suit;
    int baseatk;
    int basedef;
    int maxhp;
    int gold;

   public:
    Player(int HP, int ATK, int DEF, Entity* protector, bool hard, Cell* currentCell);
    // getter of HP
    int getMaxHP();
    //add money to PC when found treasure
    void collectTreasure(Treasure* t);
    //getter and mutator of barrier field
    bool getBarrier();
    void setBarrier(bool a);
    //gold functions for PC gold field
    virtual int getGold();
    virtual void setGold(int n);
    virtual void addGold(int g);
    //update of score for PC
    virtual int getScore();
    //rest stats of ATK and DEF when enter new floor
    void resetStats();
    //attack
    void attackEnemy(Enemy* e);
    char display_char() override;
    virtual ~Player() = default;
};

#endif
