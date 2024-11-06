/*#include<stdio.h>
#include<stdlib.h>

int choice;
int finish[10], process_name[10], arrival_time[10], burst_time[10], waiting_time[10], TAT[10];
int avg_wt, avg_Tat;
int n, pending, remaining_burst_time[10], curr_time, count;

void input() {
    int i;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        process_name[i] = i;
        printf("\nEnter burst time of process %d: ", process_name[i]);
        scanf("%d", &burst_time[i]);
        remaining_burst_time[i] = burst_time[i];
        printf("Enter arrival time of process %d: ", process_name[i]);
        scanf("%d", &arrival_time[i]);
    }
}
void sort() {
    int i, j, temp;
    for(i = 0; i < n ; i++) {
        for(j = i + 1; j < n; j++) {
            if ((arrival_time[i] <= curr_time && finish[i] == 0) &&
                ((remaining_burst_time[i] > remaining_burst_time[j] && arrival_time[j] <= curr_time && finish[j] == 0) ||
                finish[i] == 1 || arrival_time[i] > curr_time)) {
                
                // Swap all attributes
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = remaining_burst_time[i];
                remaining_burst_time[i] = remaining_burst_time[j];
                remaining_burst_time[j] = temp;

                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = waiting_time[i];
                waiting_time[i] = waiting_time[j];
                waiting_time[j] = temp;

                temp = process_name[i];
                process_name[i] = process_name[j];
                process_name[j] = temp;
            }
        }
    }
}

void SJF_preemptive() {
    int i;
    input();
    pending = n;

    printf("\n\nGantt Chart:\n");
    for(i = 0; i < n; i++) {
        finish[i] = 0;
        waiting_time[i] = 0;
    }

    curr_time = 0;
    count = 0;

    // Start execution
    while (pending > 0)
    {
        sort();
        for (count = 0; count < n; count++) 
        {
            if (finish[count] != 1 && arrival_time[count] <= curr_time)
            {
                // Print Gantt chart
                printf("P%d || ", process_name[count]);
                curr_time += 1;
                remaining_burst_time[count] -= 1;

                // Update waiting time for other processes
                for (i = 0; i < n; i++) 
                {
                    if (i != count && finish[i] != 1 && arrival_time[i] <= curr_time) 
                    {
                        waiting_time[i] += 1;
                    }
                }

                // If process is finished
                if (remaining_burst_time[count] == 0) 
                {
                    finish[count] = 1;
                    pending--;
                    TAT[count] = curr_time - arrival_time[count];
                    waiting_time[count] = TAT[count] - burst_time[count];
                }
                break;
            }
        }
    }

    // Calculate and display averages
    for (i = 0; i < n; i++) {
        avg_wt += waiting_time[i];
        avg_Tat += TAT[i];
    }
//    avg_wt /= n;
//    avg_Tat /= n;

    printf("\n\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", process_name[i], burst_time[i], arrival_time[i], waiting_time[i], TAT[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (avg_wt*1.0)/n);
    printf("\nAverage Turnaround Time: %.2f\n", (avg_Tat*1.0)/n);
}

int main() {
    
    SJF_preemptive();
    return 0;
}*/

/*Enter the number of processes: 5
 
 Enter burst time of process 0: 6
 Enter arrival time of process 0: 2

 Enter burst time of process 1: 2
 Enter arrival time of process 1: 5

 Enter burst time of process 2: 8
 Enter arrival time of process 2: 1

 Enter burst time of process 3: 3
 Enter arrival time of process 3: 0

 Enter burst time of process 4: 4
 Enter arrival time of process 4: 4


 Gantt Chart:
 P3 || P3 || P3 || P0 || P4 || P1 || P1 || P4 || P4 || P4 || P0 || P0 || P0 || P0 || P0 || P2 || P2 || P2 || P2 || P2 || P2 || P2 || P2 ||

 Process    Burst Time    Arrival Time    Waiting Time    Turnaround Time
 P3    3        0        0        3
 P1    2        5        0        2
 P4    4        4        2        6
 P0    6        2        7        13
 P2    8        1        14        22

 Average Waiting Time: 4.60
 Average Turnaround Time: 9.20*/


//ROUND ROBIN
#include <stdio.h>
int arrival_time[10], burst_time[10], waiting_time[10], TAT[10], completion_time[10];
int remaining_burst_time[10], finish[10], process_name[10];
int n, curr_time = 0;
void input() {
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        process_name[i] = i + 1;
        printf("\nEnter arrival time of process %d: ", process_name[i]);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time of process %d: ", process_name[i]);
        scanf("%d", &burst_time[i]);
        remaining_burst_time[i] = burst_time[i];
        finish[i] = 0;
        waiting_time[i] = 0;
        TAT[i] = 0;
        completion_time[i] = 0;
    }
}
int allProcessesComplete() {
    for (int i = 0; i < n; i++)    if (!finish[i]) return 0;
    return 1;
}
void round_robin() {
    int time_quantum, queue[100], front = 0, rear = -1;
    input();
    printf("\nEnter time quantum: ");
    scanf("%d", &time_quantum);
    printf("\nGantt Chart:\n");
    // Add first process that arrives at 0 to queue
    for (int i = 0; i < n; i++) {
        if (arrival_time[i] == 0) {
            rear = (rear + 1) % 100;
            queue[rear] = i;
        }
    }
    while (front <= rear) {
        int i = queue[front];
        front = (front + 1) % 100;
        if (remaining_burst_time[i] > 0) {
            printf("P%d || ", process_name[i]);
            if (remaining_burst_time[i] <= time_quantum) {
                curr_time += remaining_burst_time[i];
                completion_time[i] = curr_time;
                remaining_burst_time[i] = 0;
                finish[i] = 1;
                TAT[i] = completion_time[i] - arrival_time[i];
                waiting_time[i] = TAT[i] - burst_time[i];
            } else {
                curr_time += time_quantum;
                remaining_burst_time[i] -= time_quantum;
            }
            // Add newly arrived processes to queue
            for (int j = 0; j < n; j++) {
                if (!finish[j] && arrival_time[j] <= curr_time && j != i) {
                    // Check if process is not already in queue
                    int in_queue = 0;
                    for (int k = front; k <= rear; k++) {
                        if (queue[k] == j) {
                            in_queue = 1;
                            break;
                        }
                    }
                    if (!in_queue) {
                        rear = (rear + 1) % 100;
                        queue[rear] = j;
                    }
                }
            }
            // If process still has remaining time, add it back to queue
            if (remaining_burst_time[i] > 0) {
                rear = (rear + 1) % 100;
                queue[rear] = i;
            }
        }
        if (front > rear && !allProcessesComplete()) {
                   int next_arrival_time = 999999;
                   int next_process = -1;
                   for (int j = 0; j < n; j++) {
                       if (!finish[j] && arrival_time[j] > curr_time && arrival_time[j] < next_arrival_time) {
                           next_arrival_time = arrival_time[j];
                           next_process = j;
                       }
                   }
                   if (next_process != -1) {
                       curr_time = next_arrival_time;
                       rear = (rear + 1) % 100;
                       queue[rear] = next_process;
                   }
               }
           }
           printf("\n\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
           float total_waiting_time = 0, total_turnaround_time = 0;
           for (int i = 0; i < n; i++) {
               total_waiting_time += waiting_time[i];
               total_turnaround_time += TAT[i];
               printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",  process_name[i], burst_time[i], arrival_time[i], waiting_time[i], TAT[i], completion_time[i]);
           }
           printf("\nAverage Waiting Time = %.2f", total_waiting_time / n);
           printf("\nAverage Turnaround Time = %.2f\n", total_turnaround_time / n);
       } // write main function below
int main()
{
    round_robin();
}
/*
 
 Enter the number of processes: 4

 Enter arrival time of process 1: 0
 Enter burst time of process 1: 5

 Enter arrival time of process 2: 1
 Enter burst time of process 2: 4

 Enter arrival time of process 3: 2
 Enter burst time of process 3: 2

 Enter arrival time of process 4: 4
 Enter burst time of process 4: 1

 Enter time quantum: 2

 Gantt Chart:
 P1 || P2 || P3 || P1 || P4 || P2 || P1 ||

 Process    Burst Time    Arrival Time    Waiting Time    Turnaround Time    Completion Time
 P1    5        0        7        12        12
 P2    4        1        6        10        11
 P3    2        2        2        4        6
 P4    1        4        4        5        9

 Average Waiting Time = 4.75
 Average Turnaround Time = 7.75
 */
