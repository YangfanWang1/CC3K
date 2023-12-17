# ifndef DRAGON_H
# define DRAGON_H

# include "Enemy.h"

class Dragon:public Enemy{
    public:
        Dragon(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        Cell* setAggroTrigger() override;
        void moveRandom() override;
        void attackPlayer(Player*);
        // create_barrier randomly 
        void create_barrier();
        ~Dragon();
};

# endif
