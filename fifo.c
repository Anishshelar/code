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
