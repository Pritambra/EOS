#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;
pthread_cond_t c;
int sun_flag = 0;  

void* sunbeam(void *param)
{
    char *str = "SUNBEAM\n";
    while(1)
   	{
        pthread_mutex_lock(&m);
        while (sun_flag == 1)
	   	{
            // If it's not this thread's turn, wait
            pthread_cond_wait(&c, &m);
        }
        // Print SUNBEAM
        for(int i=0; str[i]!='\0'; i++) 
		{
            write(1, &str[i], 1);
//            sleep(1);
        }
        sun_flag = 1;  // Next turn should be for INFOTECH thread
        pthread_cond_signal(&c);  // Signal the infotech thread
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void* infotech(void *param) 
{
    char *str = "INFOTECH\n";
    while(1)
   	{
        pthread_mutex_lock(&m);
        while (sun_flag == 0) 
		{
            // If it's not this thread's turn, wait
            pthread_cond_wait(&c, &m);
        }
        // Print INFOTECH
        for(int i=0; str[i]!='\0'; i++) 
		{
            write(1, &str[i], 1);
  //          sleep(1);
        }
        sun_flag = 0;  // Next turn should be for SUNBEAM thread
        pthread_cond_signal(&c);  // Signal the sunbeam thread
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() 
{
    pthread_t st, it;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);

    // Create the threads
    pthread_create(&it, NULL, infotech, NULL);
    pthread_create(&st, NULL, sunbeam, NULL);

    // Wait for user input to exit
    printf("press enter to exit...\n");
    getchar();

    // Cleanup
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);

    return 0;
}

