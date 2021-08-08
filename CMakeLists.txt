cmake_minimum_required(VERSION 3.16)
project(MQTT-Simulator C)

set(CMAKE_C_STANDARD 11)

add_executable(sensor sensor.c util.c queue.c)
add_executable(user user.c util.c)

target_link_libraries(sensor paho-mqtt3a pthread)
target_link_libraries(user paho-mqtt3a uuid)
