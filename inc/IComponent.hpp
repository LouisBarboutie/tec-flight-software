#ifndef __ICOMPONENT_HPP__
#define __ICOMPONENT_HPP__

#include <cstdint>
#include <string_view>

class IComponent
{
  public:
    virtual void Step() = 0;
    virtual uint64_t Period() const = 0;
    virtual std::string_view Name() const = 0;
};

#endif
