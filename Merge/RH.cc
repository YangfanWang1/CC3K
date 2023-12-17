#include "RH.h"
class Player;

bool RH::used = false;

RH::RH(bool hard, Cell* cell) : Potion{"RH", hard, cell} {}

// potion is diffent, after kill that makes it unwind from cell, it will call dtor by itself.
void RH::apply(Player* PC) {
    used = true;
    if ((PC->getHP() + 10) <= PC->getMaxHP()) {
        PC->setHP(PC->getHP() + 10);
    } else {
        PC->setHP(PC->getMaxHP());
    }
    kill();
}

bool RH::get_used() {
    return used;
}

void RH::reset_used() {
    used = false;
}
