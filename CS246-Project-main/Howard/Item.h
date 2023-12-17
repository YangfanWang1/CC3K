#ifndef H_ITEM_H
#define H_ITEM_H
#include "Entity.h"

class Cell;
class Player;
class Entity;
class Item : public Entity {
    public:
        
    virtual void acquire(Player*) = 0;
};
#endif
