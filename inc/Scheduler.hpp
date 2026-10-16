#include <cstdint>
#include <queue>
#include <set>
#include <vector>
#include <functional>

#include "IComponent.hpp"

struct Event {
    uint64_t time{};
    uint64_t period{};
    std::function<void(void)> action;
};

struct CompareTime {
    bool operator()(const Event &a, const Event &b) const { return a.time > b.time; }
};

class Scheduler
{
  public:
    void Run(uint64_t millis);
    void Step();
    uint64_t CurrentTime();
    void AddComponent(IComponent *component);
    const std::set<IComponent*>& Components();

  private:
    uint64_t millis{0};
    std::priority_queue<Event, std::vector<Event>, CompareTime> events{};
    std::set<IComponent*> components;
};
