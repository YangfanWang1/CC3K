#ifndef H_NORMAL_H
#define H_NORMAL_H
#include "Treasure.h"

class Normal : public Treasure {
   public:
     Normal( bool hard, Cell* currentCell,Entity* protector=nullptr);
     std::string getType() override;
};
#endif
