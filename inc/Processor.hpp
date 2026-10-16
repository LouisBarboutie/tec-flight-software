#ifndef __PROCESSOR_HPP__
#define __PROCESSOR_HPP__

#include "Fdir.hpp"
#include "GenericComponent.hpp"
#include "ISensor.hpp"

#include <array>
#include <cstdint>
#include <string_view>

class Processor : public GenericComponent
{
  public:
    Processor(std::string_view name);

    void Step();
    uint64_t Period();

    std::array<ISensor *, 3> imuSensors{};
    std::array<ISensor *, 2> gnssSensors{};

  private:
    Fdir fdir;
};

#endif
