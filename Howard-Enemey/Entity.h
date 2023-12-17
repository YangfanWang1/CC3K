#ifndef H_ENTITY_H
#define H_ENTITY_H
//#include "Cell.h"
class Cell;
//#include "Cell.h"
class Entity {
    protected:
    int HP;
    int ATK;
    int DEF;
    //if it's an item, this is the pointer of it's holder
    Entity* protector;
    //has the hard command added? if so we are playing with "hard" dlc.
    bool hard;
    //the cell Entity is on
    
    Cell* currentCell;
    //seed for random generation
    static int seed;
    public:
    Entity(int HP=1,int ATK=0,int DEF=0, Entity* protector=nullptr, bool hard=false,Cell* currentCell=nullptr);
    int getHP();
    int getATK();
    int getDEF();
  virtual int getGold()=0;
    Entity* getProtector();
    Cell* getCurrentCell();
    void setHP(int HP);
    void setATK(int ATK);
    void setDEF(int DEF);
    void setProtector(Entity*);
    void setCurrentCell(Cell*);
    //I'm leaving kill in entity do nothing, so this is an invariant that all sub-classes of entity must write it's implementation of kill to override it
    void virtual kill();
    virtual ~Entity()=default;
};
#endif
