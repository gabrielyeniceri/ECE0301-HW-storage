#include <algorithm>
#include "Grid.hpp"

template <typename T>
const int Grid<T>::DEFAULT_SIZE = 10;

template <typename T>
Grid<T>::Grid() : size(DEFAULT_SIZE)
{
    data = new T*[size*size];
    // initialize all to nullptr
    for (int i = 0; i < size*size; i++) {
        data[i] = nullptr;
    }
}

template <typename T>
Grid<T>::Grid(int start_size)
{
    if (start_size <= 0) {
        throw std::invalid_argument("Invalid grid size");
    }
    size = start_size;
    data = new T*[size*size];
    // initialize all to nullptr
    for (int i = 0; i < size*size; i++) {
        data[i] = nullptr;
    }
}

template <typename T>
Grid<T>::~Grid()
{
    clear();
    delete[] data;
}

template <typename T>
int Grid<T>::get_size() const
{
    return size;
}

template <typename T>
T* Grid<T>::get_cell(Location loc) const
{
    if (loc.row < 0 || loc.col < 0 || loc.row >= size || loc.col >= size) {
        throw std::out_of_range("Grid index out of bounds");
    }
    return data[loc.row * size + loc.col];
}

template <typename T>
void Grid<T>::set_cell(Location loc, T* val)
{
    if (loc.row < 0 || loc.col < 0 || loc.row >= size || loc.col >= size) {
        delete val;//added to prevent errors if out of bounds
        throw std::out_of_range("Grid index out of bounds");
    }
    int index = loc.row * size + loc.col;
    delete data[index];
    data[index] = val;
}

template <typename T>
bool Grid<T>::move(Location from, Location to)
{
    if (from.row < 0 || from.col < 0 || from.row >= size || from.col >= size ||
        to.row < 0 || to.col < 0 || to.row >= size || to.col >= size) {
        throw std::out_of_range("Grid index out of bounds");
    }
//false if occupied
    if (get_cell(to) != nullptr) {
        return false;
    }

    T* val = get_cell(from);
    int from_index = from.row * size + from.col;
    int to_index = to.row * size + to.col;
    data[to_index] = val;
    data[from_index] = nullptr;
    return true;
}

template <typename T>
void Grid<T>::clear()
{
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            set_cell(Location{r, c}, nullptr);
        }
    }
}

template <typename T>
void Grid<T>::resize(int new_size)
{
    if (new_size <= 0) {
        throw std::invalid_argument("Invalid grid size");
    }

    clear();

    // allocate new and swap
    T** new_grid = new T*[new_size*new_size];
    for (int i = 0; i < new_size*new_size; i++) {
        new_grid[i] = nullptr;
    }

    std::swap(data, new_grid);
    size = new_size;

    delete[] new_grid; //old data deleted
}

