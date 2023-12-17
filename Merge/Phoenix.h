#ifndef PHOENIX_H
#define PHOENIX_H

# include "Enemy.h"

class Phoenix:public Enemy{
    public:
        Phoenix(bool hard=false,Cell* currentCell=nullptr, Cell* stair=nullptr);
        char display_char() override;
        std::string getType() override;
        ~Phoenix();
};

#endif
