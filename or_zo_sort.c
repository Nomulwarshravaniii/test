//orphan
/*
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <unistd.h>

 int main()
 {
     int pid;
     pid = getpid();
     
     printf("Current Process ID is : %d\n\n", pid);

     printf("[ Forking Child Process ... ] \n\n");
     pid = fork();  // This will create a child process and return the child's PID

     if (pid > 0) // Parent process
     {
         sleep(2);
         printf("\nParent process terminated.\n");
         exit(0);  // Exit the parent process
     }
     else if (pid == 0) // Child process
     {
         printf("\nChild before sleep.");
         printf("\nChild process ID: %d", getpid());
         printf("\nParent process ID: %d", getppid());

         sleep(5);

         printf("\nChild after sleep.");
         printf("\nChild process ID: %d", getpid());
         printf("\nParent process ID: %d", getppid());
         
         exit(0);  // Exit the child process
     }
     else
     {
         // If fork() fails, it returns -1
         perror("Fork failed");
         exit(1);  // Exit with an error code
     }

     return 0;
 }

*/
//zombie
/*
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <unistd.h>

 int main()
 {
     int pid;
     pid = getpid();
     
     printf("Current Process ID is : %d\n\n", pid);

     printf("[ Forking Child Process ... ] \n\n");
     pid = fork();  // This will create a child process and return the child's PID

     if (pid > 0) // Parent process
     {
         printf("\nParent process (PID %d) sleeping for 10 seconds...\n", getpid());

         sleep(10); // Let the parent sleep while the child process terminates
         printf("\nParent process woke up.\n");
         
         // Note: Not calling wait() here, so the child remains a zombie
         printf("Parent process terminated.\n");
         exit(0);  // Exit the parent process
     }
     else if (pid == 0) // Child process
     {
         printf("Child process (PID %d) terminating.\n", getpid());
         exit(0);  // Child exits immediately, becomes a zombie as parent is not reaping it
     }
     else
     {
         // If fork() fails, it returns -1
         perror("Fork failed");
         exit(1);  // Exit with an error code
     }

     return 0;
 }
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to perform selection sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        // Swap elements
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Function to print array
void printArray(int arr[], int n, const char* message) {
    printf("%s: ", message);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    
    // Get array size from user
    printf("Enter the number of integers: ");
    scanf("%d", &n);
    
    // Dynamically allocate array
    int *arr = (int*)malloc(n * sizeof(int));
    
    // Get array elements from user
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Create a copy of array for child process
    int *arr_copy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }
    
    printf("\nOriginal array: ");
    printArray(arr, n, "Original array");
    
    // Create child process
    pid_t pid = fork();
    
    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("\nChild process (PID: %d) sorting using Selection Sort\n", getpid());
        selectionSort(arr_copy, n);
        printArray(arr_copy, n, "Sorted array (Child)");
        free(arr_copy);
        exit(0);
    }
    else {
        // Parent process
        printf("\nParent process (PID: %d) sorting using Bubble Sort\n", getpid());
        bubbleSort(arr, n);
        printArray(arr, n, "Sorted array (Parent)");
        
        // Wait for child to complete
        int status;
        wait(&status);
        printf("\nChild process completed with status: %d\n", status);
    }
    
    free(arr);
    return 0;
}