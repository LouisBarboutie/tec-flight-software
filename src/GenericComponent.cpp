#include "GenericComponent.hpp"

#include <format>
#include <string_view>

GenericComponent::GenericComponent(std::string_view name) { this->name = name; }

std::string_view GenericComponent::Name() const { return this->name; }

void GenericComponent::Log(const logging::Level level, const std::string_view message)
{
    logging::Log(level, std::format("{}: {}", this->name, message));
}
