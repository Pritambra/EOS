#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() 
{
    int arr[2];       
    pid_t pid1, pid2;  
    int err1, err2;
    int s1, s2;

    if (pipe(arr) == -1)
   	{
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == 0) 
	{
        close(arr[0]);  

        dup2(arr[1], 1);  
        close(arr[1]);    

        err1 = execlp("who", "who", NULL);
        if (err1 == -1) 
		{
            perror("execlp failed for who");
            exit(1);
        }
    }

    pid2 = fork();
    if (pid2 == 0) 
	{
        close(arr[1]);  

        dup2(arr[0], 0);  
        close(arr[0]);    

        err2 = execlp("wc", "wc", NULL);
        if (err2 == -1) 
		{
            perror("execlp failed for wc");
            exit(1);
        }
    }

    close(arr[0]);
    close(arr[1]);

    waitpid(pid1, &s1, 0);
    waitpid(pid2, &s2, 0);

    return 0;
}

