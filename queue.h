#ifndef MQTT_SIMULATOR_QUEUE_H
#define MQTT_SIMULATOR_QUEUE_H

#include "util.h"

#define MAX_QUEUE_BUFFER_SIZE   1024

struct queue_item {
    char uuid[UUID_STR_LEN + 1];
    int data;
};

typedef struct queue {
    struct queue_item array[MAX_QUEUE_BUFFER_SIZE];
    volatile size_t head, tail;

    sem_t queue_mutex;
    sem_t empty, full;
} queue;

void queue_init(queue *publish_queue);

void publish_queue_push(queue *publish_queue, const char *uuid, int data);

struct queue_item publish_queue_pop(queue *publish_queue);

#endif //MQTT_SIMULATOR_QUEUE_H
