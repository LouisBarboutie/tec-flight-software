cmake_minimum_required(VERSION 4.4.4)

project(TecFlightSoftware)

add_executable(TecFlightSoftware)

file(GLOB SOURCES src/*)

target_sources(TecFlightSoftware
    PRIVATE
	${SOURCES}
)

target_include_directories(TecFlightSoftware PRIVATE inc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
