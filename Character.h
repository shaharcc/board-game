#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "Auxiliaries.h"

namespace game_ns {
    class Character {
    protected:
        units_t health, ammo, range, power;
        Team team;
    public:
        Character() = delete;
        Character(units_t health, units_t ammo, const units_t range, const units_t power, Team team):
                  health(health), ammo(ammo), range(range), power(power), team(team){}
        virtual ~Character() = default;
        Character(const Character& character) = default;
        virtual Character& operator=(const Character& other);
        virtual Character* clone() const = 0;
        virtual std::string getSymbol() = 0;

        virtual void reloadAmmo() = 0;
        virtual void reduceAmmo(int n); 
        virtual bool outOfAmmo();
        virtual void updateHealth(int n); 

        virtual units_t getHealth();
        virtual Team getTeam();
        virtual units_t getRange();
        virtual units_t getPower();
        virtual units_t getAmmo();

        virtual bool isMoveLegal(int num_of_steps);  
        virtual bool isDirectionLegal(const GridPoint & src_coordinates, const GridPoint & dst_coordinates) = 0 ;
        virtual bool isRangeLegal(int num_of_steps) = 0 ;  
        virtual void makeAttack(std::vector<std::shared_ptr<Character>> board, const GridPoint & src_coordinates,
                                const GridPoint & dst_coordinates, int attacker_position, int attacked_postion,
                                std::shared_ptr<Character> attacked) = 0; 
    };
}

#endif //CHARACTER_H
