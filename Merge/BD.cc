#include "BD.h"

bool BD::used = false;

BD::BD(bool hard, Cell* cell) : Potion{"BD", hard, cell} {}

void BD::apply(Player* PC) {
    used = true;
    PC->setDEF(PC->getDEF() + 5);
    kill();
}

bool BD::get_used() {
    return used;
}

void BD::reset_used() {
    used = false;
}
