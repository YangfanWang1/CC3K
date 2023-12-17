#ifndef H_ITEM_H
#define H_ITEM_H
#include "Entity.h"
#include "Player.h"

class Cell;

class Item : public Entity {
   public:
    Item(Cell* currentCell);
    // acquire means to apply effects of its subclasses when PC picked an item
    virtual void acquire(Player* PC) = 0;
};

#endif
