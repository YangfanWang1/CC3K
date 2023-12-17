#include "Treasure.h"

Treasure::Treasure(int value,Entity* protector, bool hard, Cell* currentCell):value{value},
    Entity(0, 0, 0, protector, hard, currentCell){}

char Treasure::display_char(){
    return 'G';
}

int Treasure::getValue(){
    return value;
}
