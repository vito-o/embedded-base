#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "sem.h"

#define SEM_CONTROL_P 0
#define SEM_CONTROL_C 1

int main() 
{
    pid_t cpid;

    int semid;
    unsigned short values[] = { 1, 0 };

    semid = sem_create(2, values);
    if (semid == -1)
    {
        return -1;
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        while(1)
        {   
            sem_p(semid, SEM_CONTROL_C);
            printf("B");
            fflush(stdout);
            sem_v(semid, SEM_CONTROL_P);
        }
    }
    else if (cpid > 0)
    {
        while(1)
        {   
            sem_p(semid, SEM_CONTROL_P);
            printf("A");
            fflush(stdout);
            sem_v(semid, SEM_CONTROL_C);
            sem_p(semid, SEM_CONTROL_P);
            printf("A");
            fflush(stdout);
            sem_v(semid, SEM_CONTROL_P);
            sleep(1);
            putchar('\n');
        }

        wait(NULL);

        sem_del(semid);
    }
    

}