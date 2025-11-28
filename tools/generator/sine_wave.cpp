#include "waveform.hpp"
#include <cmath>

class SineWave : public Waveform
{
    double frequency;
    double amplitude;

public:
    SineWave(double freq, double amp)
        : frequency(freq), amplitude(amp) {}

    double getValue(uint64_t i) const override
    {
        return amplitude * std::sin(2.0 * M_PI * frequency * (double)i);
    }
};

Waveform *create_sine(double freq, double amp)
{
    return new SineWave(freq, amp);
}
