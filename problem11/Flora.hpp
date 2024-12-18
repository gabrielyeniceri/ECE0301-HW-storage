#ifndef _FLORA_HPP
#define _FLORA_HPP

#include "Agent.hpp"

class Flora : public Agent {
private:
    int energy;
    int direction_index;

public:
    static const int PHOTO_ENERGY;
    static const int GROW_ENERGY;
    static const int MOVES;

    Flora();

    // this is initial energy
    Flora(int start_energy);

    // returns the vegetation
    virtual AgentType get_type() const override;

    // returns current energy
    virtual int get_energy() const override;

    // adds photosynth energy
    virtual void energize(int amt) override;

    // returns current direction
    virtual Direction action() const override;

    // returns next direction after updating
    virtual Direction next_action() override;

    // checks if it can act
    virtual bool can_act() const override;

    // reduce energy if it can act
    virtual bool act() override;
};

#endif
