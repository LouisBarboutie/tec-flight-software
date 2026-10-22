#include "Fdir.hpp"

#include "Logger.hpp"
#include "Scheduler.hpp"

#include <cstdint>
#include <ranges>

extern Scheduler scheduler;

void Fdir::AddMonitoredSensor(const GenericSensor& sensor)
{
    this->registeredSensors[sensor.Id()] = {.lastTimeStamp = 0, .period = sensor.Period()};
    logging::Log(logging::Level::INFO, std::format("Registered sensor {} with id {}", sensor.Name(), sensor.Id()));
}

void Fdir::CheckSensors()
{
    // 2. Check that all latest timestamps are within one acquisition period
    for (auto& [id, sensor] : this->registeredSensors) {
        uint64_t diff = scheduler.CurrentTime() - sensor.lastTimeStamp;
        bool silent = diff > 3 * sensor.period;

        if (silent && !sensor.alarm) {
            logging::Log(
                logging::Level::INFO,
                std::format("RAISING ALARM: Sensor #{} hasn't provided data in 3 nominal measurement intervals {} ms ",
                            id,
                            sensor.period * 3));
        } else if (!silent && sensor.alarm)
            logging::Log(logging::Level::INFO, std::format("LOWERING ALARM: Sensor #{} has recovered", id));

        sensor.alarm = silent;
    }
}

void Fdir::PetTheDog(SensorId id)
{
    if (!this->registeredSensors.contains(id)) {
        Log(logging::Level::WARNING, std::format("Cannot pet the dog for unregistered sensor with id {}", id));
        return;
    }

    this->registeredSensors[id].lastTimeStamp = scheduler.CurrentTime();
}
