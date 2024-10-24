#include "Signal.hpp"

#include <stdexcept>
#include <string>
#include <fstream>

// TODO: constructors


// TODO: accessors


// provided: assign values to signals
void Signal::zeros() {
    for (int i=0; i<num_samples; i++) {
        sig_data[i].time = (double)i/sampling_freq;
        sig_data[i].value = 0.0;
    }
}

void Signal::constant(double val) {
    if (val < 0) {
        throw std::invalid_argument("Invalid signal value");
    }

    for (int i=0; i<num_samples; i++) {
        sig_data[i].time = (double)i/sampling_freq;
        sig_data[i].value = val;
    }
}


// TODO: sinusoid


// TODO: overloaded operators


// provided: exports
void Signal::export_signal(double time[], double values[]) {
    for (int i=0; i<num_samples; i++) {
        time[i] = sig_data[i].time;
        values[i] = sig_data[i].value;
    }
}

bool Signal::export_csv(std::string outfile) {
    std::ofstream filewrite(outfile + ".csv");
    if (!filewrite.fail()) {
        filewrite << "t, s(t)" << std::endl;
        for (int i=0; i<num_samples; i++) {
            filewrite << sig_data[i].time << ", " << sig_data[i].value << std::endl;
        }
        filewrite.close();
        return true;
    }
    return false;
}



