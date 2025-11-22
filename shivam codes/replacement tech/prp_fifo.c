#include <stdio.h>

int main() {
    int frames[10], pages[30];
    int n, f, i, j, k, avail, page_faults = 0, page_hits = 0;
    
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page sequence: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    for(i = 0; i < f; i++)
        frames[i] = -1;   // Initialize frames to empty

    printf("\n");

    k = 0;

    for(i = 0; i < n; i++) {
        avail = 0;

        // Check if page already exists in frames
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                avail = 1;
                page_hits++;
                break;
            }
        }

        if(avail == 0) { // Page fault
            frames[k] = pages[i];
            k = (k + 1) % f;
            page_faults++;

            printf("Page: %d\tMISS\tFRAMES: ", pages[i]);
            for(j = 0; j < f; j++) {
                if(frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        } 
        else { // Page hit
            printf("Page: %d\tHIT\tFRAMES: ", pages[i]);
            for(j = 0; j < f; j++) {
                if(frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    float fault_ratio = (float)page_faults / n;

    printf("\nTotal Number of Page Faults: %d\n", page_faults);
    printf("Total Number of Page Hits: %d\n", page_hits);
    printf("Fault Ratio: %.2f\n", fault_ratio);

    return 0;
}