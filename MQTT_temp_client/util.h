#ifndef MQTT_SIMULATOR_UTIL_H
#define MQTT_SIMULATOR_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include "MQTTAsync.h"

#define SERVER_ADDRESS      "tcp://localhost:1883"
#define EVENTBUS_TOPIC      "eventbus"

#define PAYLOAD             "surprise motherfucker!"

#define TEMP_SENSOR_ID      "temp_sensor_pub"
#define LIGHT_SENSOR_ID     "light_sensor_pub"
#define MONITOR_ID          "monitor_sub"
#define THREAD_SCALE        3

void connect_lost(void *context, char *cause);

int message_arrived(void *context, char *topic_name, int topic_len, MQTTAsync_message *message);

void on_disconnect(void *context, MQTTAsync_successData *response);

void on_disconnect_failure(void *context, MQTTAsync_failureData *response);

#endif //MQTT_SIMULATOR_UTIL_H
