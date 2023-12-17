// This module implements a Cell class which manages location, entity, and neighbour data.

#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include <memory>

// List of possible cell types.
const int SOLID = 0;
const int OPEN = 1;
const int H_WALL = 2;
const int V_WALL = 3;
const int DOORWAY = 4;
const int PASSAGE = 5;
const int STAIRS = 6;
const std::vector<char> cellDisplay{' ', '.', '-', '|', '+', '#', '\\'};

class Entity;

class Cell {
    private:
        const int x;
        const int y;
        int type;
        std::shared_ptr<Entity> entityHere;  // Stores Entity on current Cell.
        std::vector<Cell *> block;           // Lists Cells in surrounding block.
        bool hidden;                         // To hide stair-type cells.
    public:
        // Basic Constructor.
        Cell(int x, int y, int type);

        // Accessors for X and Y-coords.
        int getX() const;
        int getY() const;
        // Accessor and Mutator for Cell type.
        int getType() const;
        void setType(int newType);
        // Accessor and mutator for list of Cells in surrounding block.
        std::vector<Cell *> getBlock() const;
        void setBlock(std::vector<Cell *>);
        // Special version of .getBlock() which only includes cells walkable by Enemies.
        std::vector<Cell *> getWalkableBlock() const;
        // Sets [hidden] to false.
        void reveal();

        // Accessor and mutator for Entity on current Cell.
        std::shared_ptr<Entity> getEntity() const;
        void setEntity(std::shared_ptr<Entity>);
        // Swaps the Entities for current and given cell.
        void transferEntity(Cell *);

        // Recursively adds all neighbouring cells to the given Chamber.
        void generateChamber(std::vector<Cell *> *cells, std::vector<Cell *> *allCells);

        // Basic Destructor.
        ~Cell();

        // Display given Cell to output.
        friend std::ostream &operator<<(std::ostream &out, const Cell &c);
};

#endif
