#include "GenericComponent.hpp"
#include "GnssSensor.hpp"
#include <cstdint>
#include <string_view>

constexpr uint64_t GNSS_FREQUENCY_HZ = 20;

GnssSensor::GnssSensor(std::string_view name) : GenericComponent(name) {}

uint64_t GnssSensor::Period() { return 1'000 / GNSS_FREQUENCY_HZ; }

void GnssSensor::Step()
{
    // TODO
}

void GnssSensor::InjectFailure()
{
    // TODO
}

void GnssSensor::ClearFailure()
{
    // TODO
}

void GnssSensor::ReadData()
{
    // TODO
}
