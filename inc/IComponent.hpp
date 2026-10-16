#include <cstdint>
#include <string_view>

class IComponent
{
  public:
    virtual void Step() = 0;
    virtual uint64_t Period() = 0;
    virtual std::string_view Name() = 0;
};
