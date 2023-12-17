#ifndef H_BD_H
#define H_BD_H
#include "Potion.h"

class BD : public Potion {
    BD();
    void apply(Player* PC) override;
};
#endif
