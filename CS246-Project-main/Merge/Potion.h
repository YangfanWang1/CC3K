#ifndef H_POTION_H
#define H_POTION_H
#include <string>

#include "Elf.h"
#include "Entity.h"
#include "Player.h"
class Player;

class Potion : public Entity {
   protected:
    // name of the Potion
    std::string type;

   public:
    Potion(std::string type, bool hard, Cell* currentCell, Entity* protector = nullptr);
    std::string getType() override;
    // Mutate the effect of PC
    void virtual apply(Player* PC) = 0;
    // Accessor for used field of Potion.
    // used bool will be set when called subclasses of potion's apply() function
    virtual bool get_used();
    virtual ~Potion() = default;
    char display_char();
};
#endif
