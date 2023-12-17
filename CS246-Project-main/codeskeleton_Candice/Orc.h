# ifndef ORC_H
# define ORC_H

# include "Player.h"

class Orc:public Player{
    public:
        Orc(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell);
        ~Orc();
};

# endif
