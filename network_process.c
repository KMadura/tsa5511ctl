#include <pthread.h>

pthread_mutex_t mutex_net = PTHREAD_MUTEX_INITIALIZER;

void* start_networking_process() {
    /*
     * TODO: implement a network loop
     * this function should seek UDP packets and respond to them
     * some of those queries will only receive values stored in this program / daemon
     * some other of those queries will directly instruct TSA5511 chip
     * any communication with TSA5511 should use mutex to prevent race condition with
     * control thread
     */

    sleep(20);

    return NULL;
}