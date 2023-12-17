#include "Cell.h"

#include <iostream>
#include <memory>
#include <vector>

#include "Entity.h"
using namespace std;

Cell::Cell(int x, int y, int type) : x{x}, y{y}, type{type}, entityHere{nullptr} {
    if (type == STAIRS) {
        hidden = true;
    } else {
        hidden = false;
    }
}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

int Cell::getType() const {
    return type;
}

void Cell::setType(int newType) {
    type = newType;
    if (newType == STAIRS) {
        hidden = true;
    }
}

vector<Cell *> Cell::getBlock() const {
    return block;
}

void Cell::setBlock(std::vector<Cell *> newBlock) {
    block = newBlock;
}

vector<Cell *> Cell::getWalkableBlock() const {
    vector<Cell *> walkable;
    for (int i = 0; i < (int) block.size(); ++i) {
        if (block[i]->getType() == OPEN || block[i]->getType() == STAIRS) {
            walkable.emplace_back(block[i]);
        }
    }
    return walkable;
}

void Cell::reveal() {
    hidden = false;
}

std::shared_ptr<Entity> Cell::getEntity() const {
    return entityHere;
}

void Cell::setEntity(std::shared_ptr<Entity> newEntity) {
    entityHere = newEntity;
}

void Cell::transferEntity(Cell *other) {
    if (entityHere) {
        entityHere->setCurrentCell(other);
    }
    if (other->entityHere) {
        other->entityHere->setCurrentCell(this);
    }
    entityHere.swap(other->entityHere);
}

void Cell::generateChamber(std::vector<Cell *> *cells, std::vector<Cell *> *allCells) {
    bool counted = false;
    for (int i = 0; i < (int) allCells->size(); ++i) {
        if (this == allCells->at(i)) {
            counted = true;
        }
    }
    if (!counted) {
        allCells->emplace_back(this);
    }
    if (!counted && (this->type == OPEN || this->type == STAIRS)) {
        cells->emplace_back(this);
        for (int i = 0; i < (int) block.size(); ++i) {
            block.at(i)->generateChamber(cells, allCells);
        }
    }
}

Cell::~Cell() {}

ostream &operator<<(ostream &out, const Cell &c) {
    // If an entity exists on the cell, display it instead. Otherwise, display the cell.
    if (c.entityHere.get()) {
        out << c.getEntity()->display_char(); 
    } else {
        // Add special colors for each cell type later.
        if (c.type == SOLID) {
            out << cellDisplay[c.type];
        } else if (c.type == OPEN) {
            out << cellDisplay[c.type];
        } else if (c.type == H_WALL) {
            out << cellDisplay[c.type];
        } else if (c.type == V_WALL) {
            out << cellDisplay[c.type];
        } else if (c.type == DOORWAY) {
            out << cellDisplay[c.type];
        } else if (c.type == PASSAGE) {
            out << cellDisplay[c.type];
        } else if (c.type == STAIRS) {
            if (c.hidden) {
                out << cellDisplay[OPEN];
            } else {
                out << cellDisplay[c.type];
            }
        }
    }
    return out;
}

// ALTERNATE VERSION OF THE CELL OUTPUT OPERATOR WHICH INCLUDES COLOR.
// Note: MUCH slower, which is why it's disabled.
/* 
ostream &operator<<(ostream &out, const Cell &c) {
    // If an entity exists on the cell, display it instead. Otherwise, display the cell.
    if (c.entityHere.get()) {
        if (c.getEntity()->getType() == "Human" || c.getEntity()->getType() == "Elf" || 
            c.getEntity()->getType() == "Dwarf" || c.getEntity()->getType() == "Orc") {
            out << "\u001b[35m";
        } else if (c.getEntity()->getType() == "Normal" || c.getEntity()->getType() == "Small" || 
                   c.getEntity()->getType() == "Merchant_horde" || c.getEntity()->getType() == "Dragon_horde") {
            out << "\u001b[33m";
        } else if (c.getEntity()->getType() == "Compass") {
            out << "\u001b[34m";
        } else if (c.getEntity()->getType() == "Barrier") {
            out << "\u001b[31m";
        } else if (c.getEntity()->getType() == "BA" || c.getEntity()->getType() == "WA" ||
                   c.getEntity()->getType() == "BD" || c.getEntity()->getType() == "WD" ||
                   c.getEntity()->getType() == "RH" || c.getEntity()->getType() == "PH") {
            out << "\u001b[32m";
        } else if (c.getEntity()->getType() == "Vampire") {
            out << "\u001b[30;1m";
        } else if (c.getEntity()->getType() == "Werewolf") {
            out << "\u001b[34;1m";
        } else if (c.getEntity()->getType() == "Troll") {
            out << "\u001b[36;1m";
        } else if (c.getEntity()->getType() == "Goblin") {
            out << "\u001b[32;1m";
        } else if (c.getEntity()->getType() == "Dragon") {
            out << "\u001b[33;1m";
        } else if (c.getEntity()->getType() == "Phoenix") {
            out << "\u001b[31;1m";
        } else if (c.getEntity()->getType() == "Merchant") {
            out << "\u001b[35;1m";
        }
        out << c.getEntity()->display_char(); 
    } else {
        if (c.type == SOLID) {
            out << "\u001b[0m" << cellDisplay[c.type];
        } else if (c.type == OPEN) {
            out << "\u001b[30;1m" << cellDisplay[c.type];
        } else if (c.type == H_WALL) {
            out << "\u001b[0m" << cellDisplay[c.type];
        } else if (c.type == V_WALL) {
            out << "\u001b[0m" << cellDisplay[c.type];
        } else if (c.type == DOORWAY) {
            out << "\u001b[30;1m" << cellDisplay[c.type];
        } else if (c.type == PASSAGE) {
            out << "\u001b[30;1m" << cellDisplay[c.type];
        } else if (c.type == STAIRS) {
            if (c.hidden) {
                out << "\u001b[30;1m" << cellDisplay[OPEN];
            } else {
                out << "\u001b[36m" << cellDisplay[c.type];
            }
        }
    }
    out << "\u001b[0m";
    return out;
}
*/
