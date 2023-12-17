#ifndef WEREWOLF_H
#define WEREWOLF_H

#include "Enemy.h"

class Werewolf : public Enemy {
   public:
    Werewolf(bool hard = false, Cell* currentCell = nullptr, Cell* stair = nullptr);
    char display_char() override;
    std::string getType() override;
    ~Werewolf();
};

#endif
