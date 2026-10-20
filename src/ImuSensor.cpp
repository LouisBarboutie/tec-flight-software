#include "GenericComponent.hpp"
#include "ISensor.hpp"
#include "ImuSensor.hpp"
#include "Scheduler.hpp"
#include <cstdint>
#include <optional>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t IMU_FREQUENCY_HZ = 100;

ImuSensor::ImuSensor(std::string_view name) : GenericComponent(name) {}

uint64_t ImuSensor::Period() { return 1'000 / IMU_FREQUENCY_HZ; }

void ImuSensor::Step()
{
    if (this->failed) {
        return;
    }

    // TODO
    this->measurements.push({
        .timestamp = scheduler.CurrentTime(),
        .data = Vec3(),
    });

    Log(logging::Level::DEBUG,
        std::format("Generated measurement (x={}, y={}, z={})",
                    this->measurements.back().data.x,
                    this->measurements.back().data.y,
                    this->measurements.back().data.z));
}

void ImuSensor::InjectFailure()
{
    this->failed = true;
    this->measurements = {}; // clear the queue
}

void ImuSensor::ClearFailure() { this->failed = false; }

std::optional<Measurement> ImuSensor::ReadData()
{
    if (this->measurements.empty() || this->failed)
        return std::nullopt;

    Measurement measurement = this->measurements.front();
    this->measurements.pop();
    return measurement;
}
