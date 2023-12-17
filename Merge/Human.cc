#include "Human.h"

Human::Human(bool hard, Cell* currentCell) : Player{140, 20, 20, nullptr, hard, currentCell} {
    baseatk = 20;
    basedef = 20;
    maxhp = 140;
}

// NOTE: Humans have a 50% score increase.
int Human::getScore() {
    return gold * 3 / 2;
}

std::string Human::getType() {
    return "Human";
}

Human::~Human(){};
