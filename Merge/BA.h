#ifndef H_BA_H
#define H_BA_H
#include "Potion.h"

class Player;
// BA is for Boost Attack, which increase ATK for 5 after consumed.
class BA : public Potion {
   private:
    static bool used;

   public:
    BA(bool hard, Cell* cell);
    bool get_used() override;
    void apply(Player* PC) override;
    static void reset_used();
};

#endif
