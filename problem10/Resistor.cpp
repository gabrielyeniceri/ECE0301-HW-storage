#include "Resistor.hpp"
#include <stdexcept>

void Resistor::set_value(double r)
{
    if (r < 0)
    {
        throw std::invalid_argument("Resistance cannot be negative");
    }
    Component::set_value(r);
}

double Resistor::get_current() const
{
    if (get_node_a() == nullptr || get_node_b() == nullptr)
    {
        throw std::logic_error("Resistor terminals not connected");
    }

    double voltage_difference = get_node_b()->get_voltage() - get_node_a()->get_voltage();
    double resistance = get_value();

    if (resistance == 0)
    {
        throw std::logic_error("Division by zero: Resistance is zero");
    }

    return voltage_difference / resistance;
}
