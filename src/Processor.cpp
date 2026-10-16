#include "GenericComponent.hpp"
#include "Processor.hpp"
#include "Fdir.hpp"

#include <cstdint>
#include <string_view>

constexpr uint64_t PROCESSOR_FREQUENCY_HZ = 50;

Processor::Processor(std::string_view name) : GenericComponent(name)
{
    this->fdir = Fdir();
}

uint64_t Processor::Period() { return 1'000 / PROCESSOR_FREQUENCY_HZ; }

void Processor::Step()
{ // TODO
}
