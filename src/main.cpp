#include <cstdint>
#include <iostream>
#include <string_view>
#include <format>

#include "Scheduler.hpp"
#include "Logger.hpp"

class Component : public IComponent
{
  public:
    Component(std::string_view name) { this->name = name;}
    uint64_t Period() override { return 10; }
    void Step() override { logging::Log(logging::Level::INFO, std::format("{}: Step {} ", this->name, this->steps++)); }
    std::string_view Name() override { return this->name; }

  private:
    uint64_t steps{0};
    std::string name;
};

int main(void)
{
    logging::level = logging::Level::DEBUG;

    Scheduler scheduler;
    Component component1("Foo");
    Component component2("Bar");

    scheduler.AddComponent(&component1);
    scheduler.AddComponent(&component2);
    scheduler.AddComponent(&component2);

    scheduler.Run(100);

    Log(logging::Level::INFO, std::format("Ran for {} milliseconds", scheduler.CurrentTime()));

    return 0;
}
