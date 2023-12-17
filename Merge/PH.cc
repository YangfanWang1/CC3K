#include "PH.h"

#include "Elf.h"
class Player;

bool PH::used = false;

PH::PH(bool hard, Cell* cell) : Potion{"PH", hard, cell} {}

// potion is diffent, after kill that makes it unwind from cell, it will call dtor by itself.
void PH::apply(Player* PC) {
    used = true;
    Elf* check = dynamic_cast<Elf*>(PC);
    if (check != nullptr) {
        if ((PC->getHP()+10) <= PC->getMaxHP()) {
            PC->setHP(PC->getHP() + 10);
        } else {
            PC->setHP(PC->getMaxHP());
        }
    } else {
        if(PC->getHP()-10 >= 0){
            PC->setHP(PC->getHP() - 10);
        } else {
            PC->setHP(0);
        }
    }
    kill();
}

bool PH::get_used() {
    return used;
}

void PH::reset_used() {
    used = false;
}
