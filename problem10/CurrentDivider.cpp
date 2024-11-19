#include "CurrentDivider.hpp"
#include <stdexcept>
//I would not want to do this my entire life
CurrentDivider::CurrentDivider(double c, double res[], int num_res)
    : Network(2, num_res + 1), num_resistors(num_res)
{
    if (num_res < 1) {
        throw std::invalid_argument("Number of resistors must be at least 1");
    }
    set_node_voltage(0, 0.0);
    CurrentSource* cs = new CurrentSource(c);
    set_component(0, cs);

    connect_component_terminal_a(0, 0);
    connect_component_terminal_b(0, 1);

   
    for (int i = 0; i < num_resistors; ++i) {
       
        Resistor* r = new Resistor(res[i]);
        set_component(i + 1, r);
        connect_component_terminal_a(i + 1, 0);
        connect_component_terminal_b(i + 1, 1);
    }

  //calculates equivalent resistance
    double reciprocal_sum = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        double resistance = res[i];
        if (resistance == 0) {
            throw std::invalid_argument("Resistance cannot be zero");
        }
        reciprocal_sum += 1.0 / resistance;
    }
    double Rp = 1.0 / reciprocal_sum;
    double Vr = c * Rp;
    set_node_voltage(1, Vr);
}

int CurrentDivider::get_num_resistors() const
{
    return num_resistors;
}

double CurrentDivider::get_source_current() const
{
    return get_component_value(0);
}

double CurrentDivider::get_resistance(int idx) const
{
    if (idx < 0 || idx >= num_resistors) {
        throw std::out_of_range("Resistor index out of range");
    }
    return get_component_value(idx + 1);
}

double CurrentDivider::get_resistor_voltage() const
{
    return get_node_voltage(1) - get_node_voltage(0);
}

double CurrentDivider::get_resistor_current(int idx) const
{
    if (idx < 0 || idx >= num_resistors) {
        throw std::out_of_range("Resistor index out of range");
    }
    return get_component_current(idx + 1);
}

void CurrentDivider::set_source_current(double c)
{
    set_component_value(0, c);
//updates then recalculates equivalent res
    double reciprocal_sum = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        double resistance = get_component_value(i + 1);
        if (resistance == 0) {
            throw std::logic_error("Resistance cannot be zero");
        }
        reciprocal_sum += 1.0 / resistance;
    }
    double Rp = 1.0 / reciprocal_sum;
    double Vr = c * Rp;
    set_node_voltage(1, Vr);
}

void CurrentDivider::set_resistance(int idx, double r)
{
    if (idx < 0 || idx >= num_resistors) {
        throw std::out_of_range("Resistor index out of range");
    }
    set_component_value(idx + 1, r);
    double source_current = get_component_value(0);

    double reciprocal_sum = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        double resistance = get_component_value(i + 1);
        if (resistance == 0) {
            throw std::logic_error("Resistance cannot be zero");
        }
        reciprocal_sum += 1.0 / resistance;
    }
    double Rp = 1.0 / reciprocal_sum;
    double Vr = source_current * Rp;
    set_node_voltage(1, Vr);
}
//it works