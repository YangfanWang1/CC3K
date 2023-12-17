#ifndef PHOENIX_H
#define PHOENIX_H

# include "Enemy.h"

class Phoenix:public Enemy{
    public:
        Phoenix(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void attackPlayer(Player*) override;
        ~Phoenix();
};

#endif
