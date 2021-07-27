#include "util.h"

void connect_lost(void *context, char *cause) {
    printf("connect lost.\n");
    printf("cause: %s\n", cause);
}

int message_arrived(void *context, char *topic_name, int topic_len, MQTTAsync_message *message) {
    /* nothing happen */
    return 1;
}

void on_disconnect(void *context, MQTTAsync_successData *response) {
    printf("Successful disconnection\n");
}

void on_disconnect_failure(void *context, MQTTAsync_failureData *response) {
    printf("Disconnect failed\n");
}

void on_send(void *context, MQTTAsync_successData *response) {
    MQTTAsync client = (MQTTAsync) context;
    MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
    int rc;

    printf("Message with token value %d delivery confirmed\n", response->token);
    opts.onSuccess = on_disconnect;
    opts.onFailure = on_disconnect_failure;
    opts.context = client;
    if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start disconnect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
}

void on_send_failure(void *context, MQTTAsync_failureData *response) {
    MQTTAsync client = (MQTTAsync) context;
    MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
    int rc;

    printf("Message send failed token %d error code %d\n", response->token, response->code);
    opts.onSuccess = on_disconnect;
    opts.onFailure = on_disconnect_failure;
    opts.context = client;
    if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start disconnect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
}