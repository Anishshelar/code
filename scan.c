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