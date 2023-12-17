#include "Entity.h"
#include "Item.h"

Item::Item(Cell *currentCell) : Entity{1, 0, 0, nullptr, false, currentCell} {}
