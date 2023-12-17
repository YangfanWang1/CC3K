# ifndef HUMAN_H
# define HUMAN_H

# include "Player.h"

class Human:public Player{
    public:
        Human(bool hard=false,Cell* currentCell=nullptr);
        int getScore() override;
        std::string getType() override;
        ~Human();
};

# endif
