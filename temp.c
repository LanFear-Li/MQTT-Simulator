#include "temp.h"

void *temp_publish(void *thread_id) {
    long tid = (long) thread_id;
    printf("thread No.%ld\n", tid);

    MQTTAsync temp_sensor;
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    MQTTAsync_create(&temp_sensor, SERVER_ADDRESS, TEMP_SENSOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTAsync_setCallbacks(temp_sensor, NULL, connect_lost, message_arrived, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = temp_on_connect;
    conn_opts.onFailure = temp_on_connect_failure;
    conn_opts.context = temp_sensor;

    MQTTAsync_connect(temp_sensor, &conn_opts);
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

    publish_message.payload = (void *) (random() * 10 + 20);
    publish_message.payloadlen = 2;
    publish_message.qos = 1;
    publish_message.retained = 0;

    MQTTAsync_sendMessage(client, EVENTBUS_TOPIC, &publish_message, &opts);
}

void temp_on_connect_failure(void *context, MQTTAsync_failureData *response) {
    printf("Connect failed, rc %d\n", response ? response->code : 0);
}