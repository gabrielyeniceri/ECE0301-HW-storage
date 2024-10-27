#ifndef _SIGNAL_HPP
#define _SIGNAL_HPP

#include <string>
#include <fstream>
#include <stdexcept>

class Signal {
public:
    // provided: max samples
    static const int MAX_SAMPLES = 200;

    // constructors
    Signal(); 
    Signal(int num_samples, int sampling_freq);

    // accessirs
    int get_samples() const;
    int get_sampling_freq() const;

    // provided: assign values to signal
    void zeros();
    void constant(double val);
    void sinusoid(double amplitude, int freq, double phase);

    // provided: exports
    void export_signal(double time[], double values[]);
    bool export_csv(std::string outfile);

    // overloaded operators
    bool operator==(const Signal& other) const;
    bool operator!=(const Signal& other) const;
    Signal operator+(const Signal& other) const;

private:
    // provided: Point struct, private members
    struct Point {
        double time;
        double value;
    };

    int num_samples;
    int sampling_freq;
    Point sig_data[MAX_SAMPLES];
};

#endif
