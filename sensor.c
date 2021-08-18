/*
 * MQTT Sensor Client
 * Request-Response Model
 *
 * By LanFear
 * */

#include "sensor.h"

static MQTTAsync sensor;

static pthread_t data_thread, multi_thread[MAX_THREAD_SCALE];
static pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER, handle_mutex = PTHREAD_MUTEX_INITIALIZER;

static queue *publish_queue;
static int publish_QoS = 1;

static bool is_clock_begin;
static clock_t begin;
static long exec_counter;

void sensor_init() {
    publish_queue = (queue *) malloc(sizeof(queue));
    queue_init(publish_queue);

    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc;

    rc = MQTTAsync_create(&sensor, SERVER_ADDRESS, SENSOR_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to create while sub in sensor, return code %d\n", rc);
        return;
    }

    rc = MQTTAsync_setCallbacks(sensor, sensor, connect_lost, sensor_response_callback, NULL);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to set callback while sub in sensor, return code %d\n", rc);
        return;
    }

    conn_opts.keepAliveInterval = ALIVE_INTERVAL;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = NULL;
    conn_opts.onFailure = NULL;
    conn_opts.context = sensor;

    rc = MQTTAsync_connect(sensor, &conn_opts);
    if (rc != MQTTASYNC_SUCCESS) {
        // printf("Failed to start connect while sub in sensor, return code %d\n", rc);
        return;
    }

    // printf("Start connection successfully while sub in sensor\n");
    sleep(1);

    size_t len = strlen(REQUEST_TOPIC) + strlen(SENSOR_ID) + 1;
    char topic[len];
    sprintf(topic, "%s%s", REQUEST_TOPIC, SENSOR_ID);

    mqtt_subscribe(sensor, topic);
}

void *sensor_handle_request() {
    while (TRUE) {
        struct queue_item item = publish_queue_pop(publish_queue);

        // printf("Sensor handling request...\n");
        int time = (int) random() % 50 + 1;
        msleep(time);

        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        MQTTAsync_message message = MQTTAsync_message_initializer;
        int rc;

        opts.onSuccess = NULL;
        opts.onFailure = NULL;
        opts.context = sensor;

        message.payload = malloc(sizeof(int));
        ((int *) message.payload)[0] = item.data;

        message.payloadlen = sizeof(int);
        message.qos = publish_QoS;
        message.retained = TRUE;

        size_t len = strlen(RESPONSE_TOPIC) + strlen(SENSOR_ID) + 1 + UUID_STR_LEN + 1;
        char topic[len];
        sprintf(topic, "%s%s/%s", RESPONSE_TOPIC, SENSOR_ID, item.uuid);

        // printf("Sensor sending message...\n");
        rc = MQTTAsync_sendMessage(sensor, topic, &message, &opts);
        if (rc != MQTTASYNC_SUCCESS) {
            // printf("Failed to send message, return code %d\n", rc);
            return NULL;
        }

        // printf("Send message successfully, sensor data is %d\n", item.data);

        pthread_mutex_lock(&handle_mutex);
        exec_counter++;
        pthread_mutex_unlock(&handle_mutex);
    }
}

int sensor_response_callback(void *context, char *topic_name, int topic_len, MQTTAsync_message *message) {
    // printf("NOTICE: user request arrived\n");
    // printf("uuid is %s\n", (char *) message->payload);

    if (is_clock_begin == FALSE) {
        begin = clock();
        is_clock_begin = TRUE;
        // printf("clock begin at %ld\n", begin);
    }

    pthread_mutex_lock(&data_mutex);
    publish_queue_push(publish_queue, message->payload, data);
    pthread_mutex_unlock(&data_mutex);

    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topic_name);
    return 1;
}

void *sensor_data_update() {
    while (TRUE) {
        sleep(1);

        int temp_data = (int) random() % 80 + 20;
        long temp_clock;

        pthread_mutex_lock(&data_mutex);
        data = temp_data;
        
        temp_clock = clock();
        if (temp_clock > begin + 1000) {
            // printf("clock end is %ld\n", temp_clock);
             printf("%ld", exec_counter);
            exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&data_mutex);
    }
}

int main(int argc, char **argv) {
    long thread_scale = 1;
    int c;
    while ((c = getopt(argc, argv, "q:t:")) != -1) {
        switch (c) {
            case 'q':
                publish_QoS = (int) strtol(optarg, NULL, 10);
                break;
            case 't':
                thread_scale = strtol(optarg, NULL, 10);
                break;
            case '?':
                // printf("Invalid option\n");
                return -1;
            default:
                break;
        }
    }

    if (thread_scale > MAX_THREAD_SCALE) {
        // printf("Thread scale exceeded\n");
        return -1;
    }

    sensor_init();

    for (long i = 0; i < thread_scale; ++i) {
        pthread_create(&multi_thread[i], NULL, sensor_handle_request, NULL);
    }
    pthread_create(&data_thread, NULL, sensor_data_update, NULL);

    pthread_join(data_thread, NULL);
    return 0;
}
