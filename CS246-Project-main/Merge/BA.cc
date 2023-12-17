#include "BA.h"
class Player;

bool BA::used = false;

BA::BA(bool hard, Cell* cell) : Potion{"BA", hard, cell} {}

void BA::apply(Player* PC) {
    used = true;
    PC->setATK(PC->getATK() + 5);
    kill();
}

bool BA::get_used() {
    return used;
}

void BA::reset_used() {
    used = false;
}
