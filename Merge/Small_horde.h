#ifndef H_Small_H
#define H_Small_H
#include "Treasure.h"

class Small : public Treasure {
   public:
    Small(bool hard, Cell* currentCell, Entity* protector = nullptr);
    std::string getType() override;
};

#endif
