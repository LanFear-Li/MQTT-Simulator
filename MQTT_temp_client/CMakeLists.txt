cmake_minimum_required(VERSION 3.19)
project(MQTT_temp_client C)

set(CMAKE_C_STANDARD 11)

add_executable(MQTT_temp_client main.c temp.c util.c)

target_link_libraries(MQTT_temp_client paho-mqtt3a)