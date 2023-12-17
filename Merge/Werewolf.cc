# include "Werewolf.h"
using namespace std;

Werewolf::Werewolf(bool hard,Cell* currentCell, Cell* stair):
Enemy{120, 30, 5,nullptr,hard,currentCell,stair}{}

char Werewolf::display_char(){
    return 'W';
}

std::string Werewolf::getType() {
    return "Werewolf";
}

Werewolf::~Werewolf(){};
