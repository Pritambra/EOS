#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_ADDR   "127.0.0.1"
#define SERV_PORT   2809

int main()
{
    int ret, cli_fd;
    struct sockaddr_in serv_addr;
    int num1, num2, sum;

    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_fd < 0) 
	{
        perror("Socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);

    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
   	{
        perror("Connection failed");
        close(cli_fd);
        return -1;
    }

    do 
	{
        printf("Enter two numbers to sum (or type -1 to exit): ");
        scanf("%d %d", &num1, &num2);

        if (num1 == -1 && num2 == -1) 
		{
            break;
        }

        write(cli_fd, &num1, sizeof(num1));
        write(cli_fd, &num2, sizeof(num2));

        read(cli_fd, &sum, sizeof(sum));

        printf("Server: The sum is %d\n", sum);

    }
   	while (1);

    close(cli_fd);
    return 0;
}

