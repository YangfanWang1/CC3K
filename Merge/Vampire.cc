# include "Vampire.h"
using namespace std;

Vampire::Vampire(bool hard,Cell* currentCell, Cell* stair):
Enemy{50,25,25,nullptr,hard,currentCell,stair}{}

char Vampire::display_char(){
    return 'V';
}

std::string Vampire::getType() {
    return "Vampire";
}

Vampire::~Vampire(){};
