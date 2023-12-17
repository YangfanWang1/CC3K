#ifndef H_WD_H
#define H_WD_H
#include "Potion.h"

class WD : public Potion {
   WD();
    void apply(Player* PC) override;
};
#endif
