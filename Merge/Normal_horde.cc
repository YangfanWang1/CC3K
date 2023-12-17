#include "Normal_horde.h"

// worth of 1
Normal::Normal(bool hard, Cell* currentCell, Entity* protector) : Treasure(1, protector, hard, currentCell) {}

std::string Normal::getType() {
    return "Normal";
}
