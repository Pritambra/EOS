#include <stdio.h>
#include <unistd.h>

int main() {
    int ret, cnt = 0;
    while(1) {
        ret = fork();
        if(ret == -1)
	   	{ 
            printf("fork() failed.\n");
            _exit(0);
        }
        else if(ret == 0) 
		{
            sleep(5);
            _exit(0);
        }
        else 
		{
            cnt++;
            printf("child count: %d\n", cnt);
        }
    }

    return 0;
}
