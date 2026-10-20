#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "Scheduler.hpp"

#include <format>
#include <iostream>
#include <string_view>

namespace logging
{

enum class Level {
    ERROR = 0,
    WARNING = 1,
    INFO = 2,
    DEBUG = 3,
};

inline Level level;

constexpr std::string_view color(Level level)
{
    switch (level) {
    case Level::ERROR:
        return "\033[31m";
    case Level::WARNING:
        return "\033[33m";
    case Level::INFO:
        return "\033[37m";
    case Level::DEBUG:
        return "\033[32m";
    }
    return "";
}

constexpr std::string_view name(Level level)
{
    switch (level) {
    case Level::ERROR:
        return "ERROR";
    case Level::WARNING:
        return "WARNING";
    case Level::INFO:
        return "INFO";
    case Level::DEBUG:
        return "DEBUG";
    }
    return "";
}

inline void Log(Level level, std::string_view message)
{
    if (logging::level < level)
        return;

    std::cout << std::format("{}{:06d} [{}] {}\033[0m", color(level), scheduler.CurrentTime(), name(level), message)
              << std::endl;
    ;
};

} // namespace logging

#endif
