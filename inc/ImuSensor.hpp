#ifndef __IMUSENSOR_HPP__
#define __IMUSENSOR_HPP__

#include "GenericComponent.hpp"
#include "ISensor.hpp"
#include <string_view>

class ImuSensor : public GenericComponent, public ISensor
{
  public:
    ImuSensor(std::string_view name);

    void Step() override;
    uint64_t Period() override;

    void InjectFailure() override;
    void ClearFailure() override;
    void ReadData() override;
};

#endif
