// This module implements a Chamber class which stores pointers to Cell objects.

#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <vector>
#include <memory>

class Cell;

class Chamber {
    private:
        const int id;
        std::vector<Cell *> cells; // Stores Cells.
    public:
        // Basic Constructor.
        Chamber(int id);

        // Accessor for Chamber ID.
        int getId() const;
        // Accessor and mutator for Cells.
        std::vector<Cell *> getCells() const;
        void setCells(std::vector<Cell *>);

        // Basic Destructor.
        ~Chamber();
};

#endif
