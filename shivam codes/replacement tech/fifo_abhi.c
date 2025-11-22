// fifo page replacement
#include <stdio.h>

int main()
{
  int frames[10], pages[50];
  int num_frames, num_pages;
  int i, j, k = 0, faults = 0, hits = 0;

  printf("Enter number of frames: ");
  scanf("%d", &num_frames);

  printf("Enter number of pages: ");
  scanf("%d", &num_pages);

  printf("Enter page reference string:\n");
  for (i = 0; i < num_pages; i++)
  {
    scanf("%d", &pages[i]);
  }

  // initialize frames as empty
  for (i = 0; i < num_frames; i++)
  {
    frames[i] = -1;
  }

  printf("\nPage\tStatus\tFrames\n");
  printf("----------------------------------\n");

  for (i = 0; i < num_pages; i++)
  {
    int page = pages[i];
    int found = 0;

    // check for hit
    for (j = 0; j < num_frames; j++)
    {
      if (frames[j] == page)
      {
        found = 1;
        hits++;
        break;
      }
    }

    if (!found)
    {
      frames[k] = page;
      k = (k + 1) % num_frames;
      faults++;
    }

    // print output
    printf("%d\t%s\t", page, found ? "Hit" : "Fault");

    for (j = 0; j < num_frames; j++)
    {
      if (frames[j] == -1)
        printf("- ");
      else
        printf("%d ", frames[j]);
    }

    printf("\n");
  }

  printf("\nTotal Hits   = %d", hits);
  printf("\nTotal Faults = %d", faults);
  printf("\nHit Ratio    = %.2f", (float)hits / num_pages);
  printf("\nFault Ratio  = %.2f\n", (float)faults / num_pages);

  return 0;
}
// A hit happens when the page already exists in one of the frames.
// A fault happens when the page is NOT present in any frame,

// hit ratio is no of hits / total page ref