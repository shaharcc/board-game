#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Auxiliaries.h"
#include "Character.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;

namespace game_ns {
    class Game {
        int height;
        int width;
        std::vector<std::shared_ptr<Character>> board;

        public:
            Game(int height, int width);
            ~Game() = default;
            Game(const Game& other);
            Game& operator=(const Game& other);
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                units_t health, units_t ammo, units_t range, units_t power);
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void reload(const GridPoint & coordinates);
            std::ostream& printGameBoard(std::ostream& os, const char* begin,
                const char* end, unsigned int width) const;
            bool isOver(Team* winningTeam=NULL) const;
            friend ostream& operator<<(ostream&, const Game&);
            
        private:
            std::vector<std::shared_ptr<Character>> makeBoard(int height, int width);
            int findPosition(const GridPoint &coordinates);
            bool checkIfCellInBoard(const GridPoint & coordinates);
            bool checkIfCellIsEmpty(int position);
            int getTotalSteps(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        
    };
}

#endif //GAME_H
