#include "GnssSensor.hpp"
#include "ImuSensor.hpp"
#include "Logger.hpp"
#include "Processor.hpp"
#include "Scheduler.hpp"

#include <format>
#include <string_view>
#include <unistd.h>

int scenario;

void Scenario1();
void Scenario2();
void Scenario3();

int main(int argc, char* argv[])
{
    logging::level = logging::Level::INFO;
    int opt;
    while ((opt = getopt(argc, argv, "ds:")) != -1) {
        switch (opt) {
        case 'd':
            logging::level = logging::Level::DEBUG;
        case 's':
            scenario = std::atoi(optarg);
            Log(logging::Level::INFO, std::format("Selected scenario {}", scenario));
            break;
        }
    }

    switch (scenario) {
    case 1:
        Scenario1();
        break;
    case 2:
        Scenario2();
        break;
    case 3:
        Scenario3();
        break;
    default:
        Log(logging::Level::ERROR, "Unknown scenario ID");
    }

    return 0;
}

// Nominal run for 10s
void Scenario1()
{

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

    scheduler.Run(10 * SECOND);
}

// Subsequent dropout of all IMUs
void Scenario2()
{
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

    scheduler.ScheduleEvent({.time = 3 * SECOND, .period = 0, .action = [&imu1]() { imu1.InjectFailure(); }});
    scheduler.ScheduleEvent({.time = 5 * SECOND, .period = 0, .action = [&imu2]() { imu2.InjectFailure(); }});
    scheduler.ScheduleEvent({.time = 7 * SECOND, .period = 0, .action = [&imu3]() { imu3.InjectFailure(); }});

    scheduler.Run(10 * SECOND);
}

// Temporary GNSS dropout
void Scenario3()
{
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

    scheduler.ScheduleEvent({.time = 3 * SECOND, .period = 0, .action = [&gnss1, &gnss2]() {
                                 gnss1.InjectFailure();
                                 gnss2.InjectFailure();
                             }});

    // Unfail after 500ms
    scheduler.ScheduleEvent({.time = static_cast<uint64_t>(3.5 * SECOND), .period = 0, .action = [&gnss1, &gnss2]() {
                                 gnss1.ClearFailure();
                                 gnss2.ClearFailure();
                             }});

    scheduler.Run(10 * SECOND);
}
