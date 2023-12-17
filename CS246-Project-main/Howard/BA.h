#ifndef H_BA_H
#define H_BA_H
#include "Potion.h"
#include "Entity.h"
class BA : public Potion {
    BA();
    void apply(Player* PC) override;
};
#endif
