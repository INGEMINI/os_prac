#include <stdio.h>

int main() {
    int framesCount, pagesCount;

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    printf("Enter number of pages: ");
    scanf("%d", &pagesCount);

    int pages[pagesCount];
    printf("Enter page reference string:\n");
    for (int i = 0; i < pagesCount; i++)
        scanf("%d", &pages[i]);

    int frames[framesCount];
    int recent[framesCount];   // LRU timestamp
    int time = 0;
    int pageFaults = 0;

    // Initialize
    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\nStep | Page | Status | Frames\n");
    printf("---------------------------------------\n");

    for (int i = 0; i < pagesCount; i++) {
        int current = pages[i];
        int found = 0;

        // Check if page HIT
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == current) {
                found = 1;
                recent[j] = time++;
                break;
            }
        }

        if (found) {
            printf("%4d | %4d |  HIT   | ", i + 1, current);
        } else {
            pageFaults++;

            int pos = -1;

            // Find empty frame
            for (int j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // No empty → replace LRU
            if (pos == -1) {
                int minRecent = recent[0];
                pos = 0;
                for (int j = 1; j < framesCount; j++) {
                    if (recent[j] < minRecent) {
                        minRecent = recent[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = current;
            recent[pos] = time++;

            printf("%4d | %4d | MISS   | ", i + 1, current);
        }

        // Print frames with '_' instead of -1
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == -1)
                printf(" _ ");
            else
                printf("%2d ", frames[j]);
        }
        printf("\n");
    }

    printf("---------------------------------------\n");
    printf("Total Page Faults = %d\n", pageFaults);

    return 0;
}
