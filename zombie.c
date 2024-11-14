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
