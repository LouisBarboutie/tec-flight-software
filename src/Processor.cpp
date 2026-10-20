#include "Fdir.hpp"
#include "GenericComponent.hpp"
#include "ImuSensor.hpp"
#include "Processor.hpp"
#include "Scheduler.hpp"

#include <cstdint>
#include <optional>
#include <queue>
#include <ranges>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t PROCESSOR_FREQUENCY_HZ = 50;

Processor::Processor(std::string_view name) : GenericComponent(name) { this->fdir = Fdir(); }

uint64_t Processor::Period() { return 1'000 / PROCESSOR_FREQUENCY_HZ; }

void Processor::Step()
{

    // 1. Get the latest measurements

    for (const auto imu : this->imuSensors) {
        while (std::optional<Measurement> measurement = imu->ReadData()) {
            this->imuMeasurements.push_back(measurement.value());
        }
    }

    for (const auto gnss : this->gnssSensors) {
        while (std::optional<Measurement> measurement = gnss->ReadData()) {
            this->gnssMeasurements.push_back(measurement.value());
        }
    }

    // 2. Filter outdated measurements

    // Remove measurements that are older than one tick
    std::erase_if(this->imuMeasurements, [this](Measurement measurement) {
        return measurement.timestamp >= scheduler.CurrentTime() - this->Period();
    });

    // Remove measurements that are older than one second
    std::erase_if(this->gnssMeasurements, [this](Measurement measurement) {
        return measurement.timestamp >= scheduler.CurrentTime() - 1 * SECOND;
    });

    // Update data availability flags
    this->isImuDataAvailable = this->imuMeasurements.size() > 0 ? true : false;
    this->isGnssDataAvailable = this->gnssMeasurements.size() > 0 ? true : false;

    // 3. Generate averages
}
