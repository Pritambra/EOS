#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    int pid, sig;

    printf("Enter the Process ID: ");
    if (scanf("%d", &pid) != 1) 
	{
        perror("Invalid Process ID input");
        return 1;
    }

    printf("Enter the Signal Number: ");
    if (scanf("%d", &sig) != 1)
   	{
        perror("Invalid signal input");
        return 1;
    }

    if (kill(pid, sig) == -1)
   	{
        perror("Failed to send signal");
        return 1;
    }

    printf("Signal %d successfully sent to process %d.\n", sig, pid);

    return 0;
}

