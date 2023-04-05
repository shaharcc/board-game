#include <vector>
#include <memory>
#include "Character.h"
#include "Auxiliaries.h"

namespace game_ns {   
    class Medic : public Character
    {
        public:
        Medic(units_t health, units_t ammo, const units_t range, const units_t power, Team team):
        Character(health, ammo, range, power, team){};
        ~Medic() = default;
        Medic(const Medic& medic)= default;
        Medic* clone() const;
        void reloadAmmo();
        std::string getSymbol() override;
        bool isRangeLegal(int num_of_steps);
        bool isDirectionLegal(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void makeAttack(std::vector<std::shared_ptr<Character>> board, const GridPoint & src_coordinates,
                        const GridPoint & dst_coordinates, int attacker_position, int attacked_postion, std::shared_ptr<Character> attacked);
    };
}
