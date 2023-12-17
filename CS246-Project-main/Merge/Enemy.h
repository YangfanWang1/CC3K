#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include "Entity.h"

class Player;
class Cell;

class Enemy : public Entity {
   protected:
    Cell* stair;   // Stairs pointer. Nullptr if enemy is not the compass holder.

   public:
    Enemy(int HP, int ATK, int DEF, Entity* protector, bool hard, Cell* currentCell, Cell* stair);
    // Setter for stair pointer.
    void setStair(Cell * newStair);
    void moveRandom();

    // Calls the enemy to attack the given player.
    // Returns a bool for if the attack missed or not (necessary for display purposes).
    bool attackPlayer(Player*);

    // dragon and merchant override
    // Returns a string which explains what the Enemy has done.
    virtual std::string update();

    // Dragon and Merhcant override, PC does not get gold from them, and merchant drop merchant horde
    virtual void kill(Player*);
    virtual ~Enemy() = default;
};

#endif
