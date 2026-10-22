#ifndef __FDIR_HPP__
#define __FDIR_HPP__

#include "GenericSensor.hpp"
#include "ISensor.hpp"

#include <cstdint>
#include <unordered_map>

class Fdir
{
  public:
    void AddMonitoredSensor(const GenericSensor& sensor);
    void CheckSensors();
    void PetTheDog(SensorId id);

  private:
    struct RegisteredSensor {
        uint64_t lastTimeStamp{};
        uint64_t period{};
        bool alarm{false};
    };
    std::unordered_map<SensorId, RegisteredSensor> registeredSensors{};
};

#endif
