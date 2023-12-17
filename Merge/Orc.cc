# include "Orc.h"

Orc::Orc(bool hard,Cell* currentCell):
Player{180,30,25,nullptr,hard,currentCell} {
    baseatk = 30;
    basedef = 25;
    maxhp = 180;
}

// NOTE: For orcs, gold has half value.
// To deal with integer rounding properly, the gold field stores the not-halved amount of gold for the Orc.
// getGold() returns the halved amount.
int Orc::getGold(){
    return gold / 2;
}
// setGold() sets the orc's gold to TWICE the given value, so that when halved it becomes what we want.
void Orc::setGold(int n) {
    gold = n * 2;
}
// getScore() also returns the halved amount so the score is accurate.
int Orc::getScore() {
    return this->getGold();
}

std::string Orc::getType() {
    return "Orc";
}

Orc::~Orc(){};
