#include "GnssSensor.hpp"

#include "Scheduler.hpp"

#include <cstdint>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t GNSS_FREQUENCY_HZ = 20;

GnssSensor::GnssSensor(std::string_view name) : GenericSensor(name) { this->period = 1'000 / GNSS_FREQUENCY_HZ; }

Measurement GnssSensor::GenerateData()
{
    return Measurement{.timestamp = scheduler.CurrentTime(), .id = this->id, .data = Vec3()};
}
