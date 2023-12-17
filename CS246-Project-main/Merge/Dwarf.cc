# include "Dwarf.h"

Dwarf::Dwarf(bool hard,Cell* currentCell):
Player{100,20,30,nullptr,hard,currentCell}{
    basedef = 30;
    baseatk = 20;
    maxhp = 100;
}

// NOTE: Dwarves have double gold. Since we don't have to deal with integer rounding, we can
//   just store the doubled value directly, unlike for Orcs.
void Dwarf::addGold(int g) {
    gold += g * 2;
}

std::string Dwarf::getType() {
    return "Dwarf";
}

Dwarf::~Dwarf(){};
