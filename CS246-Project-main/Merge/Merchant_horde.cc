#include "Merchant_horde.h"

Merchant_horde::Merchant_horde(bool hard, Cell* currentCell, Entity* protector) : Treasure(4, protector, hard, currentCell) {}

std::string Merchant_horde::getType() {
    return "Merchant_horde";
}
