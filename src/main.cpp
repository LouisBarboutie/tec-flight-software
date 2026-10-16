#include <cstdint>
#include <iostream>
#include <string_view>

#include "Scheduler.hpp"

class Component : public IComponent
{
  public:
    Component(std::string_view name) { this->name = name;}
    uint64_t Period() override { return 10; }
    void Step() override { std::clog << "Step! " << this->name << " " << this->steps++ << std::endl; }
    std::string_view Name() override { return this->name; }

  private:
    uint64_t steps{0};
    std::string name;
};

int main(void)
{
    Scheduler scheduler;
    Component component1("Foo");
    Component component2("Bar");

    scheduler.AddComponent(&component1);
    scheduler.AddComponent(&component2);

    scheduler.Run(100);

    std::clog << "Ran for " << scheduler.CurrentTime() << " milliseconds" << std::endl;

    return 0;
}
