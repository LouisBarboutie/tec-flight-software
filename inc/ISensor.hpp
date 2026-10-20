#ifndef __ISENSOR_HPP__
#define __ISENSOR_HPP__

#include "Measurement.hpp"

#include <optional>

typedef uint64_t SensorId;

class ISensor
{
  public:
    virtual void InjectFailure() = 0;
    virtual void ClearFailure() = 0;
    virtual std::optional<Measurement> ReadData() = 0;
    virtual SensorId Id() const = 0;
};

#endif
