#include "Simulator.hpp"

#include "bitmap.hpp"
#include <stdexcept>

/* Helper methods */
Location Simulator::loc_from_direction(Location loc, Direction dir)
{
    Location newloc = loc;
    switch (dir) {
        case LEFT:
            newloc.col--;
            break;
        case UP:
            newloc.row--;
            break;
        case RIGHT:
            newloc.col++;
            break;
        case DOWN:
            newloc.row++;
            break;
    }
    return newloc;
}

void Simulator::update_flora(Location loc)
{   
    Agent* agent = simgrid.get_cell(loc);
    if (!agent || agent->get_type() != VEGETATION) {
        return; // empty
    }

    Flora* flora = dynamic_cast<Flora*>(agent);
    if (!flora) {
        return; // safety check
    }

    // if it cant act then it energizes with 0
    if (!flora->can_act()) {
        flora->energize(0);
        return;
    }

    // flora can grow
    Direction start_dir = flora->action();
    Direction current_dir = start_dir;
    bool grown = false;

    for (int i = 0; i < Flora::MOVES; i++) {
        Location target = loc_from_direction(loc, current_dir);
        
        // out of bounds checker, if its out of range it is treated as an invalid direction
        bool valid = true;
        try {
            simgrid.get_cell(target); 
        } catch (std::out_of_range&) {
            valid = false;
        }

        if (valid && simgrid.get_cell(target) == nullptr) {
            // if the empty cell is found it creates new flora
            simgrid.set_cell(target, new Flora());
            // updates and reduces energy
            flora->act();
            grown = true;
            break;
        } else {
            // invalid or occupied it tries new direction
            current_dir = flora->next_action();
        }
    }

    // it does nothing if no place to grow is found
}

void Simulator::update_prey(Location loc)
{
    Agent* agent = simgrid.get_cell(loc);
    if (!agent || agent->get_type() != PREY) {
        return; // not prey or empty
    }

    Prey* prey = dynamic_cast<Prey*>(agent);
    if (!prey) {
        return;
    }

    // it dies if the energy level is zero
    if (prey->get_energy() == 0) {
        simgrid.set_cell(loc, nullptr);
        return;
    }


    Direction start_dir = prey->action();
    Direction current_dir = start_dir;
    bool moved = false;

    for (int i = 0; i < Prey::MOVES; i++) {
        Location target = loc_from_direction(loc, current_dir);
        bool valid = true;
        Agent* occupant = nullptr;
        try {
            occupant = simgrid.get_cell(target); 
        } catch (std::out_of_range&) {
            valid = false;
        }

        if (valid) {
            if (occupant == nullptr) {
                if (simgrid.move(loc, target)) {
                    prey->act(); 
                    moved = true;
                    break;
                }
            } else {
                AgentType otype = occupant->get_type();
                if (otype == VEGETATION) {
                    // eats to get energy
                    Flora* veg = dynamic_cast<Flora*>(occupant);
                    int veg_energy = (veg) ? veg->get_energy() : 0;
                    simgrid.set_cell(target, nullptr);
                    if (simgrid.move(loc, target)) {
                        prey->energize(veg_energy);
                        prey->act(); //reduce energy and update direction
                        moved = true;
                        break;
                    } else {
                      //just in case
                    }
                } else if (otype == PREY) {
                    current_dir = prey->next_action();
                    continue;
                } else {
                    current_dir = prey->next_action();
                    continue;
                }
            }
        } else {
            // if out of bounds try another direction
            current_dir = prey->next_action();
            continue;
        }
    }

// after all directions are tried if no move was made nothing happens
}

void Simulator::update_predator(Location loc)
{
// Bonus
}

/* Public members */

Simulator::Simulator() 
{
}

Simulator::Simulator(int start_size)
{
    simgrid.resize(start_size); // Grid should throw with invalid size
}

int Simulator::size() const
{
    return simgrid.get_size();
}

AgentType Simulator::get_type(Location loc) const
{
    Agent* agent_ptr = nullptr;
    try {
        agent_ptr = simgrid.get_cell(loc);
    } catch (std::out_of_range&) {
        return NONE; // out of range means no valid cell
    }

    if (agent_ptr == nullptr) {
        return NONE;
    }
    return agent_ptr->get_type();
}

bool Simulator::set(Location loc, AgentType atype)
{
    if (simgrid.get_cell(loc) != nullptr) {
        return false;
    }
    Agent* element = nullptr;
    switch (atype) {
        case VEGETATION:
            element = new Flora();
            break;
        case PREY:
            element = new Prey();
            break;
        case PREDATOR:
            element = new Predator();
            break;
        case NONE:
            return false;
    }
    simgrid.set_cell(loc, element);
    return true;
}

bool Simulator::remove(Location loc)
{
    if (get_type(loc) == NONE) {
        return false;
    }
    simgrid.set_cell(loc, nullptr);
    return true;
}

void Simulator::clear()
{   
    simgrid.clear();
}

bool Simulator::energize(Location loc, int energy)
{
    Agent* a = nullptr;
    try {
        a = simgrid.get_cell(loc);
    } catch (std::out_of_range&) {
        return false;
    }
    if (a == nullptr) {
        return false;
    }
    a->energize(energy);
    return true;
}

void Simulator::update()
{
    int sz = simgrid.get_size();
        // updates once per step
    for (int r=0; r<sz; r++) {
        for (int c=0; c<sz; c++) {
            Location loc {r,c};
            AgentType type = get_type(loc);
            switch (type) {
                case VEGETATION:
                    update_flora(loc);
                    break;
                case PREY:
                    update_prey(loc);
                    break;
                case PREDATOR:
                    update_predator(loc);
                    break;
                case NONE:
                    break;
            }
        }
    }
}

bool Simulator::done() const
{
    int sz = simgrid.get_size();
    for (int r=0; r<sz; r++) {
        for (int c=0; c<sz; c++) {
            Location loc {r,c};
            AgentType t = get_type(loc);
            if (t == PREY || t == PREDATOR) {
                return false;
            }
        }
    }
    return true;
}

bool Simulator::export_image(std::string outfile)
{
    int sz = simgrid.get_size();
    RGBPIXEL* image_data = new RGBPIXEL[sz*sz];

    AgentType type;
    int index;
    for (int r=0; r<sz; r++) {
        for (int c=0; c<sz; c++) {
            type = get_type(Location{r,c});
            index = r*sz + c;
            switch (type) {
                case VEGETATION:
                    image_data[index] = GREEN;
                    break;
                case PREY:
                    image_data[index] = BLUE;
                    break;
                case PREDATOR:
                    image_data[index] = RED;
                    break;
                case NONE:
                    if ((r+c)%2 == 0) {
                        image_data[index] = WHITE;
                    } else {
                        image_data[index] = BLACK;
                    }
                    break;
            }
        }
    }

    RGBIMAGEDATA export_data {image_data, sz, sz};
    bool success = export_bmp(export_data, outfile);

    delete [] image_data;

    return success;
}
