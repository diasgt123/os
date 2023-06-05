#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024

typedef struct {
    int start;
    int size;
} MemoryBlock;

MemoryBlock memory[MEMORY_SIZE];

void initializeMemory() {
    memory[0].start = 0;
    memory[0].size = MEMORY_SIZE;
}

void printMemoryMap() {
    printf("Memory Map:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].size > 0) {
            printf("%d - %d\tSize: %d\n", memory[i].start, memory[i].start + memory[i].size - 1, memory[i].size);
        }
    }
    printf("\n");
}

void allocateMemory(int size) {
    int allocated = 0;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].size >= size) {
            memory[i].size -= size;
            memory[i + memory[i].size].start = memory[i].start + memory[i].size;
            memory[i + memory[i].size].size = size;
            allocated = 1;
            break;
        }
    }

    if (allocated) {
        printf("Memory allocated successfully.\n");
    } else {
        printf("Memory allocation failed.\n");
    }
}

void deallocateMemory(int start) {
    int found = 0;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].start == start) {
            memory[i - memory[i].size].size += memory[i].size;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Memory deallocated successfully.\n");
    } else {
        printf("Memory deallocation failed. Block not found.\n");
    }
}

int main() {
    initializeMemory();

    printMemoryMap();

    allocateMemory(128);
    printMemoryMap();

    allocateMemory(256);
    printMemoryMap();

    allocateMemory(512);
    printMemoryMap();

    deallocateMemory(128);
    printMemoryMap();

    deallocateMemory(0);
    printMemoryMap();

    return 0;
}

