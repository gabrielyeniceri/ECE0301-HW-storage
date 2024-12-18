#include "Flora.hpp"

const int Flora::PHOTO_ENERGY = 5;
const int Flora::GROW_ENERGY = 20;
const int Flora::MOVES = 4;

Flora::Flora()
    : energy(PHOTO_ENERGY), direction_index(0) 
{
    //initial is left
}

Flora::Flora(int start_energy)
    : energy(start_energy), direction_index(0)
{
   // initial is left
}

AgentType Flora::get_type() const {
    return AgentType::VEGETATION;
}

int Flora::get_energy() const {
    return energy;
}

void Flora::energize(int amt) {
    // increses energy
    energy += PHOTO_ENERGY + amt;
}

Direction Flora::action() const {
    // 0 left, 1 up, 2 right, 3 down
    switch (direction_index) {
        case 0: return Direction::LEFT;
        case 1: return Direction::UP;
        case 2: return Direction::RIGHT;
        case 3: return Direction::DOWN;
        default: return Direction::LEFT;
    }
}

Direction Flora::next_action() {
    // moves to the next direction
    direction_index = (direction_index + 1) % MOVES;
    return action();
}

bool Flora::can_act() const {
    return energy > GROW_ENERGY;
}

bool Flora::act() {
    if (!can_act()) {
        return false;
    }
//if there's enough energy it updates after growing
    energy -= GROW_ENERGY;
    next_action();
    return true;
}
