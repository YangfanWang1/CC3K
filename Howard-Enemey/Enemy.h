# ifndef ENEMY_H
# define ENEMY_H

# include <string>
# include <memory>
#include "Entity.h"

class Player;
class Cell;

class Enemy:public Entity{
    protected:
        bool compassHolder;
    public:
        Enemy(int HP,int ATK,int DEF,Entity* protector,bool hard,Cell* currentCell,bool compassHolder);
        virtual string getType() override = 0;
        void moveRandom();
        void attackPlayer(Entity*);
        // dragon and merchant override
        virtual void update();
        // Dragon and Merhcant override, PC does not get gold from them, and merchant drop merchant horde
        virtual void kill(Entity*);
        virtual ~Enemy();
};

# endif
