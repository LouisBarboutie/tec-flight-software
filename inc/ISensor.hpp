#ifndef __ISENSOR_HPP__
#define __ISENSOR_HPP__

#include <cstdint>
#include <optional>

struct Vec3 {
    int32_t x{};
    int32_t y{};
    int32_t z{};
};

struct Measurement {
    uint64_t timestamp{};
    Vec3 data{};
};

class ISensor
{
  public:
    virtual void InjectFailure() = 0;
    virtual void ClearFailure() = 0;
    virtual std::optional<Measurement> ReadData() = 0;
};

#endif
