#include <vector>
#include <memory>
#include "Character.h"
#include "Auxiliaries.h"

namespace game_ns {
    class Soldier : public Character
    {
        public:
        Soldier(units_t health, units_t ammo, const units_t range, const units_t power, Team team):
        Character(health, ammo, range, power, team){};
        ~Soldier() = default;
        Soldier(const Soldier& soldier)= default;
        Soldier* clone() const;
        void reloadAmmo();
        bool isRangeLegal(int num_of_steps);  
        std::string getSymbol() override;
        bool isDirectionLegal(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void makeAttack(std::vector<std::shared_ptr<Character>> board, const GridPoint & src_coordinates,
                        const GridPoint & dst_coordinates, int attacker_position, int attacked_postion, std::shared_ptr<Character> attacked);
    };
}
