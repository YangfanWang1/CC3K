// This module implements a Chamber class which stores pointers to Cell objects.

#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <vector>
#include <memory>
#include "Cell.h"

class Chamber {
    private:
        const int id;
        std::vector<std::shared_ptr<Cell>> cells; // Stores Cells.
    public:
        // Basic Constructor.
        Chamber(int id);

        // Accessor for Chamber ID.
        int getId() const;
        // Accessor and mutator for Cells.
        std::vector<std::shared_ptr<Cell>> getCells() const;
        void setCells(std::vector<std::shared_ptr<Cell>>);

        // Update existing Chamber cell-by-cell.
        void update();

        // Basic Destructor.
        ~Chamber();
};

#endif
