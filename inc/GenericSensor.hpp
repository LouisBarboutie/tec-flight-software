#ifndef __GENERICSENSOR_HPP__
#define __GENERICSENSOR_HPP__

#include "GenericComponent.hpp"
#include "ISensor.hpp"

#include <cstdint>
#include <string_view>

// Abstract base class to handle the common processing elements of sensors
class GenericSensor : public GenericComponent, public ISensor
{
  public:
    GenericSensor(std::string_view name);

    void Step() override;
    uint64_t Period() override;

    void InjectFailure() override;
    void ClearFailure() override;

    std::optional<Measurement> ReadData() override;

  protected:
    std::queue<Measurement> measurements{};
    bool failed{false};
    uint64_t period{0};

    virtual Measurement GenerateData() = 0;
};

#endif
