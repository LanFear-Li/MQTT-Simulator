#ifndef MQTT_TEMP_CLIENT_TEMP_H
#define MQTT_TEMP_CLIENT_TEMP_H

#include "util.h"

void temp_init(MQTTAsync *temp_sensor);

void temp_publish(MQTTAsync temp_sensor, int sensor_data);

#endif //MQTT_TEMP_CLIENT_TEMP_H
