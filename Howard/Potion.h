#ifndef H_POTION_H
#define H_POTION_H
#include "Entity.h"
#include <string>
class Player;
class Potion : public Entity {
   protected:
    //name of the Potion
       std::string type;
       //Has PC consumed it ,by default it's false
    bool used=false;

   public:
    Potion(std::string type,bool used=false);
    //Mutate the effect of PC
    void virtual apply(Player * PC) = 0;
    // I've added a mutator here for PC to change present field of potion
    void set_used(bool);
   virtual ~Potion()=default;
   


};
#endif
