# include "Merchant.h"
#include <iostream>
#include <mermory>
#include "Merchant_horde.h"
bool Merchant::M_hostile = false;

Merchant::Merchant(bool hard, Cell* currentCell, stair) : 
Enemy{30, 70, 5, nullptr, hard, currentCell, stair}{};

string Merchant::getType(){
    return "Merchant";
}
void Merchant::set_hostile(bool hostile){
    M_hostile=hostile;
}

ostream& Merchant::operator<<(ostream& out, Merchant& m){
             out<<"M";
            return out;
        }

void Merchant::update(){
    Entity::seed++;
    if(M-hostile==true){
    for(int i=0; i < currentCell->getBlock().size();i++){
        if((getType()=="Player")){
                attackPlayer(currentCell->getBlock().at(i));
                return;
}}
}
    moveRandom();
    };

void purchasePotion(Player* PC, string Potion){
    std::cout<<"yooooo, merchant can't sell now!"<<endl;
}

void Merchant::kill(){
    //unwind myself from cell and get it to horde
    currentCell.setEntity(shared_ptr<Merchant_horde>=make_shared<Merchant_horde>Merchant_horde());
}
