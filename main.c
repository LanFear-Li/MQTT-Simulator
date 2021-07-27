#include "util.h"
#include "temp.h"

int main() {
    pthread_t threads[THREAD_SCALE];

    pthread_create(&threads[0], NULL, temp_publish, (void *) 0);
    pthread_join(threads[0], NULL);
    return 0;
}