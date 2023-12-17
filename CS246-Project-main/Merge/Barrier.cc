#include "Barrier.h"
#include "Item.h"

Barrier::Barrier(Cell* currentCell) : Item{currentCell} {}

//the protector of barrier should be dragon, so once it's killed, it will unwind itself and make barrier's protector to null.
void Barrier::acquire(Player* PC) {
    PC->setBarrier(true);
    kill();
}

char Barrier::display_char(){
    return 'B';
}

std::string Barrier::getType() {
    return "Barrier";
}
