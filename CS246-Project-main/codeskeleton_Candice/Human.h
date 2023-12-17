# ifndef HUMAN_H
# define HUMAN_H

# include "Player.h"

class Human:public Player{
    public:
        Human(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell);
        ~Human();
};

# endif
