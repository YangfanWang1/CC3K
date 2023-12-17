#include "Potion.h"

#include <string>

Potion::Potion(std::string type, bool hard, Cell* currentCell, Entity* protector) : type{type}, Entity(0, 0, 0, protector, hard, currentCell) {}

// Should be overridden by subclasses.
bool Potion::get_used() {
    return false;
}

char Potion::display_char() {
    return 'P';
}

std::string Potion::getType() {
    return type;
}
