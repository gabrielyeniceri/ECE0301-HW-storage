#ifndef _PREY_HPP
#define _PREY_HPP

#include "Agent.hpp"

class Prey : public Agent {
private:
    int energy;
    int direction_index;

public:
    static const int MOVES;
    static const int MOVE_ENERGY;

    //starting energy = 4 * MOVE_ENERGY
    Prey();

    // Constructor for initial energy
    Prey(int start_energy);

    // returns agenttype
    virtual AgentType get_type() const override;

    // returns energy
    virtual int get_energy() const override;

    // adds energy
    virtual void energize(int amt) override;

    // returns current direction
    virtual Direction action() const override;

    // toggles direction
    virtual Direction next_action() override;

    // checks if the energy is above 0 returns true if it can act
    virtual bool can_act() const override;

    // update direction
    virtual bool act() override;
};

#endif
