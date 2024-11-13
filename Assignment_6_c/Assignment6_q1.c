#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>

#define SEM_KEY     0x4321

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

void sigchld_handler(int sig)
{
    int s;
    waitpid(-1, &s, 0);
}

int main()
{
    int ret, i, semid;
    struct sigaction sa;
    union semun su;
    struct sembuf ops[1];

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigchld_handler;
    ret = sigaction(SIGCHLD, &sa, NULL);

    semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
    if (semid == -1)
   	{
        perror("semget");
        return 1;
    }

    su.val = 1;
    ret = semctl(semid, 0, SETVAL, su);
    if (ret == -1)
   	{
        perror("semctl");
        return 1;
    }

    ret = fork();
    if (ret == 0)
   	{  
        char *str = "SUNBEAM\n";
        while (1) 
		{
            ops[0].sem_num = 0;
            ops[0].sem_op = -1; 
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if (ret == -1)
		   	{
                perror("semop - child");
                return 1;
            }
          // print sunbeam
            for (i = 0; str[i] != '\0'; i++)
		   	{
                write(1, &str[i], 1);
            }

            ops[0].sem_num = 0;
            ops[0].sem_op = +1; 
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if (ret == -1) 
			{
                perror("semop - child");
                return 1;
            }
        }
        _exit(0);
    }
    else
   	{  // print infotech
        char *str = "INFOTECH\n";
        while (1) 
		{
            ops[0].sem_num = 0;
            ops[0].sem_op = -1; 
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if (ret == -1) 
			{
                perror("semop - parent");
                return 1;
            }
            for (i = 0; str[i] != '\0'; i++) 
			{
                write(1, &str[i], 1);
            }

            ops[0].sem_num = 0;
            ops[0].sem_op = +1; 
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if (ret == -1) 
			{
                perror("semop - parent");
                return 1;
            }
        }
        semctl(semid, 0, IPC_RMID);
    }
    
    return 0;
}

