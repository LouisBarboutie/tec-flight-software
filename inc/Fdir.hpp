#ifndef __FDIR_HPP__
#define __FDIR_HPP__

#include "GenericSensor.hpp"
#include "Measurement.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

class Fdir
{
  public:
    void AddMonitoredSensor(const GenericSensor& sensor);
    void CheckOutput(bool availableImuData, bool availableGnssData);
    void CheckSensors(const std::vector<Measurement>& imuMeasurements,
                      const std::vector<Measurement>& gnssMeasurements);

  private:
    struct RegisteredSensor {
        uint64_t lastTimeStamp{};
        uint64_t period{};
        bool alarm{false};
    };
    std::unordered_map<SensorId, RegisteredSensor> registeredSensors{};
};

#endif
