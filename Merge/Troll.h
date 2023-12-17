#ifndef TROLL_H
#define TROLL_H

# include "Enemy.h"

class Troll:public Enemy{
    public:
        Troll(bool hard=false,Cell* currentCell=nullptr, Cell* stair=nullptr);
        char display_char() override;
        std::string getType() override;
        ~Troll();
};

#endif
