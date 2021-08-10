/*
 * for utility
 * */

#include "util.h"

void connect_lost(void *context, char *cause) {
    printf("connect lost due to %s\n", cause);
}

void mqtt_subscribe(MQTTAsync device, const char *topic) {
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    int rc;

    opts.onSuccess = NULL;
    opts.onFailure = NULL;
    opts.context = device;

    if ((rc = MQTTAsync_subscribe(device, topic, SUBSCRIBE_QoS, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start subscribe, return code %d\n", rc);
        return;
    }

    printf("Subscribe successfully\n");
}

void mqtt_close(MQTTAsync topic) {
    int rc = MQTTAsync_disconnect(topic, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        printf("Topic disconnect failed, return code %d\n", rc);
    }

    printf("Disconnect successfully\n");
    MQTTAsync_destroy(&topic);
}