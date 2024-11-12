#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main()
{
 int fd_client, fd_server;
 int numbers[2];
 int sum;
 ssize_t ret;

 fd_client = open("/tmp/client_to_server_fifo", O_WRONLY);
 if (fd_client < 0)
 {
  perror("Client: open() failed for client_to_server_fifo");
  exit(1);
 }

 printf("Client: Enter two numbers separated by space: ");
 scanf("%d %d", &numbers[0], &numbers[1]);

 ret = write(fd_client, numbers, sizeof(numbers));
 if (ret < 0) 
 {
  perror("Client: write() failed");
  close(fd_client);
  exit(1);
 }
  printf("Client: Sent numbers: %d, %d\n", numbers[0], numbers[1]);

  close(fd_client);

  fd_server = open("/tmp/server_to_client_fifo", O_RDONLY);
  if (fd_server < 0) 
  {
   perror("Client: open() failed for server_to_client_fifo");
   exit(1);
  }

  ret = read(fd_server, &sum, sizeof(sum));
  if (ret < 0)  
  {
  perror("Client: read() failed");
  close(fd_server);
  exit(1);
  }

  printf("Client: Received sum from server: %d\n", sum);

  close(fd_server);

  return 0;
}

