# ifndef ELF_H
# define ELF_H

# include "Player.h"

class Elf:public Player{
    public:
        Elf(int HP,int ATK,int DEF, Entity* protector, bool hard,Cell* currentCell);
        ~Elf();
};

# endif
