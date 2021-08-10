/*
 * MQTT Sensor Client
 * Request-Response Model
 *
 * By LanFear
 * */

#include "sensor.h"

static MQTTAsync sensor;

static pthread_t data_thread, publish_thread;
static sem_t data_mutex;

static queue *publish_queue;

void sensor_init() {
    publish_queue = (queue *) malloc(sizeof(queue));
    queue_init(publish_queue);

    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc;

    rc = MQTTAsync_create(&sensor, SERVER_ADDRESS, SENSOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        printf("Failed to create while sub in sensor, return code %d\n", rc);
        return;
    }

    rc = MQTTAsync_setCallbacks(sensor, sensor, connect_lost, sensor_response_callback, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        printf("Failed to set callback while sub in sensor, return code %d\n", rc);
        return;
    }

    conn_opts.keepAliveInterval = ALIVE_INTERVAL;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = NULL;
    conn_opts.onFailure = NULL;
    conn_opts.context = sensor;

    rc = MQTTAsync_connect(sensor, &conn_opts);
    if (rc != MQTTASYNC_SUCCESS) {
        printf("Failed to start connect while sub in sensor, return code %d\n", rc);
        return;
    }

    printf("Start connection successfully while sub in sensor\n");
    sleep(1);

    size_t len = strlen(REQUEST_TOPIC) + strlen(SENSOR_ID) + 1;
    char topic[len];
    sprintf(topic, "%s%s", REQUEST_TOPIC, SENSOR_ID);

    mqtt_subscribe(sensor, topic);
}

void *sensor_data_publish() {
    while (TRUE) {
        printf("Sensor sending message...\n");

        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        MQTTAsync_message message = MQTTAsync_message_initializer;
        int rc;

        opts.onSuccess = NULL;
        opts.onFailure = NULL;
        opts.context = sensor;

        struct queue_item item = publish_queue_pop(publish_queue);

        message.payload = malloc(sizeof(int));
        ((int *) message.payload)[0] = item.data;

        message.payloadlen = sizeof(int);
        message.qos = PUBLISH_QoS;
        message.retained = TRUE;

        size_t len = strlen(RESPONSE_TOPIC) + strlen(SENSOR_ID) + 1 + UUID_STR_LEN + 1;
        char topic[len];
        sprintf(topic, "%s%s/%s", RESPONSE_TOPIC, SENSOR_ID, item.uuid);

        rc = MQTTAsync_sendMessage(sensor, topic, &message, &opts);
        if (rc != MQTTASYNC_SUCCESS) {
            printf("Failed to send message, return code %d\n", rc);
            return NULL;
        }

        printf("Send message successfully, sensor data is %d\n", item.data);
    }
}

int sensor_response_callback(void *context, char *topic_name, int topic_len, MQTTAsync_message *message) {
    printf("NOTICE: user request arrived\n");
    printf("uuid is %s\n", (char *) message->payload);

    sem_wait(&data_mutex);
    publish_queue_push(publish_queue, message->payload, data);
    sem_post(&data_mutex);

    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topic_name);
    return 1;
}

void *sensor_data_update() {
    sem_init(&data_mutex, 0, 1);

    while (TRUE) {
        sleep(1);

        sem_wait(&data_mutex);
        data = (int) random() % 80 + 20;
        sem_post(&data_mutex);
    }
}

int main() {
    sensor_init();

    pthread_create(&data_thread, NULL, sensor_data_update, NULL);
    pthread_create(&publish_thread, NULL, sensor_data_publish, NULL);
    pthread_join(data_thread, NULL);
    pthread_join(publish_thread, NULL);

    return 0;
}
