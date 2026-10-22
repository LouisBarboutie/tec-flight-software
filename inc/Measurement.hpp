#ifndef __MEASUREMENT_HPP__
#define __MEASUREMENT_HPP__

#include "Vec3.hpp"

#include <format>

struct Measurement {
    uint64_t timestamp{};
    uint8_t id{};
    Vec3 data{};
};

template <> struct std::formatter<Measurement> : std::formatter<std::string_view> {
    auto format(const Measurement& measurement, std::format_context& ctx) const
    {
        std::string temp;
        std::format_to(std::back_inserter(temp),
                       "(id={}, t={}, x={}, y={}, z={})",
                       measurement.id,
                       measurement.timestamp,
                       measurement.data.x,
                       measurement.data.y,
                       measurement.data.z);
        return std::formatter<std::string_view>::format(temp, ctx);
    }
};

#endif
