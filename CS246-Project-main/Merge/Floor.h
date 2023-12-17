// This module implements a Floor class which manages Chamber and Cell objects.

#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <memory>
#include <vector>

class Chamber;
class Cell;

// Board dimensions.
const int board_width = 79;
const int board_height = 25;

class Floor {
   private:
    std::vector<std::shared_ptr<Chamber>> chambers;  // Store Chambers.
    std::vector<std::shared_ptr<Cell>> cells;        // Store Cells.
    Cell *stairsCell;                                // Stores a pointer to the stairs.
   public:
    // Basic Constructor.
    Floor();

    // Accessor for Chambers.
    std::vector<std::shared_ptr<Chamber>> getChambers() const;
    // Accessor for Cells.
    std::vector<std::shared_ptr<Cell>> getCells() const;
    // Accessor & Mutator for stairsCell.
    Cell *getStairs() const;
    void setStairs(Cell *newStairs);

    // get available cell position for random generation
    Cell *get_available_cell(int chamber_num, int seed);

    // Generate new Floor, resets layout and Entities given current floor number (0 to 4, inclusive) and reference file.
    // If Player character location is specified in input file, returns Cell * for location. Otherwise, nullptr.
    Cell *generate(int floorNum, std::string filename = "defaultfloor.txt");
    // Randomly populates floor with Potions, Gold, and Enemies (In that order).
    void populate(int seed);
    // Checks each Entity in the floor and adds their protectors based on the floor layout.
    void addProtectors();
    // Update existing Floor cell-by-cell. Returns a message describing the results.
    std::string update();

    // set compass to enemy
    void set_compass(Cell *);
    // Basic Destructor.
    ~Floor();

    // Display given Floor to output.
    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};

#endif
