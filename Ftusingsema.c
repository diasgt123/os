#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// Define the maximum number of teams
#define MAX_TEAMS 10

// Global variables
int numTeams;
char teamNames[MAX_TEAMS][50];
sem_t matchSem[MAX_TEAMS];

// Function to simulate a match
void* playMatch(void* arg) {
    int teamIndex = *((int*)arg);

    printf("Team %s is playing a match.\n", teamNames[teamIndex]);

    // Simulating the match
    // ...

    // Signal the completion of the match
    sem_post(&matchSem[teamIndex]);

    pthread_exit(NULL);
}

int main() {
    // Read the number of teams
    printf("Enter the number of teams: ");
    scanf("%d", &numTeams);

    if (numTeams < 2 || numTeams > MAX_TEAMS) {
        printf("Invalid number of teams.\n");
        return 1;
    }

    // Read the team names
    printf("Enter the names of the teams:\n");
    for (int i = 0; i < numTeams; i++) {
        printf("Team %d: ", i + 1);
        scanf("%s", teamNames[i]);

        // Initialize the semaphores
        sem_init(&matchSem[i], 0, 0);
    }

    // Create threads for matches
    pthread_t matchThreads[MAX_TEAMS];
    for (int i = 0; i < numTeams; i++) {
        int* teamIndex = malloc(sizeof(int));
        *teamIndex = i;

        pthread_create(&matchThreads[i], NULL, playMatch, teamIndex);
    }

    // Wait for all matches to complete
    for (int i = 0; i < numTeams; i++) {
        sem_wait(&matchSem[i]);
    }

    // Print the tournament fixture
    printf("\nTournament Fixture:\n");
    for (int i = 0; i < numTeams - 1; i++) {
        for (int j = i + 1; j < numTeams; j++) {
            printf("%s vs %s\n", teamNames[i], teamNames[j]);
        }
    }

    // Clean up
    for (int i = 0; i < numTeams; i++) {
        sem_destroy(&matchSem[i]);
    }

    return 0;
}

