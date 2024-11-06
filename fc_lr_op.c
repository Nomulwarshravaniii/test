#include <stdio.h>
#include <stdbool.h>

// Declare global variables for frame size and the frame array
int frame_size = 0, page,ref_len;
int frame[100],age[10],reference_string[100];

// Function to initialize frame with empty values (-1)
void LRUinput() {
    printf("Enter Frame size: ");
    scanf("%d", &frame_size);
    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1; // Initialize each frame slot to -1 (empty)
        age[i] = 0;    // Initialize each age to 0
    }
}
void FCFSinput() {
    printf("Enter Frame size: ");
    scanf("%d", &frame_size);
    for (int j = 0; j < frame_size; j++) {
        frame[j] = -1; // Initialize each frame slot to -1 (indicating empty)
    }
}
void display()
{
    for(int i=0;i<frame_size;i++)
    {
        if(frame[i]==-1)
        {
            printf("- ");
        }
        else
        {
            printf("%d ",frame[i]);
        }
    }
    printf("\n");
    
}
void Optimalinput()
{
    printf("\n enter frame size ");
    scanf("%d",&frame_size);
    
    for(int i=0;i<frame_size;i++)
    {
        frame[i]=-1;
    }
    printf("enter length of reference string ");
    scanf("%d",&ref_len);
    printf("enter reference string ");
    for(int i=0;i<ref_len;i++)
    {
        scanf("%d",&reference_string[i]);
    }
    
}
int findOptimal(int current_index)
{
    int farthest = current_index, replace_index = -1;
    
    for (int i = 0; i < frame_size; i++)
    {
        int j;
        for (j = current_index + 1; j < ref_len; j++)
        {
            if (frame[i] == reference_string[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    replace_index = i;
                }
                break;
            }
        }
        
        if (j == ref_len)
            return i; // Page not found in future references
    }
    
    return (replace_index == -1) ? 0 : replace_index;
}
void optimal()
{
    Optimalinput();
    int page_fault=0,page_hit=0;
    bool hit;
    int i,j;
    for(i=0;i<ref_len;i++)
    {
        hit=false;
        page=reference_string[i];
        
        for(j=0;j<frame_size;j++)
        {
            if(frame[j]==page)
            {
                printf("\n page hit occured ");
                page_hit++;
                hit=true;
                break;
            }
        }
        if(!hit)
        {
            if(i<frame_size)
            {
                frame[i]=page;
            }
            else
            {
                int replaceindex=findOptimal(i);
                frame[replaceindex]=page;
            }
            printf("\n page fault occured ");
            page_fault++;
        }
        display();
    }
    printf("\n page fault = %d",page_fault);
    printf("\n page hit = %d",page_hit);
    
}


// Function to perform FCFS page replacement
void FCFS() {
    FCFSinput(); // Initialize frames
    int cur_index = 0; // Track the current position to replace in frames
    int page_hit = 0, page_fault = 0; // Count hits and faults
    
    while (1) {
        bool hit = false; // Track if a page hit occurs

        printf("\nEnter Page number (or -1 to stop): ");
        scanf("%d", &page);
        
        if (page == -1) {
            break; // Stop if the user enters -1
        }

        // Check if the page is already in frames (Page Hit)
        for (int i = 0; i < frame_size; i++) {
            if (frame[i] == page) {
                page_hit++; // Increment page hit counter
                hit = true; // Set hit to true
                printf("Page Hit occurred.\n");
                break; // Stop checking if we found the page in frames
            }
        }

        // If page was not found in frames (Page Fault)
        if (!hit) {
            frame[cur_index] = page; // Replace page at current index
            page_fault++; // Increment page fault counter
            printf("Page Fault occurred.\n");
            cur_index = (cur_index + 1) % frame_size; // Move to next frame position
        }

        display(); // Show current state of frames
    }

    // Display total page hits and faults after loop ends
    printf("Total page hits: %d \nTotal page faults: %d\n", page_hit, page_fault);
}
void LRU() {
    LRUinput(); // Initialize frames and age
    int page_hit = 0, page_fault = 0;
    int pages_in_frame = 0; // Keep track of how many pages are currently in the frame

    while (1) {
        bool hit = false;

        printf("\nEnter Page number (or -1 to stop): ");
        scanf("%d", &page);

        if (page == -1) {
            break; // Stop if the user enters -1
        }

        // Check if the page is already in frames (Page Hit)
        for (int i = 0; i < frame_size; i++) {
            if (frame[i] == page) {
                page_hit++; // Increment page hit counter
                hit = true;
                age[i] = 0; // Reset age for this page as it was recently used
                printf("Page Hit occurred.\n");
                break;
            }
        }

        // If page not in frame (Page Fault)
        if (!hit)
        {
            if (pages_in_frame < frame_size)
            {
                // If frames are not fully occupied, fill the next available slot
                frame[pages_in_frame] = page;
                age[pages_in_frame] = 0; // Set age for the new page
                pages_in_frame++;
            }
            else
            {
                // If frames are full, replace the least recently used page
                int oldest = 0;
                for (int i = 1; i < frame_size; i++) {
                    if (age[i] > age[oldest]) {
                        oldest = i;
                    }
                }
                frame[oldest] = page;
                age[oldest] = 0; // Reset age for the new page
            }
            page_fault++; // Increment page fault counter
            printf("Page Fault occurred.\n");
        }

        // Increment the age for all pages except the recently accessed one
        for (int i = 0; i < frame_size; i++) {
            if (frame[i] != -1 && frame[i] != page) {
                age[i]++;
            }
        }

        display(); // Show the current frame state
    }

    // Display total page hits and faults after the loop ends
    printf("Total page hits: %d \nTotal page faults: %d\n", page_hit, page_fault);
}

int main() {
    int choice;
    printf("\nEnter choice : - 1.FCFS 2.LRU 3.Optimal");
    scanf("%d",&choice);
    if(choice==1)
    {
        FCFS();
    }
    else if(choice == 2)
    {
        LRU();
    }
    else
    {
        optimal();
    }
    return 0;
}
