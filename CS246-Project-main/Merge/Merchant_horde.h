#ifndef H_Merchant_HORDE
#define H_Merchant_HORDE
#include "Treasure.h"

class Merchant_horde : public Treasure {
   public:
   Merchant_horde( bool hard, Cell* currentCell,Entity* protector=nullptr);
   std::string getType() override;
};
#endif
