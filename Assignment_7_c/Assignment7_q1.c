#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct input
{
    int start;
    int end;
};

struct output
{
    int sum;
};

void* calculate_sum(void *param)
{
    struct input *ip = (struct input *)param;
    struct output *op = (struct output *)malloc(sizeof(struct output));
    op->sum = 0;
    
    for (int i = ip->start; i <= ip->end; i++)
   	{
        op->sum += i;
    }
    printf("Thread: sum from %d to %d is %d\n", ip->start, ip->end, op->sum);
    return op;
}

int main()
{
    pthread_t th;
    struct input in = { .start = 1, .end = 20 }; 
    struct output *out;
    pthread_create(&th, NULL, calculate_sum, &in);
    pthread_join(th, (void**)&out);
    printf("Main: sum from %d to %d is %d\n", in.start, in.end, out->sum);

    free(out);
    return 0;
}

