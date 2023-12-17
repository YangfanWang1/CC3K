#ifndef VAMPIRE_H
#define VAMPIRE_H

# include "Enemy.h"

class Vampire:public Enemy{
    public:
        Vampire(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void attackPlayer(Player*) override;
        ~Vampire();
};

#endif
