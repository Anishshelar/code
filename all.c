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


// c-scan
#include <stdio.h>
#include <stdlib.h>


void calculateCSCAN(int requests[], int n, int initial_head, int disk_size, int direction) {
    int total_seek_time = 0;
    int current_head = initial_head;


    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }


    // Find the starting index where the head should start servicing requests
    int start_index = 0;
    while (start_index < n && requests[start_index] < initial_head) {
        start_index++;
    }


    printf("\nDisk Scheduling using C-SCAN Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");


    // Move in the selected direction
    if (direction == 1) {  // Moving right towards higher values
        // Service requests to the right of the initial head position
        for (int i = start_index; i < n; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", i - start_index + 1, requests[i], seek_time);
            current_head = requests[i];
        }


        // Move to the end of the disk, if not already there, and then jump to the start
        if (current_head < disk_size - 1) {
            int end_seek_time = abs(disk_size - 1 - current_head);
            total_seek_time += end_seek_time;
            printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, end_seek_time);
        }
        int reset_seek_time = disk_size - 1;  // Jump from end to start
        total_seek_time += reset_seek_time;
        printf("|      -       |     0     |     %3d        |\n", reset_seek_time);
        current_head = 0;


        // Continue servicing the remaining requests from the start
        for (int i = 0; i < start_index; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", i + n - start_index + 1, requests[i], seek_time);
            current_head = requests[i];
        }
    } else {  // Moving left towards lower values
        // Service requests to the left of the initial head position
        for (int i = start_index - 1; i >= 0; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", start_index - i, requests[i], seek_time);
            current_head = requests[i];
        }


        // Move to the start of the disk and then jump to the end
        if (current_head > 0) {
            int start_seek_time = abs(current_head - 0);
            total_seek_time += start_seek_time;
            printf("|      -       |     0     |     %3d        |\n", start_seek_time);
        }
        int reset_seek_time = disk_size - 1;  // Jump from start to end
        total_seek_time += reset_seek_time;
        printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, reset_seek_time);
        current_head = disk_size - 1;


        // Continue servicing the remaining requests from the end
        for (int i = n - 1; i >= start_index; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", n - i, requests[i], seek_time);
            current_head = requests[i];
        }
    }


    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time); // Display total seek time
}


int main() {
    int n, initial_head, disk_size, direction;


    // Accept number of requests and initial head position
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);


    int requests[n];
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);


    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);


    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);


    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }


    // Calculate and display the C-SCAN scheduling
    calculateCSCAN(requests, n, initial_head, disk_size, direction);


    return 0;
}

// input
// Enter the number of disk requests: 8
// Enter the disk size: 200
// Enter the initial head position: 50
// Enter the direction (1 for right, 0 for left): 1
// Enter the disk requests:
// Request 1: 98
// Request 2: 183
// Request 3: 37
// Request 4: 122
// Request 5: 14
// Request 6: 124
// Request 7: 65
// Request 8: 67


// deadlock banker
#include <stdio.h>
#include <stdbool.h>


#define MAX_PROCESSES 10
#define MAX_RESOURCES 10


int processes, resources;
int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];


void calculateNeed() {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}


bool isSafeState() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;


    // Initialize work as a copy of available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }


    while (count < processes) {
        bool found = false;


        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;


                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }


                if (canAllocate) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }


        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }


    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}


int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);


    printf("Enter the number of resources: ");
    scanf("%d", &resources);


    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }


    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }


    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }


    calculateNeed();
    isSafeState();


    return 0;
}

// input
// Enter the number of processes: 5
// Enter the number of resources: 3

// Enter the available resources:
// 3 3 2
   
// Enter the maximum resource matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3

// Enter the allocation matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2


// dinphilsem
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

// fcfs
//3  FCFS 
#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int n, int head) {
    int seek_time = 0;
    printf("Sequence of disk access:\n%d", head);

    for (int i = 0; i < n; i++) {
        printf(" -> %d", requests[i]);
        seek_time += abs(requests[i] - head);
        head = requests[i];
    }

    printf("\nTotal seek time: %d\n", seek_time);
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    FCFS(requests, n, head);

    return 0;
}

// input
// Enter the number of requests: 5
// Enter the request queue: 98 183 37 122 14
// Enter initial head position: 53

// fcfs disk
// fcfs disk
#include <stdio.h>
#include <stdlib.h>


void calculateFCFS(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;


    printf("\nDisk Scheduling using FCFS Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");
   
    for (int i = 0; i < n; i++) {
        int seek_time = abs(requests[i] - current_head);
        total_seek_time += seek_time;
        printf("|      %2d      |    %3d     |     %3d        |\n", i + 1, requests[i], seek_time);
        current_head = requests[i];
    }


    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time);
}


int main() {
    int n;
    int initial_head;


    // Accept number of requests and initial head position
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);


    int requests[n];
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);


    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }


    // Calculate and display the FCFS scheduling
    calculateFCFS(requests, n, initial_head);


    return 0;
}

// input
// Enter the number of disk requests: 5
// Enter the initial head position: 50
// Enter the disk requests:
// Request 1: 98
// Request 2: 183
// Request 3: 37
// Request 4: 122
// Request 5: 14


// fifo
//4 FIFO 
#include <stdio.h>

void FIFO(int pages[], int n, int capacity) {
    int frames[capacity];
    int count = 0, page_faults = 0;

    for (int i = 0; i < capacity; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[count % capacity] = page;
            count++;
            page_faults++;
        }

        printf("Frames: ");
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int n, capacity;
    printf("Enter the number of page requests: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);

    return 0;
}

// input
// Enter the number of page requests: 12
// Enter the pages: 1 3 0 3 5 6 3 1 2 1 3 2
// Enter the frame capacity: 3

// output
// Frames: 1 - - 
// Frames: 1 3 - 
// Frames: 1 3 0 
// Frames: 1 3 0 
// Frames: 5 3 0 
// Frames: 5 6 0 
// Frames: 5 6 3 
// Frames: 1 6 3 
// Frames: 1 2 3 
// Frames: 1 2 3 
// Frames: 1 3 3 
// Frames: 1 3 2 
// Total Page Faults: 9


// linebyline
//line by line :- 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream inFile("input.txt");

    if (!inFile)
    {
        cerr << " input file not present";
        return 1;
    }

    char ch;
    while (inFile.get(ch))
    {
        cout << ch << endl;
    }

    inFile.close();
    inFile.open("input.txt");

    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    cout << "successfully copied the content";
}

// lru
// lru
#include <stdio.h>

#define MAX_FRAMES 10

// Function to find the index of the Least Recently Used (LRU) page
int findLRU(int frames[], int time[], int frameCount) {
    int min = time[0], minIndex = 0;
    for (int i = 1; i < frameCount; i++) {
        if (time[i] < min) {
            min = time[i];
            minIndex = i;
        }
    }
    return minIndex; // Return the index of the LRU page
}

// Function to check if a page is already present in the frames
int isPageInFrames(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return 1; // Page found in frames
        }
    }
    return 0; // Page not found
}

// Function to display the current state of frames
void displayFrames(int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int frameCount, pageCount;
    int pageFaults = 0;

    // Input: Number of frames and number of pages in the reference string
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageCount);

    int pages[pageCount];
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    int frames[MAX_FRAMES];
    int time[MAX_FRAMES]; // Array to keep track of the last used time of each frame
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames as empty
        time[i] = -1; // Initialize last used time as -1 for unused frames
    }

    // Processing each page in the reference string
    printf("\nPage Replacement Process:\n");
    for (int i = 0; i < pageCount; i++) {
        int currentPage = pages[i];

        // Check if the current page is already in the frames
        if (!isPageInFrames(frames, frameCount, currentPage)) {
            // Page fault occurs as the page is not in frames
            int lruIndex = findLRU(frames, time, frameCount); // Find the index of the LRU page
            frames[lruIndex] = currentPage; // Replace the LRU page with the current page
            pageFaults++; // Increment page faults
            printf("Page %d caused a page fault. Frames: ", currentPage);
        } else {
            printf("Page %d did not cause a page fault. Frames: ", currentPage);
        }

        // Update the last used time for each page in the frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == currentPage) {
                time[j] = i; // Set the current time index as the last used time
                break;
            }
        }

        // Display current state of frames after each request
        displayFrames(frames, frameCount);
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

// input
// Enter the number of frames: 3
// Enter the number of pages in the reference string: 12
// Enter the reference string (space-separated): 7 0 1 2 0 3 0 4 2 3 0 3

// matrix
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX 3  // Size of the matrix (MAX x MAX)
#define NUM_THREADS MAX * MAX  // Number of threads


int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX]; // Matrices for operations
int D[MAX][MAX]; // Result matrix for addition
int E[MAX][MAX]; // Result matrix for multiplication


// Structure to pass data to threads
typedef struct {
    int row;
    int col;
} ThreadData;


// Function for matrix addition
void *matrix_addition(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row;
    int col = data->col;


    D[row][col] = A[row][col] + B[row][col];


    pthread_exit(0);
}


// Function for matrix multiplication
void *matrix_multiplication(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row;
    int col = data->col;


    E[row][col] = 0;
    for (int k = 0; k < MAX; k++) {
        E[row][col] += A[row][k] * B[k][col];
    }


    pthread_exit(0);
}


int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];


    // Initialize matrices A and B
    printf("Matrix A:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }


    printf("Matrix B:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }


    // Create threads for matrix addition
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[i * MAX + j].row = i;
            thread_data[i * MAX + j].col = j;
            pthread_create(&threads[i * MAX + j], NULL, matrix_addition, (void *)&thread_data[i * MAX + j]);
        }
    }


    // Join threads for matrix addition
    for (int i = 0; i < MAX * MAX; i++) {
        pthread_join(threads[i], NULL);
    }


    // Display result of matrix addition
    printf("Result of Matrix Addition (D = A + B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }


    // Create threads for matrix multiplication
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[i * MAX + j].row = i;
            thread_data[i * MAX + j].col = j;
            pthread_create(&threads[i * MAX + j], NULL, matrix_multiplication, (void *)&thread_data[i * MAX + j]);
        }
    }


    // Join threads for matrix multiplication
    for (int i = 0; i < MAX * MAX; i++) {
        pthread_join(threads[i], NULL);
    }


    // Display result of matrix multiplication
    printf("Result of Matrix Multiplication (E = A * B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", E[i][j]);
        }
        printf("\n");
    }


    return 0;
}

// input
// Matrix A:
// 3 7 1 
// 6 5 9 
// 2 4 8 

// Matrix B:
// 4 6 8 
// 1 0 5 
// 9 3 2 

// Result of Matrix Addition (D = A + B):
// 7 13 9 
// 7 5 14 
// 11 7 10 

// Result of Matrix Multiplication (E = A * B):
// 40 27 39 
// 102 57 73 
// 94 38 58 


// opcode error
//27 OPCODE ERROR IN GIVEN JOB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValidOperand(char *operand) {
    // Check if operand is a valid integer or register name
    if (isdigit(operand[0])) {  // Check if operand is a valid integer
        for (int i = 0; i < strlen(operand); i++) {
            if (!isdigit(operand[i])) return 0;
        }
        return 1;
    } else {  // Check if operand is a valid register (e.g., "R1", "AX")
        return (isalpha(operand[0]) && strlen(operand) <= 3);
    }
}

void checkOperandError(char *job[], int n) {
    int error_found = 0;
    printf("\nInstruction\tOperand Validity\n");
    for (int i = 0; i < n; i++) {
        if (!isValidOperand(job[i])) {
            printf("%s\t\tInvalid (Interrupt Raised)\n", job[i]);
            error_found = 1;
        } else {
            printf("%s\t\tValid\n", job[i]);
        }
    }
    if (error_found) printf("\nInterrupt: Invalid operand(s) detected!\n");
}

int main() {
    int n;
    printf("Enter number of instructions: ");
    scanf("%d", &n);
    getchar(); // Clear newline character from input buffer

    char *job[n];
    printf("Enter operands (one per instruction):\n");
    for (int i = 0; i < n; i++) {
        job[i] = (char*) malloc(10); // Cast malloc to (char*)
        if (job[i] == NULL) { // Check if malloc was successful
            printf("Memory allocation failed\n");
            return 1;
        }
        fgets(job[i], 10, stdin); // Use fgets to avoid buffer overflow
        job[i][strcspn(job[i], "\n")] = '\0'; // Remove newline character
    }

    checkOperandError(job, n);
    
    for (int i = 0; i < n; i++) free(job[i]); // Free allocated memory

    return 0;
}

// INPUT:- 
// 123
// AX
// 45B
// 500

// operand


#include <stdio.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


void check_operand_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    for (int i = 0; i < instruction_count; i++) {
        int operand_count = 0;
        char *token = strtok(main_memory[i], " ,");
        // Count tokens after the opcode as operands
        while (token != NULL) {
            operand_count++;
            token = strtok(NULL, " ,");
        }
       
        if (operand_count < 3) { // Opcode + 2 operands
            printf("Operand error at address %d: Missing operand(s) in instruction '%s'\n", i, main_memory[i]);
        }
    }
}


int main() {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",
        "STORE R2", // Missing operand for testing
        "ADD R1, R2",
        "SUB R3" // Missing operand for testing
    };
    int instruction_count = 4;
    check_operand_errors(main_memory, instruction_count);
    return 0;
}

// input:-
// LOAD R1, 100
// STORE R2      // Missing operand
// ADD R1, R2
// SUB R3        // Missing operand

// optimal
//6 Optimal page replacement
#include <stdio.h>

int predict(int pages[], int n, int page, int index) {
    int farthest = index, res = -1;
    for (int i = 0; i < n; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (pages[j] == page) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return res == -1 ? 0 : res;
}

void OptimalPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < capacity) {
                frames[i] = page;
            } else {
                int j = predict(pages, n, frames, i + 1);
                frames[j] = page;
            }
            page_faults++;
        }

        printf("Frames: ");
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int n, capacity;
    printf("Enter the number of page requests: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    OptimalPageReplacement(pages, n, capacity);

    return 0;
}

// input
// Enter the number of page requests: 12
// Enter the pages: 1 3 0 3 5 6 3 1 2 1 3 2
// Enter the frame capacity: 3

// output
// Frames: 1 - - 
// Frames: 1 3 - 
// Frames: 1 3 0 
// Frames: 1 3 0 
// Frames: 5 3 0 
// Frames: 5 6 0 
// Frames: 5 6 3 
// Frames: 1 6 3 
// Frames: 1 2 3 
// Frames: 1 2 3 
// Frames: 1 3 3 
// Frames: 1 3 2 
// Total Page Faults: 9

// pcmeu
//1 producer consumer meutex
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_producer, cond_consumer;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }

        buffer[count++] = i;
        printf("Produced: %d\n", i);

        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}


// pcsem
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


// priority
// priority

#include <stdio.h>
#include <stdbool.h>


struct Process {
    int pid;          // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime; // For preemptive scheduling
    int priority;
    int finishTime;
    int turnAroundTime;
    int waitingTime;
    bool isCompleted;
};


// Function for Non-Preemptive Priority Scheduling
void priorityNonPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;


    while (completed < n) {
        int minIndex = -1;
        int highestPriority = 1e9;


        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime &&
                processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                minIndex = i;
            }
        }


        if (minIndex == -1) {
            currentTime++;
        } else {
            // Calculate the finish time, turnaround time, and waiting time
            processes[minIndex].finishTime = currentTime + processes[minIndex].burstTime;
            processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
            processes[minIndex].isCompleted = true;


            currentTime = processes[minIndex].finishTime;
            completed++;
        }
    }
}


// Function for Preemptive Priority Scheduling
void priorityPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;


    while (completed < n) {
        int minIndex = -1;
        int highestPriority = 1e9;


        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted &&
                processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                minIndex = i;
            }
        }


        if (minIndex != -1) {
            // Process one unit of the burst time
            processes[minIndex].remainingTime--;
            currentTime++;


            // If process is completed
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].finishTime = currentTime;
                processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                processes[minIndex].isCompleted = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}


void displayResults(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tPriority\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].finishTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }


    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }


    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}


int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);


    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", processes[i].pid);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }


    printf("Choose Scheduling:\n1. Non-Preemptive Priority\n2. Preemptive Priority\n");
    scanf("%d", &choice);


    if (choice == 1) {
        priorityNonPreemptive(processes, n);
    } else if (choice == 2) {
        priorityPreemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }


    displayResults(processes, n);
    return 0;
}

// input:-

// 4
// 0 8 2
// 1 4 1
// 2 9 3
// 3 5 2
// 1

// round robin
//ROUND ROBBIN

#include <stdio.h>

struct Process {
    int pid; // Process ID
    int burstTime; // Burst Time
    int remainingTime; // Remaining Time
    int waitingTime; // Waiting Time
    int turnaroundTime; // Turnaround Time
    int finishTime; // Finish Time
};

int main() {
    int n, quantum, currentTime = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        processes[i].pid = i + 1;
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].finishTime = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                if (processes[i].remainingTime > quantum) {
                    currentTime += quantum;
                    processes[i].remainingTime -= quantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].finishTime = currentTime;
                    processes[i].turnaroundTime = processes[i].finishTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    completed++;
                }
            }
        }
    }

    printf("\nProcess\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].finishTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    return 0;
}

// INPUT:-
// 3
// 5
// 3
// 8
// 3

// rwmeu
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


//rwsem
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


//scan
//SCAN DISK SCHDULING

#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int seek_time = 0;
    int idx = 0, temp_head = head;
    requests[n] = head; 
    requests[n + 1] = direction == 1 ? disk_size - 1 : 0;
    n += 2;

    // Sort the requests array
    qsort(requests, n, sizeof(int), compare);

    while (requests[idx] != head) idx++;
    printf("\nRequest\tSeek Time\n");

    // Process requests in the specified direction
    if (direction == 1) {
        for (int i = idx; i < n; i++) {
            seek_time += abs(temp_head - requests[i]);
            printf("%d\t%d\n", requests[i], abs(temp_head - requests[i]));
            temp_head = requests[i];
        }
    } else {
        for (int i = idx - 1; i >= 0; i--) {
            seek_time += abs(temp_head - requests[i]);
            printf("%d\t%d\n", requests[i], abs(temp_head - requests[i]));
            temp_head = requests[i];
        }
    }

    printf("Total Seek Time: %d\n", seek_time);
}

int main() {
    int n, head, disk_size, direction;
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n + 2];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter direction (1 for high, -1 for low): ");
    scanf("%d", &direction);

    scan(requests, n, head, disk_size, direction);
    return 0;
}

// INPUT:- 
// 200
// 5
// 98 183 37 122 14
// 50
// 1

//shell.sh
Factorial Using Recursion:-
#!/bin/bash

# Factorial using Recursion
factorial() {
  if [ $1 -le 1 ]; then
    echo 1
  else
    prev=$(factorial $(( $1 - 1 )))
    echo $(( $1 * prev ))
  fi
}

echo "Factorial of 5: $(factorial 5)"

Palindrome Check for a String:-

#!/bin/bash

# Palindrome Check for a String
is_palindrome() {
  input=$1
  reversed=$(echo $input | rev)
  if [ "$input" == "$reversed" ]; then
    echo "$input is a palindrome"
  else
    echo "$input is not a palindrome"
  fi
}

is_palindrome "racecar"
is_palindrome "hello"

Bubble Sort:-
#!/bin/bash

# Bubble Sort
bubble_sort() {
  arr=("$@")
  n=${#arr[@]}
  
  for (( i=0; i<$n; i++ ))
  do
    for (( j=0; j<$n-i-1; j++ ))
    do
      if [ ${arr[$j]} -gt ${arr[$((j+1))]} ]; then
        temp=${arr[$j]}
        arr[$j]=${arr[$((j+1))]}
        arr[$((j+1))]=$temp
      fi
    done
  done

  echo "Sorted Array: ${arr[@]}"
}

bubble_sort 5 2 9 1 5 6


Count Occurrences of Substring
#!/bin/bash

# Count Occurrences of Substring
count_occurrences() {
  string=$1
  substring=$2
  count=$(grep -o "$substring" <<< "$string" | wc -l)
  echo "The substring '$substring' occurs $count times"
}

count_occurrences "hello world, hello again" "hello"


Sum of Digits:-
#!/bin/bash

# Sum of Digits
sum_digits() {
  number=$1
  sum=0
  while [ $number -gt 0 ]; do
    digit=$(( number % 10 ))
    sum=$(( sum + digit ))
    number=$(( number / 10 ))
  done
  echo "Sum of digits: $sum"
}

sum_digits 12345


Reverse Digits:-
#!/bin/bash

# Reverse Digits
reverse_digits() {
  number=$1
  reverse=0
  while [ $number -gt 0 ]; do
    digit=$(( number % 10 ))
    reverse=$(( reverse * 10 + digit ))
    number=$(( number / 10 ))
  done
  echo "Reversed number: $reverse"
}

reverse_digits 12345


Armstrong Number Check:-
#!/bin/bash

# Function to check if a number is an Armstrong number
is_armstrong() {
  num=$1
  sum=0
  temp=$num
  n=${#num}  # Number of digits

  # Calculate the sum of each digit raised to the power of the number of digits
  while [ $temp -gt 0 ]
  do
    digit=$((temp % 10))                 # Extract the last digit
    sum=$((sum + digit ** n))             # Add digit^n to sum
    temp=$((temp / 10))                   # Remove the last digit
  done

  # Check if the calculated sum matches the original number
  if [ $sum -eq $num ]; then
    echo "$num is an Armstrong number."
  else
    echo "$num is not an Armstrong number."
  fi
}

# Input number
read -p "Enter a number: " number
is_armstrong "$number"

// sjf
//shortest job first

#include <stdio.h>
#include <stdbool.h>


struct Process {
    int pid;          // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime; // For preemptive SJF
    int finishTime;
    int turnAroundTime;
    int waitingTime;
    bool isCompleted;
};


// Function for Non-Preemptive SJF
void sjfNonPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;


    while (completed < n) {
        int minIndex = -1;
        int minBurstTime = 1e9;


        // Select the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime &&
                processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                minIndex = i;
            }
        }


        if (minIndex == -1) {
            currentTime++;
        } else {
            // Calculate the finish time, turnaround time, and waiting time
            processes[minIndex].finishTime = currentTime + processes[minIndex].burstTime;
            processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
            processes[minIndex].isCompleted = true;


            currentTime = processes[minIndex].finishTime;
            completed++;
        }
    }
}


// Function for Preemptive SJF
void sjfPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;
    int minIndex = -1;
    int minRemainingTime = 1e9;


    while (completed < n) {
        minIndex = -1;
        minRemainingTime = 1e9;


        // Select the process with the smallest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted &&
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                minIndex = i;
            }
        }


        if (minIndex != -1) {
            processes[minIndex].remainingTime--;
            currentTime++;


            // If process is completed
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].finishTime = currentTime;
                processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                processes[minIndex].isCompleted = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}


void displayResults(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].finishTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }


    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }


    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}


int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);


    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }


    printf("Choose Scheduling:\n1. Non-Preemptive SJF\n2. Preemptive SJF\n");
    scanf("%d", &choice);


    if (choice == 1) {
        sjfNonPreemptive(processes, n);
    } else if (choice == 2) {
        sjfPreemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }


    displayResults(processes, n);
    return 0;
}

// input:-
// 4
// 0 7
// 2 4
// 4 1
// 5 4 
// 1

//SSTF DISK SCHEDULING

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include this for INT_MAX

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sstf(int requests[], int n, int head) {
    int seek_time = 0, index;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("\nRequest\tSeek Time\n");
    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX; // Replace INT_MAX with INT_MAX
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(head - requests[j]) < min_seek) {
                min_seek = abs(head - requests[j]);
                index = j;
            }
        }
        visited[index] = 1;
        seek_time += min_seek;
        printf("%d\t%d\n", requests[index], min_seek);
        head = requests[index];
    }
    printf("Total Seek Time: %d\n", seek_time);
}

int main() {
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);

    sstf(requests, n, head);
    return 0;
}

// INPUT:-
// 8
// 82 170 43 140 24 16 190 200
// 50

// syscalls


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
 
// Function prototypes
void process_related();
void file_related();
void communication_related();
void info_related();
 
void process_related() {
    int choice;
    pid_t pid;
 
    printf("\nProcess Related System Calls:\n");
    printf("1. fork()\n");
    printf("2. exit()\n");
    printf("3. wait()\n");
    printf("4. exec()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            pid = fork();
            if (pid == 0) {
                printf("Child process. PID = %d\n", getpid());
                exit(0);
            } else {
                printf("Parent process. PID = %d\n", getpid());
                wait(NULL);
            }
            break;
        case 2:
            printf("Exiting process with status 0...\n");
            exit(0);
            break;
        case 3:
            pid = fork();
            if (pid == 0) {
                printf("Child process created. PID = %d\n", getpid());
                exit(0);
            } else {
                wait(NULL);
                printf("Child process has terminated. Parent PID = %d\n", getpid());
            }
            break;
        case 4:
            pid = fork();
            if (pid == 0) {
                execl("/bin/ls", "ls", NULL);
                perror("execl failed");
                exit(0);
            } else {
                wait(NULL);
                printf("Executed ls command in child process.\n");
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
void file_related() {
    int choice;
    int fd;
    char buffer[100];
 
    printf("\nFile Related System Calls:\n");
    printf("1. open(), write(), close()\n");
    printf("2. link(), stat(), unlink()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
            if (fd == -1) {
                perror("Error opening file");
                exit(1);
            }
 
            write(fd, "Hello, World!\n", 14);
            close(fd);
            printf("File written and closed successfully.\n");
 
            fd = open("example.txt", O_RDONLY);
            read(fd, buffer, sizeof(buffer));
            printf("File content: %s", buffer);
            close(fd);
            break;
        case 2:
            link("example.txt", "example_link.txt");
            struct stat file_stat;
            stat("example_link.txt", &file_stat);
            printf("Size of linked file: %ld bytes\n", file_stat.st_size);
            unlink("example_link.txt");
            printf("Link removed.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
void communication_related() {
    int choice;
    int fd[2];
    char write_msg[] = "Hello, World!";
    char read_msg[20];
    pid_t pid;
 
    printf("\nCommunication Related System Calls:\n");
    printf("1. pipe()\n");
    printf("2. FIFO (named pipe)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            if (pipe(fd) == -1) {
                perror("Pipe failed");
                exit(1);
            }
 
            pid = fork();
            if (pid == 0) {
                close(fd[0]); // Close unused read end
                write(fd[1], write_msg, strlen(write_msg)+1);
                close(fd[1]);
                exit(0);
            } else {
                close(fd[1]); // Close unused write end
                read(fd[0], read_msg, sizeof(read_msg));
                printf("Received message: %s\n", read_msg);
                close(fd[0]);
                wait(NULL);
            }
            break;
        case 2:
            mkfifo("/tmp/myfifo", 0666);
            pid = fork();
 
            if (pid == 0) {
                int fd = open("/tmp/myfifo", O_WRONLY);
                write(fd, write_msg, strlen(write_msg)+1);
                close(fd);
                exit(0);
            } else {
                int fd = open("/tmp/myfifo", O_RDONLY);
                read(fd, read_msg, sizeof(read_msg));
                printf("Received message: %s\n", read_msg);
                close(fd);
                unlink("/tmp/myfifo");
                wait(NULL);
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
void info_related() {
    int choice;
 
    printf("\nInformation Related System Calls:\n");
    printf("1. alarm()\n");
    printf("2. sleep()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            printf("Setting an alarm for 5 seconds...\n");
            alarm(5);
            sleep(6); // Wait to see alarm trigger
            break;
        case 2:
            printf("Sleeping for 3 seconds...\n");
            sleep(3);
            printf("Woke up after 3 seconds.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
int main() {
    int choice;
 
    while(1) {
        // printf("\nMenu:\n");
        // printf("1. Process Related System Calls\n");
        // printf("2. File Related System Calls\n");
        // printf("3. Communication Related System Calls\n");
        // printf("4. Information Related System Calls\n");
        // printf("5. Exit\n");
        // printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch(choice) {
            case 1:
                process_related();
                break;
            case 2:
                file_related();
                break;
            case 3:
                communication_related();
                break;
            case 4:
                info_related();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
 
    return 0;
}

// input:-

// 1
// 1
// 1 3 1 4 1 2

// zombie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void calculate_even_sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    printf("Sum of even numbers (Parent): %d\n", sum);
}

void calculate_odd_sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            sum += arr[i];
        }
    }
    printf("Sum of odd numbers (Child): %d\n", sum);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process, PID: %d\n", getpid());

        // Parent calculates sum of even numbers
        wait(NULL);  // Wait for the child process to finish

        calculate_even_sum(arr, n);  // Parent calculates even sum after child finishes
    } else if (pid == 0) {
        // Child process
        printf("Child process, PID: %d\n", getpid());
        
        // Child calculates sum of odd numbers
        calculate_odd_sum(arr, n);

        exit(0);  // Child exits, making it a zombie process until the parent calls wait
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}
