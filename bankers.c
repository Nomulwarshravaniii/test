#include<stdio.h>
#include<stdlib.h>
int max[10][10],allocation[10][10],need[10][10];
int avail[10];
int np,nr;
void readmatrix(int matrix[10][10])
{
    int i,j;
    for(i=0;i<np;i++)
    {
        for(j=0;j<nr;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
}
void display_matrix(int matrix[10][10])
{
    int i,j;
    for(i=0;i<np;i++)
    {
        for(j=0;j<nr;j++)
        {
            printf("%d  ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void calculate_need()
{
    int i,j;
    for(i=0;i<np;i++)
    {
        for(j=0;j<nr;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
    printf("\n");
}

void banker()
{
    int i, j, k = 0, flag;
    int finish[10], saf_seq[10];
    
    for (i = 0; i < np; i++)
    {
        finish[i] = 0;
    }
    
    int found;  // Flag to check if any process can proceed
    
    // Loop until we have a complete safe sequence
    while (k < np)
    {
        found = 0;  // Reset found flag for each pass

        for (i = 0; i < np; i++)
        {
            if (finish[i] == 0)  // Check unfinished processes
            {
                flag = 0;

                // Check if the process can proceed
                for (j = 0; j < nr; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)  // Process i can safely proceed
                {
                    finish[i] = 1;
                    saf_seq[k++] = i;  // Add to safe sequence
                    found = 1;         // Mark that we found a process

                    // Update available resources
                    for (j = 0; j < nr; j++)
                    {
                        avail[j] += allocation[i][j];
                    }
                 }
             }
        }

        // If no process could proceed, a deadlock has occurred
        if (found == 0)
        {
            printf("\nDeadlock occurred\n");
            return;
        }
    }

    // If safe sequence was found, print it
    printf("Printing safe sequence:\n");
    for (i = 0; i < np; i++)
    {
        printf("P%d  ", saf_seq[i]);
    }
    printf("\n");
}
/*void add_new_process()
{
    int i;
    np++; // Increase the process count for the new process

    printf("Enter allocated resources for the new process P%d:\n", np - 1);
    for(i = 0; i < nr; i++)
    {
        scanf("%d", &allocation[np - 1][i]);
    }
    
    printf("Enter maximum resources required for the new process P%d:\n", np - 1);
    for(i = 0; i < nr; i++)
    {
        scanf("%d", &max[np - 1][i]);
    }
    
    // Subtract the allocated resources of the new process from available resources
    for(i = 0; i < nr; i++)
    {
        avail[i] -= allocation[np - 1][i];
        
        // Check if available resources go negative
        if (avail[i] < 0) {
            printf("\nError: Adding process P%d causes insufficient resources.\n", np - 1);
            np--;  // Rollback the process count increment
            for (int j = 0; j <= i; j++) avail[j] += allocation[np][j]; // Restore avail values
            return;
        }
    }
    
    // Recalculate the need matrix for all processes including the new one
    calculate_need();
    
    // Display the updated available resources
    printf("Available resources after adding new process:\n");
    for(i = 0; i < nr; i++)
    {
        printf("%d  ", avail[i]);
    }
    printf("\n");
}
*/

int main()
{
    char add_more;
    int i;
    //take input from resource
    printf("\n enter no of processes ");
    scanf("%d",&np);
    printf("\n enter no of resources");
    scanf("%d",&nr);
    printf("\n enter allocation matrix :");
    readmatrix(allocation);
    
    printf("\n enter max requirement matrix :");
    readmatrix(max);
    
    printf("\n enter available resources :");
    for(i=0;i<nr;i++)
    {
        scanf("%d",&avail[i]);
    }
    
    //display the entered data
    printf("\n ****** Entered data is ******");
    printf("\n Inital allocation :\n");
    display_matrix(allocation);
    printf("\n\n\n Available Resources \n:");
    for(i=0;i<nr;i++)
    {
        printf("%d  ",avail[i]);
    }
    
    
    //caluclate need matrix
    calculate_need();
    printf("\n\n\n Need is :\n");
    display_matrix(need);
    
    //execute bankers
    banker();
    printf("\n\n\n\n");
    
    /*do
        {
            printf("Do you want to add a new process? (y/n): ");
            scanf(" %c", &add_more);

            if (add_more == 'y' || add_more == 'Y')
            {
                add_new_process();
                banker(); // Run Banker's algorithm again with the updated matrices
            }
        }
        while (add_more == 'y' || add_more == 'Y');*/
    
    return 0;
}
/*

  enter no of proceeses 5

  enter no of resourcses 3

 enter allocation matrix
 0 1 0
 2 0 0
 3 0 2
 2 1 1
 0 0 2

 enter max matrix
 7 5 3
 3 2 2
 9 0 2
 2 2 2
 4 3 3

  enter available resources3 3 2

 need matric :
 7 4 3
 1 2 2
 6 0 0
 0 1 1
 4 3 1


  safe sequenceP1 =>P3 =>P4 =>P0 =>P2 =>



 */
