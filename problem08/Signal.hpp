#ifndef _SIGNAL_HPP
#define _SIGNAL_HPP

#include <string>
#include <fstream>

class Signal {
    public:
        // provided: max samples
        static const int MAX_SAMPLES = 200;

        // TODO: constructors

        // TODO: accessors

        // provided: assign values to signals
        void zeros();
        void constant(double val);

        // TODO: sinusoid

        // TODO: overloaded operators

        // provided: exports
        void export_signal(double time[], double values[]); 
        bool export_csv(std::string outfile);

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