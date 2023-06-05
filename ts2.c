#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 3

// Semaphore declarations
sem_t red_light_sem;
sem_t yellow_light_sem;
sem_t green_light_sem;

void* redLight(void* arg) {
    while (1) {
        sem_wait(&red_light_sem);  
        printf("RED LIGHT: Stop!\n");
        sleep(5);  
        
        sem_post(&yellow_light_sem);  
    }
}

void* yellowLight(void* arg) {
    while (1) {
        sem_wait(&yellow_light_sem);  

        printf("YELLOW LIGHT: Prepare to stop!\n");
        sleep(2);  
        
        sem_post(&green_light_sem);  
    }
}

void* greenLight(void* arg) {
    while (1) {
        sem_wait(&green_light_sem);  

        printf("GREEN LIGHT: Go!\n");
        sleep(5);  
        
        sem_post(&red_light_sem);  
    }
}

int main() {
    
    sem_init(&red_light_sem, 0, 1);
    sem_init(&yellow_light_sem, 0, 0);
    sem_init(&green_light_sem, 0, 0);

    pthread_t threads[NUM_THREADS];

    
    pthread_create(&threads[0], NULL, redLight, NULL);
    pthread_create(&threads[1], NULL, yellowLight, NULL);
    pthread_create(&threads[2], NULL, greenLight, NULL);

    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

   
    sem_destroy(&red_light_sem);
    sem_destroy(&yellow_light_sem);
    sem_destroy(&green_light_sem);

    return 0;
}

