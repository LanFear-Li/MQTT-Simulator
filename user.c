/*
 * MQTT User Client
 * Request-Response Model
 *
 * By LanFear
 * */

#include "user.h"

static MQTTAsync user;

static sem_t request_con;

void user_init() {
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc;

    rc = MQTTAsync_create(&user, SERVER_ADDRESS, USER_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to create client object, return code %d\n", rc);
        return;
    }

    rc = MQTTAsync_setCallbacks(user, NULL, connect_lost, user_request_callback, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to set callback, return code %d\n", rc);
        return;
    }

    conn_opts.keepAliveInterval = ALIVE_INTERVAL;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = NULL;
    conn_opts.onFailure = NULL;
    conn_opts.context = user;

    rc = MQTTAsync_connect(user, &conn_opts);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to start connect, return code %d\n", rc);
        return;
    }

    // printf("Start connection successfully\n");
    sleep(1);
}

void user_uuid_publish(char *sensor_name) {
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message message = MQTTAsync_message_initializer;
    int rc;

    opts.onSuccess = NULL;
    opts.onFailure = NULL;
    opts.context = user;

    uuid_t binuuid;
    char uuid[UUID_STR_LEN + 1];

    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    uuid[UUID_STR_LEN] = '\0';

    message.payload = uuid;
    message.payloadlen = UUID_STR_LEN;
    message.qos = PUBLISH_QoS;
    message.retained = TRUE;

    size_t len = strlen(REQUEST_TOPIC) + strlen(sensor_name) + 1;
    char publish_topic[len];
    sprintf(publish_topic, "%s%s", REQUEST_TOPIC, sensor_name);

    rc = MQTTAsync_sendMessage(user, publish_topic, &message, &opts);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to send message, return code %d\n", rc);
        return;
    }
    // printf("Send uuid successfully\n");

    len = strlen(RESPONSE_TOPIC) + strlen(sensor_name) + 1 + UUID_STR_LEN + 1;
    char subscribe_topic[len];
    sprintf(subscribe_topic, "%s%s/%s", RESPONSE_TOPIC, sensor_name, uuid);

    mqtt_subscribe(user, subscribe_topic);
}

int user_request_callback(void *context, char *topic_name, int topic_len, MQTTAsync_message *message) {
    sem_post(&request_con);

    // printf("NOTICE: data message arrived\n");
    // printf("topic: %s\n", topic_name);
    // printf("message: %d\n", *(int *) message->payload);
    MQTTAsync_freeMessage(&message);
    return 1;
}

int main() {
    user_init();

    sem_init(&request_con, 0, 0);
    while (TRUE) {
        user_uuid_publish(SENSOR_ID);
        sem_wait(&request_con);
    }

    return 0;
}