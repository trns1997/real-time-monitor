#pragma once
#include <cstdint>

class Waveform
{
public:
    virtual ~Waveform() = default;
    virtual double getValue(uint64_t index) const = 0;
};
