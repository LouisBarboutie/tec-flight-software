#ifndef __GENERICCOMPONENT_HPP__
#define __GENERICCOMPONENT_HPP__

#include "IComponent.hpp"
#include "Logger.hpp"

#include <cstdint>
#include <string>
#include <string_view>

class GenericComponent : public IComponent
{
  public:
    GenericComponent(std::string_view name);
    std::string_view Name() override;

  protected:
    std::string name;

    void Log(const logging::Level level, const std::string_view message);
};

#endif
