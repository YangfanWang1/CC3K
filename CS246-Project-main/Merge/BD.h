#ifndef H_BD_H
#define H_BD_H
#include "Potion.h"

class Player;
// BD is for Boost Defense, which increase DEF for 5 after consumed.
class BD : public Potion {
   private:
    static bool used;

   public:
    BD(bool hard, Cell* cell);
    bool get_used() override;
    void apply(Player* PC) override;
    static void reset_used();
};
#endif
