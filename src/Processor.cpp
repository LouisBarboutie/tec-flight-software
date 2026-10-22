#include "Processor.hpp"

#include "Fdir.hpp"
#include "GenericComponent.hpp"
#include "ImuSensor.hpp"
#include "Scheduler.hpp"
#include "Vec3.hpp"

#include <cstdint>
#include <optional>
#include <string_view>

extern Scheduler scheduler;

constexpr uint64_t PROCESSOR_FREQUENCY_HZ = 50;

Processor::Processor(std::string_view name) : GenericComponent(name) { this->fdir = Fdir(); }

uint64_t Processor::Period() const { return 1'000 / PROCESSOR_FREQUENCY_HZ; }

void Processor::Step()
{

    // 1. Get the latest measurements

    for (const auto imu : this->imuSensors) {
        while (std::optional<Measurement> measurement = imu->ReadData()) {
            this->imuMeasurements.push_back(measurement.value());
            this->fdir.PetTheDog(imu->Id());
        }
    }

    for (const auto gnss : this->gnssSensors) {
        while (std::optional<Measurement> measurement = gnss->ReadData()) {
            this->gnssMeasurements.push_back(measurement.value());
            this->fdir.PetTheDog(gnss->Id());
        }
    }

    // 2. Filter outdated measurements

    // Remove measurements that are older than one tick
    std::erase_if(this->imuMeasurements, [this](Measurement measurement) {
        return scheduler.CurrentTime() - measurement.timestamp > this->Period();
    });

    // Remove measurements that are older than one second
    std::erase_if(this->gnssMeasurements, [this](Measurement measurement) {
        return scheduler.CurrentTime() - measurement.timestamp > 1 * SECOND;
    });

    // Update data availability flags
    this->isImuDataAvailable = this->imuMeasurements.size() > 0 ? true : false;
    this->isGnssDataAvailable = this->gnssMeasurements.size() > 0 ? true : false;

    // 3. Generate averages

    Vec3 imuMean = ComputeAverage(this->imuMeasurements);
    Vec3 gnssMean = ComputeAverage(this->gnssMeasurements);

    // 4. Run the FDIR

    this->fdir.CheckSensors();
}

void Processor::Init()
{
    for (const auto sensor : this->imuSensors)
        this->fdir.AddMonitoredSensor(*sensor);
    for (const auto sensor : this->gnssSensors)
        this->fdir.AddMonitoredSensor(*sensor);
}

Vec3 Processor::ComputeAverage(const std::vector<Measurement>& measurements)
{
    Vec3 mean{};
    for (const auto& measurement : measurements) {
        mean = mean + measurement.data;
    }
    mean = (1 / static_cast<double>(this->gnssMeasurements.size())) * mean;
    Log(logging::Level::DEBUG, std::format("{}", mean));
    return mean;
}
