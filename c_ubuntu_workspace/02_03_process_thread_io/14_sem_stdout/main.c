#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "sem.h"

int main() 
{
    pid_t cpid;

    int semid;
    unsigned short values[] = { 1 };

    semid = sem_create(1, values);
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
            sem_p(semid, 0);
            printf("------------------------------\n");
            printf("C Start.\n");
			sleep(1);
			printf("C End.\n");
            printf("------------------------------\n");
            sem_v(semid, 0);
        }
    }
    else if (cpid > 0)
    {
        while(1)
        {   
            sem_p(semid, 0);
            printf("------------------------------\n");
            printf("P Start.\n");
			sleep(1);
			printf("P End.\n");
            printf("------------------------------\n");
            sem_v(semid, 0);
        }

        wait(NULL);

        sem_del(semid);
    }
    

}