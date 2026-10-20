#ifndef __IMUSENSOR_HPP__
#define __IMUSENSOR_HPP__

#include "GenericSensor.hpp"

#include <string_view>

class ImuSensor final : public GenericSensor
{
  public:
    ImuSensor(std::string_view name);

  private:
    Measurement GenerateData() override;
};

#endif
