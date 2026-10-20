#ifndef __MEASUREMENT_HPP__
#define __MEASUREMENT_HPP__

#include <cstdint>
#include <format>

struct Vec3 {
    int32_t x{};
    int32_t y{};
    int32_t z{};
};

struct Measurement {
    uint64_t timestamp{};
    Vec3 data{};
};

template <> struct std::formatter<Measurement> : std::formatter<std::string_view> {
    auto format(const Measurement& measurement, std::format_context& ctx) const
    {
        std::string temp;
        std::format_to(std::back_inserter(temp),
                       "(t={}, x={}, y={}, z={})",
                       measurement.timestamp,
                       measurement.data.x,
                       measurement.data.y,
                       measurement.data.z);
        return std::formatter<std::string_view>::format(temp, ctx);
    }
};

#endif
