#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include <format>

struct Vec3 {
    double x{};
    double y{};
    double z{};
};

static Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
    Vec3 res{};
    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    res.z = lhs.z + rhs.z;

    return res;
}

static Vec3 operator*(const double lhs, const Vec3& rhs)
{
    Vec3 res{};
    res.x = lhs * rhs.x;
    res.y = lhs * rhs.y;
    res.z = lhs * rhs.z;

    return res;
}

template <> struct std::formatter<Vec3> : std::formatter<std::string_view> {
    auto format(const Vec3& vec, std::format_context& ctx) const
    {
        std::string temp;
        std::format_to(std::back_inserter(temp), "(x={}, y={}, z={})", vec.x, vec.y, vec.z);
        return std::formatter<std::string_view>::format(temp, ctx);
    }
};

#endif
