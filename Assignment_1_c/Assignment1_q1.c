#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int i, s;

    for (i = 0; i < 5; i++)
   	{
        pid = fork();  

        if (pid == 0) 
		{  
            for (int count = 1; count <= 5; count++)  
			{
                printf("Child %d (PID: %d) - Count: %d\n", i + 1, getpid(), count);
                sleep(1);  
            }
            _exit(0);  
        }
    }

    for (i = 0; i < 5; i++)
   	{
        wait(&s);  
    }
    printf("Parent: All child processes have completed.\n");

    return 0;
}

