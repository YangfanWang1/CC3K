#ifndef ELF_H
#define ELF_H

#include "Player.h"

class Elf:public Player{
    public:
        Elf(bool hard,Cell* currentCell);
        std::string getType() override;
        ~Elf();
};

#endif
