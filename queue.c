/*
 * concurrency queue
 * */

#include "queue.h"

void queue_init(queue *publish_queue) {
    publish_queue->head = publish_queue->tail = 0;
    sem_init(&publish_queue->queue_mutex, 0, 1);

    sem_init(&publish_queue->empty, 0, MAX_QUEUE_BUFFER_SIZE);
    sem_init(&publish_queue->full, 0, 0);
}

void publish_queue_push(queue *publish_queue, const char *uuid, int data) {
    sem_wait(&publish_queue->empty);
    sem_wait(&publish_queue->queue_mutex);
    sprintf(publish_queue->array[publish_queue->tail].uuid, "%s", uuid);
    publish_queue->array[publish_queue->tail].data = data;

    publish_queue->tail = (publish_queue->tail + 1) % MAX_QUEUE_BUFFER_SIZE;
    sem_post(&publish_queue->queue_mutex);
    sem_post(&publish_queue->full);
}

struct queue_item publish_queue_pop(queue *publish_queue) {
    sem_wait(&publish_queue->full);
    sem_wait(&publish_queue->queue_mutex);
    struct queue_item item = publish_queue->array[publish_queue->head];
    publish_queue->head = (publish_queue->head + 1) % MAX_QUEUE_BUFFER_SIZE;
    sem_post(&publish_queue->queue_mutex);
    sem_post(&publish_queue->empty);

    return item;
}