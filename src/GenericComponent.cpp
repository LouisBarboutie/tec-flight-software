#include "GenericComponent.hpp"

#include <cstdint>
#include <format>
#include <string_view>

GenericComponent::GenericComponent(std::string_view name) { this->name = name; }

std::string_view GenericComponent::Name() { return this->name; }

void GenericComponent::Log(const logging::Level level, const std::string_view message)
{
    logging::Log(level, std::format("{}: {}", this->name, message));
}

void GenericComponent::Step()
{
    // To be implemented by derived class
}

uint64_t GenericComponent::Period()
{
    // To be implemented by derived class
    return 0;
}
