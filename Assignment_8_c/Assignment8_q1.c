#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func(void *param) 
{
    int *arr = (int*)param;
    int n = 10;

    for (int i = 0; i < n - 1; i++) 
	{
        int min_index = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (arr[j] < arr[min_index]) 
			{
                min_index = j;
            }
        }
        if (min_index != i) 
		{
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }

    return NULL;
}

int main() 
{
    pthread_t th;
    int arr[10] = {32, 85, 73, 10, 2, 45, 81, 17, 69, 96}; 

    printf("Main: Array before sorting: ");
    for (int i = 0; i < 10; i++)
   	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_create(&th, NULL, thread_func, arr);

    pthread_join(th, NULL);

    printf("Main: Array after sorting: ");
    for (int i = 0; i < 10; i++) 
	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

