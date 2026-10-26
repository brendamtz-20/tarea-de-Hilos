#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

#define N 10000
#define BLOQUE 10

void* count_down(void* arg);

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, count_down, NULL) != 0) {
        perror("Error al crear el hilo");
        return EXIT_FAILURE;
    }
    for (int i = 1; i <= N; i++) {
        printf("Ascendente: %d\n", i);
        if (i % BLOQUE == 0) {
            fflush(stdout);
            sched_yield();
        }
    }
    pthread_join(thread, NULL);
    return 0;
}

void* count_down(void* arg) {
    (void)arg;
    for (int i = N; i >= 1; i--) {
        printf("Descendente: %d\n", i);

        if (i % BLOQUE == 0) {
            fflush(stdout);
            sched_yield();
        }
    }

    return NULL;
}