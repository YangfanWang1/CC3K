# ifndef PLAYER_H
# define PLAYER_H

# include <string>
# include <memory>
//# include "Entity.h"
class Entity;

class Player;
class Cell;

class Enemy:public Entity{
    protected:
        Cell* aggroTrigger;
        bool compassHolder;
    public:
        // only dragon overrides
        virtual Cell* setAggroTrigger();
        // only dragon overrides
        virtual void moveRandom();
        virtual void attackPlayer(Player*);
        void update();
        void kill();
        virtual ~Enemy() = 0;
};

# endif
