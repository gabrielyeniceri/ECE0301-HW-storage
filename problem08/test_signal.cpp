#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <stdexcept>
#include <cmath>

#include "Signal.hpp"

const double THRESHOLD = 1e-9;

/* Provided test cases */

// TEST_CASE("Export example", "[signal]"){
//     Signal sdef;
//     sdef.sinusoid(5, 10, -M_PI/4);
//     sdef.export_csv("output");
// }

TEST_CASE("Test default construction", "[signal]"){
    Signal sdef;

    REQUIRE(sdef.get_samples() == 101);
    REQUIRE(sdef.get_sampling_freq() == 100);
}

TEST_CASE("Test construction with args", "[signal]"){
    int samples = 50;
    int frequency = 200;
    Signal sarg(samples, frequency);

    REQUIRE(sarg.get_samples() == samples);
    REQUIRE(sarg.get_sampling_freq() == frequency);

    // must call the signal constructor directly to check throws in constructor
    // invalid samples
    REQUIRE_THROWS_AS(Signal(-1, frequency), std::invalid_argument);
    REQUIRE_THROWS_AS(Signal(Signal::MAX_SAMPLES+1, frequency), std::invalid_argument);
    // invalid freq
    REQUIRE_THROWS_AS(Signal(samples, -1), std::invalid_argument);
    REQUIRE_THROWS_AS(Signal(samples, 0), std::invalid_argument);   
}

TEST_CASE("Test default construction zeros", "[signal]"){
    Signal zero;

    const int samples = zero.get_samples();
    int freq = zero.get_sampling_freq();

    // arrays to hold exported data
    double time[samples];
    double values[samples];

    zero.export_signal(time, values);

    double time_diff, val_diff;
    for (int i=0; i<samples; i++) {
        // check time according to equation
        time_diff = std::abs(time[i] - (double)i/freq);
        REQUIRE(time_diff <= THRESHOLD);
        // all values should be zero
        val_diff = std::abs(values[i] - 0);
        REQUIRE(val_diff <= THRESHOLD);
    }
}

/* Your test cases here */
