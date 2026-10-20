#include "Fdir.hpp"

#include "Logger.hpp"
#include "Scheduler.hpp"

#include <algorithm>
#include <cstdint>
#include <ranges>

extern Scheduler scheduler;

void Fdir::AddMonitoredSensor(const GenericSensor& sensor)
{
    this->registeredSensors[sensor.Id()] = {.lastTimeStamp = 0, .period = sensor.Period()};
    logging::Log(logging::Level::INFO, std::format("Registered sensor {} with id {}", sensor.Name(), sensor.Id()));
}

void Fdir::CheckOutput(bool availableImuData, bool availableGnssData) {}

void Fdir::CheckSensors(const std::vector<Measurement>& imuMeasurements,
                        const std::vector<Measurement>& gnssMeasurements)

{
    // 1. Update the latest time stamps
    for (const auto* batch : {&imuMeasurements, &gnssMeasurements}) {
        for (const Measurement& m : *batch) {
            if (auto it = registeredSensors.find(m.id); it != registeredSensors.end())
                it->second.lastTimeStamp = std::max(it->second.lastTimeStamp, m.timestamp);
        }
    }

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
