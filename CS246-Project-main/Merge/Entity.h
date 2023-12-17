#ifndef H_ENTITY_H
#define H_ENTITY_H
#include <vector>
#include "Cell.h"

class Entity {
   protected:
    int HP;
    int ATK;
    int DEF;
    // if it's an item, this is the pointer of it's holder,else nullptr
    Entity* protector;
    //enmey's protecting field(mainly for dragon of it's gold and barrier)
    std::vector<Entity *> protectedList;
    //flag we set for hard mode, sadly didn't have enough time to implement
    bool hard;
    // the cell Entity is on
    Cell* currentCell;
    //seed for random movement
    static int seed;

   public:
    Entity(int HP = 1, int ATK = 0, int DEF = 0, Entity* protector = nullptr, bool hard = false, Cell* currentCell = nullptr);
    int getHP();
    int getATK();
    int getDEF();
    Entity* getProtector();
    Cell* getCurrentCell();
    void setHP(int HP);
    void setATK(int ATK);
    void setDEF(int DEF);
    void setProtector(Entity*);
    void setCurrentCell(Cell*);
    virtual std::string update();
    // This function gets overridden for any classes which need to set protectors.
    virtual void checkForProtectors();
    void deleteProtected(Entity*);
    virtual std::string getType();
    // I'm leaving kill in entity do nothing, so this is an invariant that all sub-classes of entity must write it's implementation of kill to override it
    void virtual kill();
    virtual ~Entity() = default; 
    virtual char display_char();
};

#endif
