cmake_minimum_required(VERSION 3.16)
project(MQTT-Simulator C)

set(CMAKE_C_STANDARD 11)

add_executable(pub pub.c temp.c util.c)
add_executable(sub sub.c monitor.c util.c)

target_link_libraries(pub paho-mqtt3a)
target_link_libraries(sub paho-mqtt3a)
