17 sum of even…
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
        // Parent process calculates sum of even numbers
        wait(NULL);  // Wait for the child process to finish
        calculate_even_sum(arr, n);
    } else if (pid == 0) {
        // Child process calculates sum of odd numbers
        calculate_odd_sum(arr, n);
        exit(0);
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}

// input
// {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

// output 
// Sum of odd numbers (Child): 25
// Sum of even numbers (Parent): 30
