#include <vector>
#include <memory>
#include "Cell.h"
#include "Chamber.h"
using namespace std;

Chamber::Chamber(int id) : id{id} {}

int Chamber::getId() const {
    return id;
}

vector<shared_ptr<Cell>> Chamber::getCells() const {
    return cells;
}

void Chamber::setCells(std::vector<std::shared_ptr<Cell>> newCells) {
    cells = newCells;
}

Chamber::~Chamber() {}

void Chamber::update() {
    return;
}
