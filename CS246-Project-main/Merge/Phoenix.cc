# include "Phoenix.h"
using namespace std;

Phoenix::Phoenix(bool hard,Cell* currentCell, Cell* stair):
Enemy{50,35,20,nullptr,hard,currentCell,stair}{}

char Phoenix::display_char(){
    return 'X';
}

std::string Phoenix::getType() {
    return "Phoenix";
}

Phoenix::~Phoenix(){};
