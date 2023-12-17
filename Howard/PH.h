#ifndef H_PH_H
#define H_PH_H
#include "Potion.h"

class PH : public Potion {
    PH();
    void apply(Player* PC) override;
};
#endif
