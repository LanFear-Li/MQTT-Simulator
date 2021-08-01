#include "temp.h"
#include <sys/socket.h>

void temp_init(MQTTAsync *temp_sensor) {
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc;

    if ((rc = MQTTAsync_create(temp_sensor, SERVER_ADDRESS, TEMP_SENSOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to create client object, return code %d\n", rc);
        return;
    }

    if ((rc = MQTTAsync_setCallbacks(*temp_sensor, NULL, connect_lost, message_arrived, NULL)) != MQTTASYNC_SUCCESS) {
        printf("Failed to set callback, return code %d\n", rc);
        return;
    }

    conn_opts.keepAliveInterval = 100;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = NULL;
    conn_opts.onFailure = NULL;
    conn_opts.context = *temp_sensor;

    if ((rc = MQTTAsync_connect(*temp_sensor, &conn_opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start connect, return code %d\n", rc);
        return;
    }
    printf("Start connection successfully\n");
    printf("Waiting for publication " "on topic %s for client with ClientID: %s\n", EVENTBUS_TOPIC, TEMP_SENSOR_ID);
}

void temp_publish(MQTTAsync temp_sensor, int sensor_data) {
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message publish_message = MQTTAsync_message_initializer;
    int rc;

    /* set callback function */
    opts.onSuccess = NULL;
    opts.onFailure = NULL;
    opts.context = temp_sensor;

    char *str = malloc(3);
    printf("sensor data is %d\n", sensor_data);
    snprintf(str, 3, "%d", sensor_data);

    publish_message.payload = malloc(4);
    ((int *) publish_message.payload)[0] = sensor_data;

    publish_message.payloadlen = 1;
    publish_message.qos = 1;
    publish_message.retained = 0;

    if ((rc = MQTTAsync_sendMessage(temp_sensor, EVENTBUS_TOPIC, &publish_message, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to send message, return code %d\n", rc);
        return;
    }

    printf("Send message successfully\n");
}