#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
    int pipe_fd[2];
    int pipe_size;

    if (pipe(pipe_fd) == -1)
   	{
        perror("pipe failed");
        exit(1);
    }

    pipe_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1)
   	{
        perror("fcntl failed");
        exit(1);
    }

    printf("Size of the pipe buffer: %d bytes\n", pipe_size);

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}

