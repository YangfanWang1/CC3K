#include <vector>
#include <memory>
#include "Chamber.h"
using namespace std;

class Cell;

Chamber::Chamber(int id) : id{id} {}

int Chamber::getId() const {
    return id;
}

vector<Cell *> Chamber::getCells() const {
    return cells;
}

void Chamber::setCells(std::vector<Cell *> newCells) {
    cells = newCells;
}

Chamber::~Chamber() {}
