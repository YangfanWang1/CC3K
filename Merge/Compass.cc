#include "Compass.h"
#include "Item.h"

class Cell;

Compass::Compass(Cell* currentCell, Cell* stair) : stair{stair}, Item(currentCell) {}

// check if user on the same pos of compass, if so, make stair cell appear, and unwind compass from cell
void Compass::acquire(Player* PC) {
    stair->reveal();
    kill();
}

char Compass::display_char() {
    return 'C';
}

std::string Compass::getType() {
    return "Compass";
}
