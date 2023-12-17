#ifndef MERCHANT_H
#define MERCHANT_H
#include <string>

#include "Compass.h"
#include "Enemy.h"

class Merchant : public Enemy {
    static bool M_hostile;

   public:
    Merchant(bool hard, Cell* currentCell, Cell* stair = nullptr);
    static bool get_hostile();
    static void set_hostile(bool hostile);
    std::string update() override;
    char display_char() override;
    std::string getType() override;
    ~Merchant() = default;
    void kill(Player* PC) override;
};

#endif
