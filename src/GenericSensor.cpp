#include "GenericSensor.hpp"

#include "Scheduler.hpp"

extern Scheduler scheduler;

GenericSensor::GenericSensor(std::string_view name) : GenericComponent(name) {}

uint64_t GenericSensor::Period() { return this->period; }

void GenericSensor::Step()
{
    if (this->failed)
        return;

    this->measurements.push(GenerateData());

    Log(logging::Level::DEBUG, std::format("Generated measurement {}", this->measurements.back()));
}

void GenericSensor::InjectFailure()
{
    this->failed = true;
    Log(logging::Level::INFO, "Sensor failed.");
}

void GenericSensor::ClearFailure()
{
    this->failed = false;
    Log(logging::Level::INFO, "Sensor unfailed.");
}

std::optional<Measurement> GenericSensor::ReadData()
{
    if (this->failed || this->measurements.empty())
        return std::nullopt;

    Measurement measurement = this->measurements.front();
    this->measurements.pop();
    return measurement;
}
