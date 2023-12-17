#include <iostream>
#include <vector>
#include <memory>
#include "Chamber.h"
#include "Cell.h"
#include "Floor.h"
using namespace std;

Floor::Floor() {}

vector<shared_ptr<Chamber>> Floor::getChambers() const {
    return chambers;
}

vector<shared_ptr<Cell>> Floor::getCells() const {
    return cells;
}

void Floor::generate() {
    return;
}

void Floor::update() {
    return;
}

Floor::~Floor() {}

ostream &operator<<(ostream &out, const Floor &f) {
    return out;
}
