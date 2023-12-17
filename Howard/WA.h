#ifndef H_WA_H
#define H_WA_H
#include "Potion.h"

class WA : public Potion {
    WA();
    void apply(Player* PC) override;
};
#endif
