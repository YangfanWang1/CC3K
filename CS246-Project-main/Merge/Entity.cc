#include "Entity.h"

#include <iostream>
class Cell;
int Entity::seed = 0;
Entity::Entity(int HP, int ATK, int DEF, Entity* protector, bool hard, Cell* currentCell) : HP{HP}, ATK{ATK}, DEF{DEF}, protector{protector}, hard{hard}, currentCell{currentCell} {}

int Entity::getHP() {
    return HP;
}

int Entity::getATK() {
    return ATK;
}

int Entity::getDEF() {
    return DEF;
}

Entity* Entity::getProtector() {
    return protector;
}

std::string Entity::getType(){
    return "";
}

Cell* Entity::getCurrentCell() {
    return currentCell;
}

void Entity::setHP(int HP) {
    this->HP = HP;
}

void Entity::setATK(int ATK) {
    this->ATK = ATK;
}

std::string Entity::update(){
    return std::string();
}

void Entity::setDEF(int DEF) {
    this->DEF = DEF;
}

void Entity::setProtector(Entity* protector) {
    this->protector = protector;
}

void Entity::setCurrentCell(Cell* cell) {
    this->currentCell = cell;
}

// Supposed to be overridden
void Entity::checkForProtectors() {
    return;
}

void Entity::deleteProtected(Entity* protectedEnt) {
    std::vector<Entity *> temp;
    for (int i = 0; i < protectedList.size(); ++i) {
        if (protectedEnt != protectedList.at(i)) {
            temp.emplace_back(protectedList.at(i));
        }
    }
    protectedList = temp;
}

// just unbinding you from the cell,i am not calling dtor since this is the parent class, call dtor yourself
void Entity::kill() {
    this->getCurrentCell()->setEntity(nullptr);
    currentCell = nullptr;

    // Unlinks any protectors, if necessary (FOR DLC)
    if (protector) {
        protector->deleteProtected(this);
    }
    for (int i = 0; i < protectedList.size(); ++i) {
        protectedList.at(i)->setProtector(nullptr);
    }
}

// supposed to be overriden
char Entity::display_char(){
    return (char) 0;
}
