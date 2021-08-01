//
// Created by lanfear on 2021/7/24.
//

#ifndef MQTT_SIMULATOR_TEMP_H
#define MQTT_SIMULATOR_TEMP_H

#include "util.h"

void *temp_publish(void *thread_id);

void temp_on_connect(void *context, MQTTAsync_successData *response);

void temp_on_connect_failure(void *context, MQTTAsync_failureData *response);

#endif //MQTT_SIMULATOR_TEMP_H
