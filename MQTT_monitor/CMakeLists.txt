cmake_minimum_required(VERSION 3.20)
project(MQTT_monitor C)

set(CMAKE_C_STANDARD 11)

add_executable(MQTT_monitor main.c monitor.c util.c)

target_link_libraries(MQTT_monitor paho-mqtt3a)
