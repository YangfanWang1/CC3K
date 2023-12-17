// This module implements a Cell class which manages location, entity, and neighbour data.

#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include <memory>
#include "Entity.h"

class Cell {
    private:
        const int x;
        const int y;
        const int type;
        std::shared_ptr<Entity> entityHere;  // Stores Entity on current Cell.
        std::vector<Cell *> block;           // Lists Cells in surrounding block.
        bool hidden;                         // To hide stair-type cells.
    public:
        // Basic Constructor.
        Cell(int x, int y, int type);

        // Accessors for X and Y-coords.
        int getX() const;
        int getY() const;
        // Accessor for Cell type.
        int getType() const;
        // Accessor and mutator for list of Cells in surrounding block.
        std::vector<Cell *> getBlock() const;
        void setBlock(std::vector<Cell *>);
        // Sets [hidden] to false.
        void reveal();

        // Accessor and mutator for Entity on current Cell.
        Entity * getEntity() const;
        void setEntity(Entity *);
        // Swaps the Entities for current and given cell.
        void transferEntity(Cell *);

        // Basic Constructor.
        ~Cell();

        // Display given Cell to output.
        friend std::ostream &operator<<(std::ostream &out, const Cell &c);
};

#endif
