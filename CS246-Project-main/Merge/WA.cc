#include "WA.h"

#include "Elf.h"
class Player;

bool WA::used = false;

WA::WA(bool hard, Cell* cell) : Potion{"WA", hard, cell} {}

void WA::apply(Player* PC) {
    used = true;
    Elf* check = dynamic_cast<Elf*>(PC);
    if (check != nullptr) {
        PC->setATK(PC->getATK() + 5);
    } else {
        if (PC->getATK() - 5 <= 0) {
            PC->setATK(0);
        } else {
            PC->setATK(PC->getATK() - 5);
        }
    }
    kill();
}

bool WA::get_used() {
    return used;
}

void WA::reset_used() {
    used = false;
}
