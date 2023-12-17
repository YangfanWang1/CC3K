#ifndef TROLL_H
#define TROLL_H

# include "Enemy.h"

class Troll:public Enemy{
    public:
        Troll(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void attackPlayer(Player*) override;
        ~Troll();
};

#endif
