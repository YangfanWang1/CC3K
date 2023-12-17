#include "Dragon_horde.h"

Dragon_horde::Dragon_horde(bool hard, Cell* currentCell, Entity* protector) : Treasure(6, protector, hard, currentCell) {}

std::string Dragon_horde::getType() {
    return "Dragon_horde";
}
