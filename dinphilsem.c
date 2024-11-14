//7 dining phil semaphore
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;

    printf("Philosopher %d is thinking.\n", id);
    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

    printf("Philosopher %d is eating.\n", id);
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);

    printf("Philosopher %d finished eating.\n", id);
    return NULL;
}

int main() {
    int ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
