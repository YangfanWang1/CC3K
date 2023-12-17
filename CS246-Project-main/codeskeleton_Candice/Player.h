# ifndef PLAYER_H
# define PLAYER_H

# include <string>
# include <memory>
# include <vector>
# include <string>
//# include "Entity.h"
class Entity;
class Enemy;
class Potion;
class Treasure;

class Player:public Entity{
    protected:
        std::vector<std::string> usedPotionTypes;
        bool barrier_suit;
        int baseatk;
        int basedef;
        int def;
        int maxhp;
        int gold;
    public:
        // modify my treasure
        collectTreasure(Treasure* t);
        void setBarrier(bool a);
        int getGold();
        void setGold(int n);
        void attackEnemy(Enemy* e);
        void kill();
        virtual ~Player() = 0;
};

# endif
