#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MQ_KEY  0x1234
typedef struct msg 
{
    long id;             
    int data[2];           
} msg_t;

int main() 
{
  int mqid, pid, s, ret;
    
  mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
  if(mqid < 0)
   	{
     perror("msgget() failed");
     _exit(1);
    }

  pid = fork();
    if(pid == 0) 
	{  
      msg_t m1;
      m1.id = 101;  

      printf("Child: Enter two numbers separated by space: ");
      scanf("%d %d", &m1.data[0], &m1.data[1]);

      ret = msgsnd(mqid, &m1, sizeof(msg_t) - sizeof(long), 0);
      if(ret < 0)
	   {
        perror("Child: msgsnd() failed");
       } else
	   {
        printf("Child: Message sent with numbers: %d, %d\n", m1.data[0], m1.data[1]);
       }
        
       msg_t m2;
       ret = msgrcv(mqid, &m2, sizeof(msg_t) - sizeof(long), 102, 0);
       if(ret < 0)
	   	{
         perror("Child: msgrcv() failed");
        }
	   	else 
		{
         printf("Child: Received sum from parent: %d\n", m2.data[0]);
        }
        
        exit(0);
    }
    else
   	{  
     msg_t m1;
     printf("Parent: Waiting for message from child...\n");

     ret = msgrcv(mqid, &m1, sizeof(msg_t) - sizeof(long), 101, 0);
     if(ret < 0) 
  	{
      perror("Parent: msgrcv() failed");
    }
	else
	{
     printf("Parent: Received numbers from child: %d, %d\n", m1.data[0], m1.data[1]);
    
     int sum = m1.data[0] + m1.data[1];

        m1.id = 102;  
        m1.data[0] = sum;  

        ret = msgsnd(mqid, &m1, sizeof(msg_t) - sizeof(long), 0);
        if(ret < 0)
		 {
          perror("Parent: msgsnd() failed");
         }
	   	else  
		{
         printf("Parent: Sent sum to child: %d\n", sum);
        }
        }
        waitpid(pid, &s, 0);

        printf("Parent: Exiting\n");
    }

    return 0;
}

