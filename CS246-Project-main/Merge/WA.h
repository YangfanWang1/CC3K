#ifndef H_WA_H
#define H_WA_H
#include "Potion.h"
// WA is for Weaken Attack, which decrease ATK for 5 after consumed.
class WA : public Potion {
   private:
    static bool used;

   public:
    WA(bool hard, Cell* cell);
    bool get_used() override;
    void apply(Player* PC) override;
    static void reset_used();
};
#endif
