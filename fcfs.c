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