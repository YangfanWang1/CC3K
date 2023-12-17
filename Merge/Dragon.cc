# include <sstream>
# include "Dragon.h"
# include "Barrier.h"
# include "Compass.h"
# include "Cell.h"
using  namespace std;

Dragon::Dragon(bool hard,Cell* currentCell, Cell* stair): Enemy{150,20,20,nullptr,hard,currentCell,stair} {}

void Dragon::checkForProtectors() {
    //check dragonhorde nearby, and set protector & aggrotrigger
    Entity *ent = nullptr;
    for(int i=0; i < currentCell->getWalkableBlock().size();i++){
        ent = currentCell->getWalkableBlock().at(i)->getEntity().get();
        if(ent && ent->getType()=="Dragon_horde"){
            setAggroTrigger(currentCell->getWalkableBlock().at(i));
            ent->setProtector(this);
            protectedList.emplace_back(ent);
            break;
        }
    }
    for(int i=0; i < currentCell->getWalkableBlock().size();i++){
        ent = currentCell->getWalkableBlock().at(i)->getEntity().get();
        if(ent && ent->getType()=="Barrier"){
            ent->setProtector(this);
            protectedList.emplace_back(ent);
            break;
        }
    }
}

void Dragon::setAggroTrigger(Cell *cell){
    aggroTrigger = cell;
};

string Dragon::update(){
    Entity::seed++;
    if(aggroTrigger) {
        for(int i=0; i < aggroTrigger->getBlock().size();i++){
            if (aggroTrigger->getBlock().at(i)->getEntity().get() == this) {
                continue;
            }
            std::shared_ptr<Player> PC = std::dynamic_pointer_cast<Player>(aggroTrigger->getBlock().at(i)->getEntity());
            if (PC && (PC->getType()=="Human" || PC->getType()=="Elf" || 
                       PC->getType()=="Dwarf" || PC->getType()=="Orc")) {
                ostringstream result;
                // check if dragon dies or not
                if (HP <= 0) {
                    kill(PC.get());
                    result << "D dies. ";
                } else {
                    int prevHP = PC->getHP();
                    bool attack_success = attackPlayer(PC.get());
                    if (attack_success) {
                        result << "D deals " << prevHP - PC->getHP() << " damage to PC";
                        if (PC->getBarrier()) {
                            result << " (Barrier suit equipped). ";
                        } else {
                            result << ". ";
                        }
                    } else {
                        result << "D attacks, but misses. ";
                    }
                }
                return result.str();
            }
        }
    }
    return string();
}

void Dragon::kill(Player* pc){
    if(this->getHP()<=0){
        setHP(0);
        // no gold drops
        // unbind myself from cell;
        currentCell->setEntity(nullptr);
        // set dragon horde's protector to nullptr
        for (int i = 0; i < protectedList.size(); ++i) {
            protectedList.at(i)->setProtector(nullptr);
        }
        //if I'm compass holder:
        if (stair != nullptr) {
            currentCell->setEntity(make_shared<Compass>(currentCell, stair));
        }
        else{
            return;
        }
    }
};

char Dragon::display_char(){
    return 'D';
}

std::string Dragon::getType() {
    return "Dragon";
}

Dragon::~Dragon(){};
