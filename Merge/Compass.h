#ifndef H_COMPASS_H
#define H_COMPASS_H
#include "Entity.h"
#include "Cell.h"
#include "Item.h"

class Cell;

class Compass : public Item {
   protected:
    Cell* stair;

   public:
    Compass(Cell* currentCell, Cell* stair);
    
    void acquire(Player*) override;
    char display_char() override;
    std::string getType() override;
};
#endif
