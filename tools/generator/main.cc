#include "waveform.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include "rtm/probe.h"

using namespace std::chrono;

Waveform *create_sine(double freq, double amp);
Waveform *create_square(double freq, double amp);
Waveform *create_saw(double freq, double amp);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: generator <filename> <wave> <samples>\n";
        std::cerr << "Wave types: sine | square | saw\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string wave_type = argv[2];
    uint64_t samples = std::stoull(argv[3]);

    std::unordered_map<std::string, Waveform *(*)(double, double)> factory = {
        {"sine", create_sine},
        {"square", create_square},
        {"saw", create_saw}};

    if (!factory.count(wave_type))
    {
        std::cerr << "Unknown wave type: " << wave_type << "\n";
        return 1;
    }

    constexpr nanoseconds START = 8'000'000s;
    auto io = std::make_unique<rtm::FileWrite>(filename.c_str());
    rtm::Probe probe;
    probe.init("generator", wave_type.c_str(),
               START, 1ms, 42,
               std::move(io));

    std::unique_ptr<Waveform> wave(factory[wave_type](0.001, 1.0));

    for (uint64_t i = 0; i < samples; ++i)
    {
        double value = wave->getValue(i);
        nanoseconds now = START + duration_cast<nanoseconds>(milliseconds(i)) +
                          duration_cast<nanoseconds>(microseconds((int)(value * 500)));

        probe.log(now);
        probe.log(now + 200us);
    }
    probe.flush();
}
