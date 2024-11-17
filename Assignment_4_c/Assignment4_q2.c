#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int ret, arr1[2], arr2[2], s;
    int num1 = 5, num2 = 7, sum;
    int result;

    ret = pipe(arr1);
    if (ret < 0) 
	{
        perror("pipe() failed");
        _exit(1);
    }

    ret = pipe(arr2);
    if (ret < 0) {
        perror("pipe() failed");
        _exit(1);
    }

    ret = fork();
    if (ret == 0) 
	{ 
        close(arr1[0]); 
        close(arr2[1]); 
        
        write(arr1[1], &num1, sizeof(num1));
        write(arr1[1], &num2, sizeof(num2));
        printf("child: sent numbers %d and %d to parent\n", num1, num2);
        close(arr1[1]); 

        read(arr2[0], &result, sizeof(result));
        printf("child: received result from parent: %d\n", result);
        close(arr2[0]);
    }
    else 
	{
        close(arr1[1]);
        close(arr2[0]); 

        read(arr1[0], &num1, sizeof(num1));
        read(arr1[0], &num2, sizeof(num2));
        printf("parent: received numbers %d and %d from child\n", num1, num2);
        close(arr1[0]); 

        sum = num1 + num2;

        write(arr2[1], &sum, sizeof(sum));
        printf("parent: sent sum %d back to child\n", sum);
        close(arr2[1]); 

        waitpid(ret, &s, 0); 
    }

    return 0;
}

