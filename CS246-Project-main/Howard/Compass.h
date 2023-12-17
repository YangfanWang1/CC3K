#ifndef H_COMPASS_H
#define H_COMPASS_H
#include "Entity.h"
#include "Item.h"
class Cell;
class Compass : public Item {
   protected:
    Cell* stair;

   public:
    Compass(Cell* stair);
    void acquire(Player*) override;
};
#endif
