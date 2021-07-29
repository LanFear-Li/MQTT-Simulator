#include "monitor.h"

int main() {
    MQTTAsync monitor;
    monitor_init(&monitor);

    sleep(5);
    monitor_subscribe(monitor);


    while (1) {

    }

    return 0;
}
