#ifndef MQTT_SIMULATOR_MONITOR_H
#define MQTT_SIMULATOR_MONITOR_H

#include "util.h"

void monitor_init(MQTTAsync *temp_sensor);

void monitor_subscribe(MQTTAsync monitor);

#endif //MQTT_SIMULATOR_MONITOR_H
