#include "ImuSensor.hpp"

#include "GenericSensor.hpp"
#include "Scheduler.hpp"

#include <cmath>
#include <cstdint>
#include <random>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t IMU_FREQUENCY_HZ = 100;

ImuSensor::ImuSensor(std::string_view name) : GenericSensor(name) { this->period = 1'000 / IMU_FREQUENCY_HZ; }

Measurement ImuSensor::GenerateData()
{
    std::random_device device;
    std::mt19937 generator{device()};
    std::normal_distribution<double> dist{0, 0.1};

    Vec3 data = {std::sin(IMU_FREQUENCY_HZ * scheduler.CurrentTime() + 0) + dist(generator),
                 std::sin(IMU_FREQUENCY_HZ * scheduler.CurrentTime() + 1) + dist(generator),
                 std::sin(IMU_FREQUENCY_HZ * scheduler.CurrentTime() + 2) + dist(generator)};

    return Measurement{.timestamp = scheduler.CurrentTime(), .id = this->id, .data = data};
}
