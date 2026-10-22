#include "GnssSensor.hpp"

#include "Scheduler.hpp"

#include <cstdint>
#include <random>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t GNSS_FREQUENCY_HZ = 20;

GnssSensor::GnssSensor(std::string_view name) : GenericSensor(name) { this->period = 1'000 / GNSS_FREQUENCY_HZ; }

Measurement GnssSensor::GenerateData()
{
    std::random_device device;
    std::mt19937 generator{device()};
    std::normal_distribution<double> dist{0, 0.1};

    Vec3 data = {std::sin(GNSS_FREQUENCY_HZ * scheduler.CurrentTime() + 0) + dist(generator),
                 std::sin(GNSS_FREQUENCY_HZ * scheduler.CurrentTime() + 1) + dist(generator),
                 std::sin(GNSS_FREQUENCY_HZ * scheduler.CurrentTime() + 2) + dist(generator)};

    return Measurement{.timestamp = scheduler.CurrentTime(), .id = this->id, .data = data};
}
