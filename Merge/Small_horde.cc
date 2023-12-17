#include "Small_horde.h"

Small::Small(bool hard, Cell* currentCell, Entity* protector) : Treasure{2, protector, hard, currentCell} {}

std::string Small::getType() {
    return "Small";
}
