//2 reader writer meutex
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int data = 0;

void* writer(void* arg) {
    pthread_mutex_lock(&mutex);
    data++;
    printf("Writer updated data to %d\n", data);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Reader read data as %d\n", data);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t writers[2], readers[2];
    pthread_mutex_init(&mutex, NULL);

    // Create writer threads
    for (int i = 0; i < 3; i++)
        pthread_create(&writers[i], NULL, writer, NULL);

    // Create reader threads
    for (int i = 0; i < 3; i++)
        pthread_create(&readers[i], NULL, reader, NULL);

    // Join threads
    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
