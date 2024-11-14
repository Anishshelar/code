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