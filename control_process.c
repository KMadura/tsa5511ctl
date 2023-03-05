#include <pthread.h>

pthread_mutex_t mutex_mon = PTHREAD_MUTEX_INITIALIZER;

void* start_monitoring_process() {
    while(true) {
        pthread_mutex_lock(&mutex_mon);

        /* TODO: check if device is still running, if not try to reconnect */

        /* TODO: check if frequency is set to required one, if not then change it */

        /* TODO: check if lock is set to current required value, if not try to change it */

        /* TODO: add more checks */

        pthread_mutex_unlock(&mutex_mon);

        sleep(20);

        // Remove this break, it exists only for debugging purposes
        break;
    }

    return NULL;
}