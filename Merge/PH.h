#ifndef H_PH_H
#define H_PH_H
#include "Potion.h"

// PH is for Posion Health, which decrease health for 5 after consumed.

class PH : public Potion {
   private:
    static bool used;

   public:
    PH(bool hard, Cell* cell);
    bool get_used() override;
    void apply(Player* PC) override;
    static void reset_used();
};
#endif
