// This module implements a Floor class which manages Chamber and Cell objects.

#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <vector>
#include <memory>
#include "Chamber.h"
#include "Cell.h"

class Floor {
    private:
        std::vector<std::shared_ptr<Chamber>> chambers; // Store Chambers.
        std::vector<std::shared_ptr<Cell>> cells;       // Store Cells.
    public:
        // Basic Constructor.
        Floor();

        // Accessor for Chambers.
        std::vector<std::shared_ptr<Chamber>> getChambers() const;
        // Accessor for Cells.
        std::vector<std::shared_ptr<Cell>> getCells() const;

        // Generate new Floor, resets layout and Entities.
        void generate();
        // Update existing Floor cell-by-cell.
        void update();

        // Basic Destructor.
        ~Floor();

        // Display given Floor to output.
        friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};

#endif
