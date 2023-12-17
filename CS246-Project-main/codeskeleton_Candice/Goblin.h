#ifndef GOBLIN_H
#define GOBLIN_H

# include "Enemy.h"

class Goblin:public Enemy{
    public:
        Goblin(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void attackPlayer(Player*) override;
        ~Goblin();
};

#endif
