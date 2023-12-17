# ifndef DRAGON_H
# define DRAGON_H

# include "Enemy.h"

class Dragon:public Enemy{
    Cell* aggroTrigger;
    public:
        Dragon(bool hard=false,Cell* currentCell=nullptr, Cell* stair=nullptr);
        void checkForProtectors() override;
        void setAggroTrigger(Cell *cell);
        void kill(Player*) override;
        std::string update() override;
        char display_char() override;
        std::string getType() override;
        ~Dragon();
};

# endif
