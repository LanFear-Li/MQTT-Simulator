#ifndef MQTT_SIMULATOR_USER_H
#define MQTT_SIMULATOR_USER_H

#include "util.h"

void user_init();

void user_uuid_publish(char *sensor_name);

int user_request_callback(void *context, char *topic_name, int topic_len, MQTTAsync_message *message);

#endif //MQTT_SIMULATOR_USER_H
