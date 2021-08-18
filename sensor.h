#ifndef MQTT_SIMULATOR_SENSOR_H
#define MQTT_SIMULATOR_SENSOR_H

#include "util.h"
#include "queue.h"

static int data;

void sensor_init();

int sensor_response_callback(void *context, char *topic_name, int topic_len, MQTTAsync_message *message);

void *sensor_handle_request();

void *sensor_data_update();

#endif //MQTT_SIMULATOR_SENSOR_H
