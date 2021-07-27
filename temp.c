#include "temp.h"

void *temp_publish(void *thread_id) {
    long tid = (long) thread_id;
    printf("thread No.%ld\n", tid);

    MQTTAsync temp_sensor;
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc;

    if ((rc = MQTTAsync_create(&temp_sensor, SERVER_ADDRESS, TEMP_SENSOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to create client object, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    if ((rc = MQTTAsync_setCallbacks(temp_sensor, NULL, connect_lost, message_arrived, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to set callback, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = temp_on_connect;
    conn_opts.onFailure = temp_on_connect_failure;
    conn_opts.context = temp_sensor;

    if ((rc = MQTTAsync_connect(temp_sensor, &conn_opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for publication "
           "on topic %s for client with ClientID: %s\n",
           EVENTBUS_TOPIC, TEMP_SENSOR_ID);

    sleep(1);
}

void temp_on_connect(void *context, MQTTAsync_successData *response) {
    MQTTAsync client = (MQTTAsync) context;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message publish_message = MQTTAsync_message_initializer;
    int rc;

    printf("Successful connection\n");
    opts.onSuccess = on_send;
    opts.onFailure = on_send_failure;
    opts.context = client;

    char *str = malloc(4);
    int sensor_data = (int) (random() % 80) + 20;
    printf("sensor data is %d\n", sensor_data);
    snprintf(str, 4, "%d", sensor_data);

    publish_message.payload = str;
    publish_message.payloadlen = 4;
    publish_message.qos = 2;
    publish_message.retained = 0;

    MQTTAsync_sendMessage(client, EVENTBUS_TOPIC, &publish_message, &opts);
}

void temp_on_connect_failure(void *context, MQTTAsync_failureData *response) {
    printf("Connect failed, rc %d\n", response ? response->code : 0);
}