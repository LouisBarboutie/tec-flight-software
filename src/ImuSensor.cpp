#include "ImuSensor.hpp"

#include "GenericSensor.hpp"
#include "Scheduler.hpp"

#include <cstdint>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t IMU_FREQUENCY_HZ = 100;

ImuSensor::ImuSensor(std::string_view name) : GenericSensor(name) { this->period = 1'000 / IMU_FREQUENCY_HZ; }

Measurement ImuSensor::GenerateData() { return Measurement{.timestamp = scheduler.CurrentTime(), .data = Vec3()}; }
