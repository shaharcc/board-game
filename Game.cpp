#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Auxiliaries.h"
#include "Game.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include "Exceptions.h"
#include "Character.h"

using namespace mtm;

const string empty_cell = " ";


Game::Game(int height, int width): height(height), width(width)
{
    if(height < 0 || width < 0){
        throw IllegalArgument();
    }
    this->board = makeBoard(height, width);
}

Game::Game(const Game& other): height(other.height), width(other.width)
{
    std::vector<std::shared_ptr<Character>>::const_iterator iterator = other.board.begin();
    while(iterator != other.board.end())
    {
        if(*iterator == nullptr)
            board.push_back(nullptr);
        std::shared_ptr<Character> character((*iterator)->clone());
        board.push_back(character);
        iterator++;
    }
}

Game &Game::operator=(const Game& other) 
{
    if(this == &other)
        return *this;
    this->width = other.width;
    this->height = other.height;

    /*NOT FINISHED:
    NEED TO COPY THE BOARD
    by insert? push_back? else?
    */

    return *this;
}

void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
{
    if(!checkIfCellInBoard(coordinates))
        throw IllegalCell();
    int position = findPosition(coordinates);
    if(!checkIfCellIsEmpty(position))
        throw CellOccupied();

    std::vector<std::shared_ptr<Character>>::iterator iterator = board.begin();
    std::advance(iterator, position);
    board.insert(iterator, character);
}

static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                units_t health, units_t ammo, units_t range, units_t power)
{
    if(health < 1 || ammo < 0 || range < 0 || power < 0)
        throw IllegalArgument();

    switch (type){
        case SOLDIER:
            return std::shared_ptr<Character>(new Soldier(health, ammo, range, power, team));
        case SNIPER:
            return std::shared_ptr<Character>(new Sniper(health, ammo, range, power, team));
        case MEDIC:
            return std::shared_ptr<Character>(new Medic(health, ammo, range, power, team));
    }
}

void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(!checkIfCellInBoard(src_coordinates) || !checkIfCellInBoard(dst_coordinates))
        throw IllegalCell();
    int src_position = findPosition(src_coordinates);
    if(checkIfCellIsEmpty(src_position))
        throw CellEmpty();
    int dst_position = findPosition(dst_coordinates);
    if(!checkIfCellIsEmpty(dst_position))
        throw CellOccupied();

    int total_steps = getTotalSteps(src_coordinates, dst_coordinates);
    std::shared_ptr<Character> curr_character = board.at(src_position);
    if(!curr_character->isMoveLegal(total_steps))
        throw MoveTooFar();

    std::vector<std::shared_ptr<Character>>::iterator src_iterator, dst_iterator;
    src_iterator = board.begin();
    advance(src_iterator, src_position);
    dst_iterator = board.begin();
    advance(dst_iterator, dst_position);

    std::swap(src_iterator, dst_iterator);
}

void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(!checkIfCellInBoard(src_coordinates) || !checkIfCellInBoard(dst_coordinates))
        throw IllegalCell();
    int src_position = findPosition(src_coordinates);
    if(checkIfCellIsEmpty(src_position))
        throw CellEmpty();
    
    std::shared_ptr<Character> curr_character = board.at(src_position);
    int total_steps = getTotalSteps(src_coordinates, dst_coordinates);

    if (!curr_character->isMoveLegal(total_steps) || 
        !curr_character->isDirectionLegal(src_coordinates, dst_coordinates)){
        throw OutOfRange();
    }
}


void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(!checkIfCellInBoard(src_coordinates) || !checkIfCellInBoard(dst_coordinates))
        throw IllegalCell();
    int attacker_position = findPosition(src_coordinates);
    if(checkIfCellIsEmpty(attacker_position))
        throw CellEmpty();

    std::shared_ptr<Character> curr_character = board.at(attacker_position);
    int total_steps = getTotalSteps(src_coordinates, dst_coordinates);
    if (!curr_character->isMoveLegal(total_steps) || 
        !curr_character->isDirectionLegal(src_coordinates, dst_coordinates))
        throw OutOfRange();
    int attacked_postion = findPosition(dst_coordinates);
    std::shared_ptr<Character> attacked = board.at(attacked_postion);
    curr_character->makeAttack(board, src_coordinates, dst_coordinates, 
                            attacker_position, attacked_postion, attacked);
    //check if out of game for all the characters involved

    /* makeAttack needs to check for the exceptions:
        throw OutOfRange();
        throw OutOfAmmo();
        throw IllegalTarget();
    */
}


void Game::reload(const GridPoint &coordinates)
{
    int position = findPosition(coordinates);
    if(!checkIfCellInBoard(coordinates)){
        throw IllegalCell();
    }
    if(checkIfCellIsEmpty(position)){
        throw CellEmpty();
    }
    std::shared_ptr<Character> curr_character = board.at(position);
    curr_character->reloadAmmo();
}

namespace mtm{
    ostream& operator<<(ostream& os, const Game& game)
    {
        std::string symbol;

        for(const std::shared_ptr<Character> &iterator : game.board){
            if(iterator == nullptr)
                symbol += empty_cell;
            else
                symbol += iterator->getSymbol();
        }
        std::shared_ptr<Character> iterator = *game.board.end();
        string end = iterator->getSymbol(); //or '/0'
        return printGameBoard(os, symbol.c_str(), end.c_str(), game.width);
        
    }
}

bool Game::isOver(Team* winningTeam=NULL) const
{
    int i = 0;
    while(board.at(i) == nullptr)
        i++; //first appearance of a player
    if((*board.at(i)).getTeam() == CROSSFITTERS){
        for(; i < width*height; i++){
            if(board.at(i) != nullptr && (*board.at(i)).getTeam() != CROSSFITTERS)
                return false;
        }
        *winningTeam = CROSSFITTERS;
        return true;
    }
    else{
        for(; i < width*height; i++){
            if(board.at(i) != nullptr && (*board.at(i)).getTeam() != POWERLIFTERS)
                return false;
        }
        *winningTeam = POWERLIFTERS;
        return true;
    }
}

std::vector<std::shared_ptr<Character>> Game::makeBoard(int height, int width)
{
    std::vector<std::shared_ptr<Character>> board;
    for(int i = 0; i < height * width; i++)
        board.push_back(nullptr);
    return board;
}

int Game::findPosition(const GridPoint &coordinates)
{
    int position = this->width * coordinates.row + coordinates.col;
    return position;
}

bool Game::checkIfCellInBoard(const GridPoint & coordinates)
{
    if((coordinates.row < 0 || coordinates.row > this->height - 1) ||
       (coordinates.col < 0 || coordinates.col > this->width - 1))
       return false;
    return true;
}

bool Game::checkIfCellIsEmpty(int position)
{
    if(this->board[position] == nullptr)
        return true;
    return false;
}

int Game::getTotalSteps(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    int total_steps = abs(dst_coordinates.row - src_coordinates.row) + 
                      abs(dst_coordinates.col - src_coordinates.col);
    return total_steps;
}

