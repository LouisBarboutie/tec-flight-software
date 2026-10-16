#include "GenericComponent.hpp"
#include "ImuSensor.hpp"
#include <cstdint>
#include <string_view>

constexpr uint64_t IMU_FREQUENCY_HZ = 100;

ImuSensor::ImuSensor(std::string_view name) : GenericComponent(name) {}

uint64_t ImuSensor::Period() { return 1'000 / IMU_FREQUENCY_HZ; }

void ImuSensor::Step()
{
    // TODO
}

void ImuSensor::InjectFailure()
{
    // TODO
}

void ImuSensor::ClearFailure()
{
    // TODO
}

void ImuSensor::ReadData()
{
    // TODO
}
