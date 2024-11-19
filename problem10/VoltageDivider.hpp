#ifndef _VOLTAGE_DIVIDER_HPP
#define _VOLTAGE_DIVIDER_HPP

#include "Network.hpp"
#include "VoltageSource.hpp"
#include "Resistor.hpp"
#include <vector>

class VoltageDivider : public Network {

    private:
        int num_resistors;

    public:
        VoltageDivider(double v, double res[], int num_res);
        int get_num_resistors() const;
        double get_source_voltage() const;
        double get_resistance(int idx) const;
        double get_resistor_voltage(int idx) const;
        double get_loop_current() const;

        void set_source_voltage(double v);
        void set_resistance(int idx, double r);
};

#endif
