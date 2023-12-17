#ifndef H_TREASURE_H
#define H_TREASURE_H
#include "Entity.h"

class Treasure : public Entity {
   protected:
    int value;

   public:
    Treasure(int value,Entity* protector, bool hard, Cell* currentCell);
    //getter of treasure value for polymorphism
    int getValue();
    virtual ~Treasure()=default;
    char display_char() override;
};
#endif
