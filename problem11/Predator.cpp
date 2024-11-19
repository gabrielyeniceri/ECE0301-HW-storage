#include "Predator.hpp"

const int Predator::MOVES = 4;
const int Predator::MOVE_ENERGY = 7;

// BONUS

Predator::Predator() 
{
}

Predator::Predator(int start_energy) 
{
}

AgentType Predator::get_type() const
{
    return NONE;
}

int Predator::get_energy() const
{
    return 0;
}

void Predator::energize(int e)
{
}

Direction Predator::action() const
{
    return RIGHT;
}

Direction Predator::next_action()
{
    return RIGHT;
}


bool Predator::can_act() const
{
    return false;
}

bool Predator::act()
{
    return false;
}