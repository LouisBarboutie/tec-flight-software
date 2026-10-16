#include <cstdint>
#include <format>
#include <string_view>
#include <unistd.h>

#include "GnssSensor.hpp"
#include "ImuSensor.hpp"
#include "Logger.hpp"
#include "Processor.hpp"
#include "Scheduler.hpp"

int main(int argc, char *argv[])
{
    logging::level = logging::Level::INFO;

    while (int opt = getopt(argc, argv, "d") != -1) {
        switch (opt) {
        case 'd':
            logging::level = logging::Level::DEBUG;
        }
    }

    Processor processor("Processor");
    ImuSensor imu1("IMU_1"), imu2("IMU_2"), imu3("IMU_3");
    GnssSensor gnss1("GNSS_1"), gnss2("GNSS_2");

    processor.imuSensors[0] = &imu1;
    processor.imuSensors[1] = &imu2;
    processor.imuSensors[2] = &imu3;

    processor.gnssSensors[0] = &gnss1;
    processor.gnssSensors[1] = &gnss2;

    scheduler.AddComponent(&processor);
    scheduler.AddComponent(&imu1);
    scheduler.AddComponent(&imu2);
    scheduler.AddComponent(&imu3);
    scheduler.AddComponent(&gnss1);
    scheduler.AddComponent(&gnss2);

    scheduler.ScheduleEvent({.time = 42, .period = 0, .action = []() { Log(logging::Level::ERROR, "ERror"); }});

    scheduler.Run(100);

    Log(logging::Level::INFO, std::format("Ran for {} milliseconds", scheduler.CurrentTime()));

    return 0;
}
