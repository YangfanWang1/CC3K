#ifndef H_TREASURE_H
#define H_TREASURE_H
#include "Entity.h"

class Treasure : public Entity {
   protected:
    int value;

   public:
    Treasure(int value);
    int getValue();
    virtual ~Treasure()=default;
};
#endif
