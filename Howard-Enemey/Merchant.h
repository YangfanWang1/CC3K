#ifndef MERCHANT_H
#define MERCHANT_H

# include "Enemy.h"

class Merchant:public Enemy{
    static bool M_hostile;
    public:
        Merchant(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void set_hostile(bool hostile);
        void update() override;
        void purchasePotion(Player* PC,string Potion);
        string getType() override;
        ostream& operator<<(ostream& out, Merchant m);
        ~Merchant()=default;
        void kill() override;
};

#endif
