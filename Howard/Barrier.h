#ifndef H_BARRIER_H
#define H_BARRIER_H
#include "Entity.h"
#include "Item.h"
class Cell;

class Barrier : public Item {
    void acquire(Player*) override;
};
#endif
