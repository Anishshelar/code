//13 producer consumer semaphore
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty_slots;  // Tracks empty slots in the buffer
sem_t full_slots;   // Tracks full slots in the buffer
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty_slots);      // Wait if buffer is full
        pthread_mutex_lock(&mutex);   // Lock the buffer

        buffer[count++] = i;          // Produce an item
        printf("Produced: %d\n", i);

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full_slots);        // Increment full slots
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full_slots);        // Wait if buffer is empty
        pthread_mutex_lock(&mutex);   // Lock the buffer

        int item = buffer[--count];   // Consume an item
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty_slots);       // Increment empty slots
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty_slots, 0, BUFFER_SIZE);  // Buffer initially empty
    sem_init(&full_slots, 0, 0);             // No items initially

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}
