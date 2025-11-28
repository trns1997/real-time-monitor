#include "waveform.hpp"
#include <cmath>

class SawWave : public Waveform
{
    double frequency;
    double amplitude;

public:
    SawWave(double freq, double amp)
        : frequency(freq), amplitude(amp) {}

    double getValue(uint64_t i) const override
    {
        double t = (double)i * frequency;
        return amplitude * (2.0 * (t - std::floor(t)) - 1.0);
    }
};

Waveform *create_saw(double freq, double amp)
{
    return new SawWave(freq, amp);
}
