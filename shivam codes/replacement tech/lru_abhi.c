// lru
#include <stdio.h>

int main()
{
  int frames[10], pages[50], last_used[10];
  int num_frames, num_pages;
  int hit = 0, fault = 0;

  printf("Enter number of frames: ");
  scanf("%d", &num_frames);

  printf("Enter number of pages: ");
  scanf("%d", &num_pages);

  printf("Enter page reference string:\n");
  for (int i = 0; i < num_pages; i++)
  {
    scanf("%d", &pages[i]);
  }

  // initialize frames
  for (int i = 0; i < num_frames; i++)
  {
    frames[i] = -1;
    last_used[i] = -1;
  }

  printf("\nPage\tStatus\tFrames\n");
  printf("-------------------------------------------\n");

  for (int i = 0; i < num_pages; i++)
  {

    int page = pages[i];
    int found = 0;

    // check for HIT
    for (int j = 0; j < num_frames; j++)
    {
      if (frames[j] == page)
      {
        found = 1;
        hit++;
        last_used[j] = i; // update last used time
        break;
      }
    }

    // if NOT found → page fault
    if (!found)
    {
      fault++;

      int pos = -1;

      // check for empty frame
      for (int j = 0; j < num_frames; j++)
      {
        if (frames[j] == -1)
        {
          pos = j;
          break;
        }
      }

      // if no empty frame → replace least recently used
      if (pos == -1)
      {
        int lru = 0;
        for (int j = 1; j < num_frames; j++)
        {
          if (last_used[j] < last_used[lru])
          {
            lru = j;
          }
        }
        pos = lru;
      }

      frames[pos] = page;
      last_used[pos] = i;
    }

    // print info
    printf("%d\t%s\t", page, found ? "Hit  " : "Fault");

    for (int j = 0; j < num_frames; j++)
    {
      if (frames[j] == -1)
        printf("- ");
      else
        printf("%d ", frames[j]);
    }

    printf("\n");
  }

  printf("\nTotal Hits   = %d", hit);
  printf("  \nTotal Faults = %d", fault);
  printf("  \nHit Ratio    = %.2f", (float)hit / num_pages);
  printf("  \nFault Ratio  = %.2f\n", (float)fault / num_pages);

  return 0;
}
// ⭐ 2) last_used[] ← LRU ka main array

// 👉 Ye batata hai kis frame ko last time kab use kiya tha
// 👉 Jitna chhota number → utna purana use
// 👉 Purana use = Least Recently Used = isko replace karna