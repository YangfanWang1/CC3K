# include "Elf.h"

Elf::Elf(bool hard,Cell* currentCell):
Player{140,30,10,nullptr,hard,currentCell}{
    baseatk = 30;
    basedef = 10;
    maxhp = 140;
}

std::string Elf::getType() {
    return "Elf";
}

Elf::~Elf(){};
