#include "Character.h"
#include "Auxiliaries.h"
#include "Game.h"
#include "Exceptions.h"

using namespace game_ns;

Character& Character::operator=(const Character& other) {
    if(this == &other)
        return *this;
    
    this->health = other.health;
    this->ammo = other.ammo;
    this->range = other.range;
    this->power = other.power;
    this->team = other.team;

    return *this;
}

bool Character::isMoveLegal(int num_of_steps) {
    if (num_of_steps <= this->range){
        return true;
    }
    return false;
}

bool Character::outOfAmmo() {
    return (this->ammo == 0);
}

void Character::updateHealth(int n) {
    this->health += n; 
}  

units_t Character::getHealth() {
    return this->health; 
}

Team Character::getTeam() {
    return this->team;
}

units_t Character::getRange() {
    return this->range;
}

units_t Character::getPower() {
    return this->power;
}

units_t Character::getAmmo() {
    return this->ammo;
}

void Character::reduceAmmo(int n) {
    this->ammo -= n;
}
