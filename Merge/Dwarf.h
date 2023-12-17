#ifndef DWARF_H
#define DWARF_H

#include "Player.h"

class Dwarf:public Player{
    public:
        Dwarf(bool hard,Cell* currentCell);
        void addGold(int g) override;
        std::string getType() override;
        ~Dwarf();
};

#endif
