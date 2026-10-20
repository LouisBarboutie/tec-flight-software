#include "GenericComponent.hpp"
#include "GnssSensor.hpp"
#include "ISensor.hpp"
#include "Scheduler.hpp"
#include <cstdint>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t GNSS_FREQUENCY_HZ = 20;

GnssSensor::GnssSensor(std::string_view name) : GenericComponent(name) {}

uint64_t GnssSensor::Period() { return 1'000 / GNSS_FREQUENCY_HZ; }

void GnssSensor::Step()
{
    if (this->failed)
        return;

    this->measurements.push({.timestamp = scheduler.CurrentTime(), .data = Vec3()});
}

void GnssSensor::InjectFailure() { this->failed = true; }

void GnssSensor::ClearFailure() { this->failed = false; }

std::optional<Measurement> GnssSensor::ReadData()
{
    if (this->failed || this->measurements.empty())
        return std::nullopt;

    Measurement measurement = this->measurements.front();
    this->measurements.pop();
    return measurement;
}
