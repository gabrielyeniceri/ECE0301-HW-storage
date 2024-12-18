#ifndef _GRID_HPP
#define _GRID_HPP

#include <stdexcept>

struct Location {
    int row;
    int col;
};

template <typename T>
class Grid {
    private:
        int size;
        T** data;

    public:
        static const int DEFAULT_SIZE;

        Grid();
        Grid(int start_size);
        Grid(const Grid& gcopy) = delete; // not copyable
        Grid& operator=(const Grid& g) = delete; // not copyable
        ~Grid();

        int get_size() const;
        T* get_cell(Location loc) const;
        void set_cell(Location loc, T* val);
        bool move(Location from, Location to);
        void clear();
        void resize(int new_size);
};

#include "Grid.tpp"

#endif
