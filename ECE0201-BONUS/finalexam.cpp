#include <iostream>

class Shelf {
    private:
        static const int MAX_ITEMS = 10;
        std::string items[MAX_ITEMS];
        int num_items;
    public:
        Shelf();
        bool add(std::string new_item);
        std::string get_item(int idx) const;
        void replace(int idx, std::string new_item);
        int get_num_items() const;
};
 
void Shelf::replace(int idx, std::string new_item) {
    if (idx < 0 || idx >= num_items) {
        throw std::out_of_range("Invalid index");
    }
    items[idx] = new_item;
}

class Square : public Shape {
    private:
        double size;
        int num_sides;
    public:
        double perimeter() const;
        double area() const;
        double compactness() const;
        bool set_size(double newsize);
};

class Rectangle : public Shape {
    private:
        double height, width;
        int num_sides;
    public:
        double perimeter() const;
        double area() const;
        double compactness() const;
        bool set_height(double newheight);
        bool set_width(double newwidth);
};

class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual double compactness() const = 0;
    virtual bool set_dimensions(double dimension1, double dimension2 = 0) = 0;
};