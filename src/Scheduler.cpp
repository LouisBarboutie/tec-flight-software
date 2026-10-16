#include "Scheduler.hpp"

#include <iostream>

void Scheduler::Run(uint64_t millis)
{
    while (this->millis < millis) {
        this->millis++;
    }

    std::clog << "Ran for " << this->millis << " milliseconds" << std::endl;
}
