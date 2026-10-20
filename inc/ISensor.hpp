#ifndef __ISENSOR_HPP__
#define __ISENSOR_HPP__

#include "Measurement.hpp"

#include <optional>

class ISensor
{
  public:
    virtual void InjectFailure() = 0;
    virtual void ClearFailure() = 0;
    virtual std::optional<Measurement> ReadData() = 0;
};

#endif
