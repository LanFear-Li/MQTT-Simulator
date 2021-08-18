#ifndef MQTT_SIMULATOR_UTIL_H
#define MQTT_SIMULATOR_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include <uuid/uuid.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <MQTTAsync.h>

#define REQUEST_TOPIC       "request/"
#define RESPONSE_TOPIC      "response/"
#define SERVER_ADDRESS      "tcp://localhost:1883"
#define SENSOR_ID           "temp_sensor"
#define USER_ID             "ignoramus"

#define TRUE                1
#define FALSE               0
#define MAX_NAME_SIZE       100
#define MAX_THREAD_SCALE    100
#define ALIVE_INTERVAL      5
#define PUBLISH_QoS         1
#define SUBSCRIBE_QoS       1

typedef size_t bool;

void connect_lost(void *context, char *cause);

void mqtt_subscribe(MQTTAsync device, const char *topic);

void mqtt_close(MQTTAsync topic);

void msleep(long millisecond);

#endif //MQTT_SIMULATOR_UTIL_H
