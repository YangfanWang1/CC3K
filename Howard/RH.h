#ifndef H_RH_H
#define H_RH_H
#include "Potion.h"

class RH : public Potion {
    RH();
    void apply(Player* PC) override;
};
#endif
