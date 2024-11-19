#include "Simulator.hpp"

#include "bitmap.hpp"

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
    }
    return newloc;
}

void Simulator::update_flora(Location loc)
{   
    // TODO 
}


void Simulator::update_prey(Location loc)
{
    // TODO
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
    // TODO
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
    if (simgrid.get_cell(loc) == nullptr) {
        return false;
    }
    simgrid.get_cell(loc)->energize(energy);
    return true;
}

void Simulator::update()
{
    int size = simgrid.get_size();
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
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
    // TODO
    return false;
}

bool Simulator::export_image(std::string outfile)
{
    int size = simgrid.get_size();
    RGBPIXEL* image_data = new RGBPIXEL[size*size];

    AgentType type;
    int index;
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            type = get_type(Location{r,c});
            index = r*size + c;
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

    RGBIMAGEDATA export_data {image_data, size, size};
    bool success = export_bmp(export_data, outfile);

    delete [] image_data;

    return success;
}
