#ifndef WEREWOLF_H
#define WEREWOLF_H

# include "Enemy.h"

class Werewolf:public Enemy{
    public:
        Werewolf(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell, bool compassHolder);
        void attackPlayer(Player*) override;
        ~Werewolf();
};

#endif
