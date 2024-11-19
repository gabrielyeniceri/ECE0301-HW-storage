#ifndef _PREDATOR_HPP
#define _PREDATOR_HPP

#include "Agent.hpp"

// BONUS

class Predator : public Agent {
    public:
        static const int MOVES;
        static const int MOVE_ENERGY;
        Predator();
        Predator(int start_energy);
        AgentType get_type() const;
        int get_energy() const;
        void energize(int e);
        Direction action() const;
        Direction next_action();
        bool can_act() const;
        bool act();
};

#endif