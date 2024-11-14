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
