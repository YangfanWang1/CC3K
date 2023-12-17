#ifndef VAMPIRE_H
#define VAMPIRE_H

# include "Enemy.h"

class Vampire:public Enemy{
    public:
        Vampire(bool hard=false,Cell* currentCell=nullptr, Cell* stair = nullptr);
        char display_char() override;
        std::string getType() override;
        ~Vampire();
};

#endif
