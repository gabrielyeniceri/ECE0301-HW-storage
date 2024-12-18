#include "Prey.hpp"
#include <algorithm>

const int Prey::MOVES = 2;
const int Prey::MOVE_ENERGY = 5;

Prey::Prey()
    : energy(4 * MOVE_ENERGY), direction_index(0)
{
   //initial up direction
}

Prey::Prey(int start_energy)
    : energy(start_energy), direction_index(0)
{
   //initial up direction
}

AgentType Prey::get_type() const {
    return AgentType::PREY;
}

int Prey::get_energy() const {
    return energy;
}

void Prey::energize(int amt) {
    energy += amt;
}

Direction Prey::action() const {
    // 0 up, 1 left
    switch (direction_index) {
        case 0: return Direction::UP;
        case 1: return Direction::LEFT;
        default: return Direction::UP; 
    }
}

Direction Prey::next_action() {
    // toggles between up and left
    direction_index = (direction_index + 1) % MOVES;
    return action();
}

bool Prey::can_act() const {
    return energy > 0;
}

bool Prey::act() {
    if (!can_act()) {
        return false;
    }

    // can move if it has more than zero energy, but it cannot go below 0
    energy = std::max(energy - MOVE_ENERGY, 0);
    next_action();
    return true;
}
