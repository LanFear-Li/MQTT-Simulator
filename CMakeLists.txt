cmake_minimum_required(VERSION 3.19)
project(mqtt_simulator C)

set(CMAKE_C_STANDARD 11)

add_executable(mqtt_simulator main.c temp.c util.c)
target_link_libraries(mqtt_simulator pthread paho-mqtt3a)