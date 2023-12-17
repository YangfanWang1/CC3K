#include "WD.h"

#include "Elf.h"

bool WD::used = false;

WD::WD(bool hard, Cell* cell) : Potion{"WD", hard, cell} {}

void WD::apply(Player* PC) {
    used = true;
    Elf* check = dynamic_cast<Elf*>(PC);
    if (check != nullptr) {
        PC->setDEF(PC->getDEF() + 5);
    } else {
        if (PC->getDEF() - 5 <= 0) {
            PC->setDEF(0);
        } else {
            PC->setDEF(PC->getDEF() - 5);
        }
    }
    kill();
}

bool WD::get_used() {
    return used;
}

void WD::reset_used() {
    used = false;
}
