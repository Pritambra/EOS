#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_ADDR   "127.0.0.1"
#define SERV_PORT   2809

int main() {
    int ret, serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    int num1, num2, sum;

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_fd < 0) 
	{
        perror("Socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
   	{
        perror("Binding failed");
        close(serv_fd);
        return -1;
    }

    listen(serv_fd, 5);

    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    if (cli_fd < 0)
   	{
        perror("Accept failed");
        close(serv_fd);
        return -1;
    }

    do 
	{
        read(cli_fd, &num1, sizeof(num1));
        read(cli_fd, &num2, sizeof(num2));

        sum = num1 + num2;

        write(cli_fd, &sum, sizeof(sum));
        printf("Server: Sent sum %d back to client\n", sum);

    } 
	while (1);

    close(cli_fd);

    shutdown(serv_fd, SHUT_RDWR);
    return 0;
}

