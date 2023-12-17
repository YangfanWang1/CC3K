# ifndef ORC_H
# define ORC_H

# include "Player.h"

class Orc : public Player{
    public:
        Orc(bool hard,Cell* currentCell);
        int getGold() override;
        void setGold(int n) override;
        int getScore() override;
        std::string getType() override;
        ~Orc();
};

# endif
