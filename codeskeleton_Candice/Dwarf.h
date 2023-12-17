# ifndef DWARF_H
# define DWARF_H

# include "Player.h"

class Dwarf:public Player{
    public:
        Dwarf(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell);
        ~Dwarf();
};

# endif
