//
// Created by lanfear on 2021/7/27.
//

#ifndef MQTT_SIMULATOR_MONITOR_H
#define MQTT_SIMULATOR_MONITOR_H

#include "util.h"

void *monitor_subscribe(void *thread_id);

int monitor_message_arrived(void *context, char *topic_name, int topic_len, MQTTAsync_message *message);

void monitor_on_connect(void *context, MQTTAsync_successData *response);

void monitor_on_connect_failure(void *context, MQTTAsync_successData *response);

#endif //MQTT_SIMULATOR_MONITOR_H
