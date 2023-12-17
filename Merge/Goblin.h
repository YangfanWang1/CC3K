#ifndef GOBLIN_H
#define GOBLIN_H

# include "Enemy.h"

class Goblin:public Enemy{
    public:
        Goblin(bool hard=false,Cell* currentCell=nullptr, Cell* stair=nullptr);
        char display_char() override;
        std::string getType() override;
        ~Goblin();
};

#endif
