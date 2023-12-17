#ifndef H_Dragon_HORDE
#define H_Dragon_HORDE
#include "Treasure.h"

class Dragon_horde : public Treasure {
   public:
    Dragon_horde(bool hard, Cell* currentCell, Entity* protector = nullptr);
    std::string getType() override;
};

#endif
