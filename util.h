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

#define TEMP_SENSOR_ID      "temp_sensor_pub"
#define MONITOR_ID          "monitor_sub"

void connect_lost(void *context, char *cause);

int message_arrived(void *context, char *topic_name, int topic_len, MQTTAsync_message *message);

void on_disconnect(void *context, MQTTAsync_successData *response);

void on_disconnect_failure(void *context, MQTTAsync_failureData *response);

void on_send(void *context, MQTTAsync_successData *response);

void on_send_failure(void *context, MQTTAsync_failureData *response);

void on_subscribe(void* context, MQTTAsync_successData* response);

void on_subscribe_failure(void* context, MQTTAsync_failureData* response);

#endif //MQTT_SIMULATOR_UTIL_H
