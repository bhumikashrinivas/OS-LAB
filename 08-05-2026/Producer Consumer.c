#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 8   // Buffer size

int buffer[N];
int in = 0, out = 0;

// Semaphores
sem_t empty;   // Counts empty slots
sem_t full;    // Counts filled slots
pthread_mutex_t S; // Mutex lock

// Function to produce item
int produce_item() {
    static int item = 1;
    return item++;
}

// Function to consume item
void consume_item(int item) {
    printf("Item processed: %d\n", item);
}

// Producer thread
void* producer(void* arg) {
    int itemP;

   for(int i=0;i<3;i++) {
        itemP = produce_item();

        sem_wait(&empty);          // Wait for empty slot
        pthread_mutex_lock(&S);    // Enter critical section

        buffer[in] = itemP;
        printf("Produced: %d at position %d\n", itemP, in);

        in = (in + 1) % N;

        pthread_mutex_unlock(&S);  // Exit critical section
        sem_post(&full);           // Signal filled slot

        sleep(1);
    }

    return NULL;
}

// Consumer thread
void* consumer(void* arg) {
    int itemC;

    for(int i=0;i<3;i++) {
        sem_wait(&full);           // Wait for filled slot
        pthread_mutex_lock(&S);    // Enter critical section

        itemC = buffer[out];
        printf("Consumed: %d from position %d\n", itemC, out);

        out = (out + 1) % N;

        pthread_mutex_unlock(&S);  // Exit critical section
        sem_post(&empty);          // Signal empty slot

        consume_item(itemC);

        sleep(2);
    }

    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&S, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&S);

    return 0;
}


