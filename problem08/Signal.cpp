#include "Signal.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <fstream>
const double THRESHOLD = 1e-9;
// constructors
Signal::Signal() : num_samples(101), sampling_freq(100) {
    zeros();
}

// paramertized constructor
Signal::Signal(int num_samples, int sampling_freq) {
    if (num_samples < 0 || num_samples > MAX_SAMPLES) {
        throw std::invalid_argument("Invalid number of samples");
    }
    if (sampling_freq <= 0) {
        throw std::invalid_argument("Invalid sampling frequency");
    }
    this->num_samples = num_samples;
    this->sampling_freq = sampling_freq;
    zeros();
}

// accessor
int Signal::get_samples() const {
    return num_samples;
}

int Signal::get_sampling_freq() const {
    return sampling_freq;
}

// provided: assign values to signals
void Signal::zeros() {
    for (int i = 0; i < num_samples; i++) {
        sig_data[i].time = static_cast<double>(i) / sampling_freq;
        sig_data[i].value = 0.0;
    }
}

void Signal::constant(double val) {
    if (val < 0) {
        throw std::invalid_argument("Invalid signal value");
    }

    for (int i = 0; i < num_samples; i++) {
        sig_data[i].time = static_cast<double>(i) / sampling_freq;
        sig_data[i].value = val;
    }
}

void Signal::sinusoid(double amplitude, int freq, double phase) {
    if (amplitude < 0 || freq < 0) {
        throw std::invalid_argument("Amplitude and frequency must be non-negative");
    }

    for (int i = 0; i < num_samples; i++) {
        sig_data[i].time = static_cast<double>(i) / sampling_freq;
        sig_data[i].value = amplitude * cos(2 * M_PI * freq * sig_data[i].time + phase);
    }
}

// provided: exports
void Signal::export_signal(double time[], double values[]) {
    for (int i = 0; i < num_samples; i++) {
        time[i] = sig_data[i].time;
        values[i] = sig_data[i].value;
    }
}

bool Signal::export_csv(std::string outfile) {
    std::ofstream filewrite(outfile + ".csv");
    if (!filewrite.fail()) {
        filewrite << "t, s(t)" << std::endl;
        for (int i = 0; i < num_samples; i++) {
            filewrite << sig_data[i].time << ", " << sig_data[i].value << std::endl;
        }
        filewrite.close();
        return true;
    }
    return false;
}

// Overloaded operators
bool Signal::operator==(const Signal& other) const {
    if (num_samples != other.num_samples || sampling_freq != other.sampling_freq) {
        return false;
    }
    for (int i = 0; i < num_samples; i++) {
        if (std::abs(sig_data[i].time - other.sig_data[i].time) > THRESHOLD ||
            std::abs(sig_data[i].value - other.sig_data[i].value) > THRESHOLD) {
            return false;
        }
    }
    return true;
}

bool Signal::operator!=(const Signal& other) const {
    return !(*this == other);
}

Signal Signal::operator+(const Signal& other) const {
    if (sampling_freq != other.sampling_freq) {
        throw std::logic_error("Sampling frequencies must be the same for addition");
    }

    int min_samples = std::min(num_samples, other.num_samples);
    Signal result;
    result.num_samples = std::max(num_samples, other.num_samples);
    result.sampling_freq = sampling_freq;

    for (int i = 0; i < min_samples; i++) {
        result.sig_data[i].time = sig_data[i].time;
        result.sig_data[i].value = sig_data[i].value + other.sig_data[i].value;
    }

    if (num_samples > min_samples) {
        for (int i = min_samples; i < num_samples; i++) {
            result.sig_data[i] = sig_data[i];
        }
    } else {
        for (int i = min_samples; i < other.num_samples; i++) {
            result.sig_data[i] = other.sig_data[i];
        }
    }

    return result;
}
