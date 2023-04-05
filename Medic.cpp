#include "Medic.h"
#include <cmath>
#include <vector>
#include "Auxiliaries.h"
#include "Exceptions.h"


using namespace game_ns;

void Medic::reloadAmmo() {
    this->ammo += 5;
}

bool Medic::isRangeLegal(int num_of_steps) {
    return Medic::isMoveLegal(num_of_steps);
}

// can attack anywhere
bool Medic::isDirectionLegal(const GridPoint & src_coordinates, const GridPoint & dst_coordinates) {
    return true;
}

Medic* Medic::clone() const {
    return new Medic(*this);
}

void Medic::makeAttack(std::vector<std::shared_ptr<Character>> board, const GridPoint & src_coordinates,
                       const GridPoint & dst_coordinates, int attacker_position, int attacked_postion, std::shared_ptr<Character> attacked) {
    if (src_coordinates.row == dst_coordinates.row && src_coordinates.col == dst_coordinates.col){
        throw IllegalTarget();
    }
    if (attacked == nullptr){
        throw IllegalTarget(); 

    }
    if (this->team != attacked->getTeam() {
        reduceAmmo(1);
        attacked->updateHealth(-1*(this->power));
        if (attacked->getHealth() == 0){
            attacked = nullptr;
        }
    }
    else {
        attacked->updateHealth((this->power));
    }
}

std::string Medic::getSymbol() {
    if(this->team == CROSSFITTERS)
        return "m";
    else 
        return "M";
}
    
