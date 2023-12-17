# include "Goblin.h"
using namespace std;

Goblin::Goblin(bool hard,Cell* currentCell, Cell* stair):
Enemy{70,5,10,nullptr,hard,currentCell,stair}{}


char Goblin::display_char(){
    return 'N';
}

std::string Goblin::getType() {
    return "Goblin";
}

Goblin::~Goblin(){};
