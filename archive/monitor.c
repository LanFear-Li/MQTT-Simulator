//
// Created by lanfear on 2021/7/27.
//

#include "monitor.h"

void *monitor_subscribe(void *thread_id) {
    long tid = (long) thread_id;
    printf("thread No.%ld\n", tid);

    MQTTAsync monitor;
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
    int rc;
    int ch;

    if ((rc = MQTTAsync_create(&monitor, SERVER_ADDRESS, MONITOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) !=
        MQTTASYNC_SUCCESS) {
        printf("Failed to create client object, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    if ((rc = MQTTAsync_setCallbacks(monitor, NULL, connect_lost, monitor_message_arrived, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to set callback, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = monitor_on_connect;
    conn_opts.onFailure = monitor_on_connect_failure;
    conn_opts.context = monitor;

    if ((rc = MQTTAsync_connect(monitor, &conn_opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    sleep(2);
}

void monitor_on_connect(void *context, MQTTAsync_successData *response) {
    MQTTAsync client = (MQTTAsync) context;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    int rc;

    printf("Successful connection\n");

    printf("Subscribing to topic %s for client %s using QoS%d\n", EVENTBUS_TOPIC, MONITOR_ID, 2);

    opts.onSuccess = on_subscribe;
    opts.onFailure = on_subscribe_failure;
    opts.context = client;
    if ((rc = MQTTAsync_subscribe(client, EVENTBUS_TOPIC, 2, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start subscribe, return code %d\n", rc);
    }
}

void monitor_on_connect_failure(void *context, MQTTAsync_successData *response) {
    printf("Disconnect failed\n");
}

int monitor_message_arrived(void *context, char *topic_name, int topic_len, MQTTAsync_message *message) {
    printf("Message arrived\n");
    printf("     topic: %s\n", topic_name);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topic_name);
    return 1;
}