#include "Sniper.h"
#include <cmath>
#include <vector>
#include <memory>
#include "Auxiliaries.h"
#include "Exceptions.h"

using namespace game_ns;

void Sniper::reloadAmmo() {
    this->ammo += 2;
}

bool Sniper::isRangeLegal(int num_of_steps) {
    if (num_of_steps <= this->range && num_of_steps >= ceil((this->range)/2)){
        return true;
    }
    return false;
} 

// can attack anywhere
bool Sniper::isDirectionLegal(const GridPoint & src_coordinates, const GridPoint & dst_coordinates) {
    return true;
}

Sniper* Sniper::clone() const {
    return new Sniper(*this);
}

void Sniper::makeAttack(std::vector<std::shared_ptr<Character>> board, const GridPoint & src_coordinates,
                        const GridPoint & dst_coordinates, int attacker_position, int attacked_postion, std::shared_ptr<Character> attacked) {
  
    if (this->team != attacked->getTeam()){
        throw IllegalTarget();
    }
    reduceAmmo(1);
    attack_counter++; 

    if (attack_counter%3 == 0){
        attacked->updateHealth(-2*(this->power));
        if (attacked->getHealth() == 0){
            attacked = nullptr;
            //board.erase(attacked_postion); // not good
        }
        attack_counter = 0; 
    }
    else {
        attacked->updateHealth(-1*(this->power));
        if (attacked->getHealth() == 0) {
            attacked = nullptr;
        }
    }
}

std::string Sniper::getSymbol() {
    if(this->team == CROSSFITTERS)
        return "s";
    else 
        return "S";
}
