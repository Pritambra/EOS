#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMD_SIZE 256

int run_command(const char *cmd)
{
    pid_t pid = fork();
    if (pid == -1) {
     
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0)
   	{
        printf("Running command: %s\n", cmd);
        execlp("/bin/sh", "sh", "-c", cmd, (char *)NULL);
       
        perror("execlp failed");
        exit(1);
    }
   	else
   	{
         int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	   	{
            printf("Command '%s' completed successfully.\n", cmd);
            return 0;  
        } else 
		{
            printf("Command '%s' failed.\n", cmd);
            return 1;  
        }
    }
}

int main()
{
   
    if (run_command("gcc -c circle.c") != 0) return 1;
    if (run_command("gcc -c square.c") != 0) return 1;
    if (run_command("gcc -c rectangle.c") != 0) return 1;
    if (run_command("gcc -c main.c") != 0) return 1;

    if (run_command("gcc -o program.out circle.o square.o rectangle.o main.o") != 0) return 1;

    if (run_command("./program.out") != 0) return 1;

    printf("Program executed successfully.\n");
    return 0;
}
