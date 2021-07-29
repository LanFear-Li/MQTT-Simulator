#include "monitor.h"

void monitor_init(MQTTAsync *monitor) {
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc;

    if ((rc = MQTTAsync_create(monitor, SERVER_ADDRESS, MONITOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to create client object, return code %d\n", rc);
        return;
    }

    if ((rc = MQTTAsync_setCallbacks(*monitor, NULL, connect_lost, message_arrived, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to set callback, return code %d\n", rc);
        return;
    }

    conn_opts.keepAliveInterval = 100;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = NULL;
    conn_opts.onFailure = NULL;
    conn_opts.context = *monitor;

    if ((rc = MQTTAsync_connect(*monitor, &conn_opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start connect, return code %d\n", rc);
        return;
    }
    printf("Start connection successfully\n");
}

void monitor_subscribe(MQTTAsync monitor) {
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    int rc;

    opts.onSuccess = NULL;
    opts.onFailure = NULL;
    opts.context = monitor;

    printf("Subscribing to topic %s for client %s using QoS%d\n", EVENTBUS_TOPIC, MONITOR_ID, 1);

    if ((rc = MQTTAsync_subscribe(monitor, EVENTBUS_TOPIC, 1, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start subscribe, return code %d\n", rc);
        return;
    }

    printf("Get message successfully\n");
}