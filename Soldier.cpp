#include "Soldier.h"
#include <cmath>
#include <vector>
#include "Auxiliaries.h"
#include "Exceptions.h"


using namespace mtm;

void Soldier::reloadAmmo()
{
    this->ammo += 3;
}

std::string Soldier::getSymbol()
{
    if(this->team == CROSSFITTERS)
        return "n";
    else 
        return "N";
}

bool Soldier::isRangeLegal(int num_of_steps)
{
    return Soldier::isMoveLegal(num_of_steps);
}  

//can attack only in staight lines
bool Soldier::isDirectionLegal(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if ((src_coordinates.row == dst_coordinates.row) || (src_coordinates.col == dst_coordinates.col)){
        return true;
    }
    return false;
}

Soldier* Soldier::clone() const
{
    return new Soldier(*this);
}


void Soldier::makeAttack(std::vector<std::shared_ptr<Character>> board, const GridPoint & src_coordinates,
                        const GridPoint & dst_coordinates, int attacker_position, int attacked_postion, std::shared_ptr<Character> attacked)
{
    reduceAmmo(1);
    
    if (this->getTeam() != attacked->getTeam()){
        attacked->updateHealth(-1*(this->power));

        if (attacked->getHealth() == 0){
            //board.erase(attacked_postion); // not good
            attacked = nullptr;
        }
    }
/*
    for (int i = 0; i < board.size(); i++){
        std::shared_ptr<Character> curr_character = board.at(i);
        if (curr_character == nullptr || this->getTeam() == curr_character->getTeam()){
            continue;
        }
        if (GridPoint::distance(dst_coordinates, //point2) <= ceil((this->range)/3 && GridPoint::distance() != 0))
        {
            curr_character->updateHealth(-1*(this->power)/2);
            if (curr_character->getHealth == 0){
                board.erase(board.begin()+i);
            }
        }
    }*/
}




    