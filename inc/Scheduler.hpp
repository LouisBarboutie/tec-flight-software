#include <cstdint>

class Scheduler
{
  public:
    void Run(uint64_t millis);

  private:
    uint64_t millis{0};
};
