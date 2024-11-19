#include "VoltageDivider.hpp"
#include <stdexcept>
//blah blah blah this sucks I spent too much time on this garbage but it works and that's what matters
VoltageDivider::VoltageDivider(double v, double res[], int num_res)
    : Network(num_res + 2, num_res + 1), num_resistors(num_res)
{
    if (num_res < 1) {
        throw std::invalid_argument("Number of resistors must be at least 1");
    }
    set_node_voltage(0, 0.0);

    VoltageSource* vs = new VoltageSource(v);
    set_component(0, vs);
    connect_component_terminal_a(0, 0);
    connect_component_terminal_b(0, 1);

for (int i = 0; i < num_resistors; ++i) {
    Resistor* r = new Resistor(res[i]);
    set_component(i + 1, r);
    connect_component_terminal_b(i + 1, i + 1);
    connect_component_terminal_a(i + 1, i + 2);
}
double total_resistance = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        total_resistance += res[i];
    }
    double loop_current = v / total_resistance;
    set_node_voltage(1, v);
    double cumulative_voltage = v;
    for (int i = 0; i < num_resistors; ++i) {
        double voltage_drop = loop_current * res[i];
        cumulative_voltage -= voltage_drop;
        set_node_voltage(i + 2, cumulative_voltage);
    }
}

int VoltageDivider::get_num_resistors() const
{
    return num_resistors;
}

double VoltageDivider::get_source_voltage() const
{
    return get_component_value(0);
}

double VoltageDivider::get_resistance(int idx) const
{
    if (idx < 0 || idx >= num_resistors) {
        throw std::out_of_range("Resistor index out of range");
    }
    return get_component_value(idx + 1);
}

double VoltageDivider::get_resistor_voltage(int idx) const
{
    if (idx < 0 || idx >= num_resistors) {
        throw std::out_of_range("Resistor index out of range");
    }
    return get_component_voltage(idx + 1);
}

double VoltageDivider::get_loop_current() const
{

    double total_resistance = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        total_resistance += get_component_value(i + 1);
    }
    double source_voltage = get_component_value(0);
    return source_voltage / total_resistance;
}

void VoltageDivider::set_source_voltage(double v)
{

    set_component_value(0, v);
    double total_resistance = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        total_resistance += get_component_value(i + 1);
    }
    double loop_current = v / total_resistance;
    set_node_voltage(1, v);
    double cumulative_voltage = v;
    for (int i = 0; i < num_resistors; ++i) {
        double voltage_drop = loop_current * get_component_value(i + 1);
        cumulative_voltage -= voltage_drop;
        set_node_voltage(i + 2, cumulative_voltage);
    }
}

void VoltageDivider::set_resistance(int idx, double r)
{
    if (idx < 0 || idx >= num_resistors) {
        throw std::out_of_range("Resistor index out of range");
    }
    set_component_value(idx + 1, r);
    double total_resistance = 0.0;
    for (int i = 0; i < num_resistors; ++i) {
        total_resistance += get_component_value(i + 1);
    }

    double source_voltage = get_component_value(0);
    double loop_current = source_voltage / total_resistance;

    set_node_voltage(1, source_voltage);
    double cumulative_voltage = source_voltage;
    for (int i = 0; i < num_resistors; ++i) {
        double voltage_drop = loop_current * get_component_value(i + 1);
        cumulative_voltage -= voltage_drop;
        set_node_voltage(i + 2, cumulative_voltage);
    }
}
