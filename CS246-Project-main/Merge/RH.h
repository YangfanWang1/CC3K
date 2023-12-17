#ifndef H_RH_H
#define H_RH_H
#include "Potion.h"
// RH is for Restore Health, which increase HP for 5 after consumed.
class RH : public Potion {
   private:
    static bool used;
   public:
    RH(bool hard, Cell* cell);
    bool get_used() override;
    void apply(Player* PC) override;
    static void reset_used();
};
#endif
