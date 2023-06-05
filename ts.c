#include <stdio.h>
#include <stdlib.h>

#define RED_LIGHT 0
#define YELLOW_LIGHT 1
#define GREEN_LIGHT 2

typedef struct {
    int light;
    int duration;
} Signal;

Signal trafficSignals[3];

void initializeTrafficSignals() {
    trafficSignals[RED_LIGHT].light = RED_LIGHT;
    trafficSignals[RED_LIGHT].duration = 10;
    
    trafficSignals[YELLOW_LIGHT].light = YELLOW_LIGHT;
    trafficSignals[YELLOW_LIGHT].duration = 3;
    
    trafficSignals[GREEN_LIGHT].light = GREEN_LIGHT;
    trafficSignals[GREEN_LIGHT].duration = 15;
}

void changeLight() {
    Signal currentSignal = trafficSignals[0];
    trafficSignals[0] = trafficSignals[1];
    trafficSignals[1] = trafficSignals[2];
    trafficSignals[2] = currentSignal;
}

void simulateTrafficSignal(int numCycles) {
    int i, j;
    for (i = 0; i < numCycles; i++) {
        for (j = 0; j < 3; j++) {
            Signal currentSignal = trafficSignals[j];
            
            switch (currentSignal.light) {
                case RED_LIGHT:
                    printf("RED LIGHT: Stop!\n");
                    break;
                case YELLOW_LIGHT:
                    printf("YELLOW LIGHT: Prepare to stop!\n");
                    break;
                case GREEN_LIGHT:
                    printf("GREEN LIGHT: Go!\n");
                    break;
            }
            
            int remainingTime = currentSignal.duration;
            while (remainingTime > 0) {
                printf("Time remaining: %d seconds\n", remainingTime);
                remainingTime--;
                sleep(1); // Delay execution by 1 second
            }
            
            printf("\n");
        }
        
        changeLight();
    }
}

int main() {
    initializeTrafficSignals();
    simulateTrafficSignal(5); // Simulate 5 cycles
    
    return 0;
}

