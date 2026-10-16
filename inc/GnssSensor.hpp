#ifndef __GNSSSENSOR_HPP__
#define __GNSSSENSOR_HPP__

#include "GenericComponent.hpp"
#include "ISensor.hpp"
#include <string_view>

class GnssSensor : public GenericComponent, public ISensor
{
  public:
    GnssSensor(std::string_view name);

    void Step() override;
    uint64_t Period() override;

    void InjectFailure() override;
    void ClearFailure() override;
    void ReadData() override;
};

#endif
