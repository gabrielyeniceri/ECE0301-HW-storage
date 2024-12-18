#ifndef _SHELF_HPP
#define _SHELF_HPP

template <typename T>
class Shelf {
    private:
        static const int MAX_ITEMS = 10;
        T items[MAX_ITEMS];
        int num_items;
    public:
        Shelf();
        bool add(T new_item);
        T get_item(int idx) const;
        void replace(int idx, T new_item);
        int get_num_items() const;
};

#endif