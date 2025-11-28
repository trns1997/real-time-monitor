#include "waveform.hpp"
#include <cmath>

class SquareWave : public Waveform
{
    double frequency;
    double amplitude;

public:
    SquareWave(double freq, double amp)
        : frequency(freq), amplitude(amp) {}

    double getValue(uint64_t i) const override
    {
        double v = std::sin(2.0 * M_PI * frequency * (double)i);
        return (v >= 0.0 ? amplitude : -amplitude);
    }
};

Waveform *create_square(double freq, double amp)
{
    return new SquareWave(freq, amp);
}
