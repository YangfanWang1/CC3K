#include "Entity.h"
#include <iostream>
class Cell;
//I am leaving initlization of values to 1 for now.So the feature of items that is breakable is avliable, and these fields will be updated when sub-classes called.
Entity::Entity(int HP,int ATK,int DEF,Entity* protector,bool hard,Cell* currentCell):HP{HP},ATK{ATK},DEF{DEF},protector{protector},hard{hard},currentCell{currentCell}{int seed = 1;}


int Entity::getHP(){
    return HP;
}

int Entity::getATK(){
    return ATK;
}

int Entity::getDEF(){
    return DEF;
}

Entity* Entity::getProtector(){
    return protector;
}

Cell* Entity::getCurrentCell(){
    return currentCell;
}


void Entity::setHP(int HP){
    this->HP=HP;
}

void Entity::setATK(int ATK){
    this->ATK=ATK;
}

void Entity::setDEF(int DEF){
    this->DEF=DEF;
}

void Entity::setProtector(Entity* protector){
    this->protector=protector;
}

void Entity::setCurrentCell(Cell* cell){
    this->currentCell=cell;
}

//just unwinding you from the cell,i am not calling dtor since this is the parent class, call dtor yourself
void Entity::kill(){
    this->getCurrentCell()->setEntity(nullptr);
}
