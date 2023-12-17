#ifndef H_BARRIER_H
#define H_BARRIER_H
#include "Item.h"

class Cell;
class Player;

class Barrier : public Item {
    public:
    Barrier(Cell* currentCell);
    void acquire(Player*) override;
    char display_char() override;
    std::string getType() override;
};

#endif
