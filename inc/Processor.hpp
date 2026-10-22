#ifndef __PROCESSOR_HPP__
#define __PROCESSOR_HPP__

#include "Fdir.hpp"
#include "GenericComponent.hpp"
#include "GnssSensor.hpp"
#include "ImuSensor.hpp"

#include <array>
#include <cstdint>
#include <string_view>

class Processor : public GenericComponent
{
  public:
    Processor(std::string_view name);

    void Step();
    uint64_t Period() const;

    void Init();

    std::array<ImuSensor*, 3> imuSensors{};
    std::array<GnssSensor*, 2> gnssSensors{};

  private:
    Fdir fdir;
    bool isImuDataAvailable{false};
    bool isGnssDataAvailable{false};
    std::vector<Measurement> imuMeasurements{};
    std::vector<Measurement> gnssMeasurements{};
    Vec3 ComputeAverage(const std::vector<Measurement>& measurements);
};

#endif
