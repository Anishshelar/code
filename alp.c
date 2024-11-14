// ALP PROGRAMM

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024  // Define main memory size

void loadALPToMemory(const char *filename, char memory[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File open failed");
        exit(1);
    }

    int address = 0;
    while (fscanf(file, "%s", &memory[address]) != EOF && address < MEMORY_SIZE) {
        address++;
    }

    fclose(file);
}

int main() {
    char memory[MEMORY_SIZE] = {0};
    loadALPToMemory("sample1.txt", memory);

    printf("ALP program loaded into memory:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] != 0) {
            printf("Memory[%d]: %c\n", i, memory[i]);
        }
    }
    return 0;
}

// INPUT FILE:- 
// MOV AX, 1
// ADD AX, BX
// SUB AX, 2
// MOV CX, AX
// JMP 100
// HLT