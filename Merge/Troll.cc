# include "Troll.h"
using namespace std;

Troll::Troll(bool hard,Cell* currentCell, Cell* stair):
Enemy{120,25,15,nullptr,hard,currentCell,stair}{}

char Troll::display_char(){
    return 'T';
}

std::string Troll::getType() {
    return "Troll";
}

Troll::~Troll(){};
