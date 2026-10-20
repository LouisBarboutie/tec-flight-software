#ifndef __GNSSSENSOR_HPP__
#define __GNSSSENSOR_HPP__

#include "GenericSensor.hpp"

#include <string_view>

class GnssSensor : public GenericSensor
{
  public:
    GnssSensor(std::string_view name);

  private:
    Measurement GenerateData() override;
};

#endif
