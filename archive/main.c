#include "util.h"
#include "temp.h"
#include "monitor.h"

int main() {
    pthread_t threads[THREAD_SCALE];

    pthread_create(&threads[0], NULL, temp_publish, (void *) 0);
    pthread_create(&threads[1], NULL, monitor_subscribe, (void *) 1);
    pthread_join(threads[0], NULL);
    sleep(2);
    pthread_join(threads[1], NULL);

    return 0;
}