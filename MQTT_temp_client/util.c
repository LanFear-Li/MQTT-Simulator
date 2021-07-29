#include "util.h"

void connect_lost(void *context, char *cause) {
    printf("connect lost.\n");
    printf("cause: %s\n", cause);
}

int message_arrived(void *context, char *topic_name, int topic_len, MQTTAsync_message *message) {
    /* nothing happen */
    return 1;
}