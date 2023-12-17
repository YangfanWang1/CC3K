#ifndef MERCHANT_H
#define MERCHANT_H

# include "Enemy.h"

class Merchant:public Enemy{
    static bool M_hostile;
    public:
        Merchant(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void attackPlayer(Player*) override;
        ~Merchant();
};

#endif
