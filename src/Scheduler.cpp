#include "Scheduler.hpp"

#include "Logger.hpp"

#include <cstdint>

void Scheduler::Run(uint64_t millis)
{
    logging::Log(logging::Level::INFO, std::format("Starting scheduler run for {} ms", millis));

    while (this->millis < millis) {
        Step();
        this->millis++;
    }

    logging::Log(logging::Level::INFO, std::format("Stopping scheduler after run for {} ms", millis));
}

void Scheduler::Step()
{
    while (!this->events.empty() && this->events.top().time <= this->millis) {
        Event event = this->events.top();
        this->events.pop();

        event.action();

        if (event.period > 0) {
            event.time += event.period;
            this->events.push(event);
        }
    }
}

uint64_t Scheduler::CurrentTime() { return this->millis; }

void Scheduler::AddComponent(IComponent* component)
{
    // Duplicates are not allowed
    if (this->components.contains(component))
        return;

    this->events.push({.time = 0, .period = component->Period(), .action = std::bind(&IComponent::Step, component)});
    this->components.insert(component);

    logging::Log(logging::Level::INFO, std::format("Registered component '{}' in scheduler", component->Name()));
}

const std::set<IComponent*>& Scheduler::Components() { return this->components; }

void Scheduler::ScheduleEvent(const Event event) { this->events.push(event); }
