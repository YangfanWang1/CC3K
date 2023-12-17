#ifndef H_WD_H
#define H_WD_H
#include "Potion.h"
// WD is for Weaken Defense, which decrease DEF for 5 after consumed.
class WD : public Potion {
   private:
    static bool used;

   public:
    WD(bool hard, Cell* cell);
    bool get_used() override;
    void apply(Player* PC) override;
    static void reset_used();
};
#endif
