#include <iostream>
#include <vector>
#include <memory>
#include "Entity.h"
#include "Cell.h"
using namespace std;

Cell::Cell(int x, int y, int type) : x{x}, y{y}, type{type}, entityHere{nullptr}, hidden{false} {}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

int Cell::getType() const {
    return type;
}

vector<Cell *> Cell::getBlock() const {
    return block;
}

void Cell::setBlock(std::vector<Cell *> newBlock) {
    block = newBlock;
}

void Cell::reveal() {
    hidden = false;
}

Entity * Cell::getEntity() const {
    return entityHere.get();
}

void Cell::setEntity(Entity *) {
    return;
}

void Cell::transferEntity(Cell *) {
    return;
}

Cell::~Cell() {}

ostream &operator<<(ostream &out, const Cell &c) {
    return out;
}
