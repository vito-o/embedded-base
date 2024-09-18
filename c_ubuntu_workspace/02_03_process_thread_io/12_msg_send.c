#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATHNAME "."
#define PRO_ID 10

#define MSG_TYPE 100
#define MSG_SZ 64

struct msgbuf {
    long mtype;
    char mtext[MSG_SZ];
};

int main(int argc, char const *argv[])
{
    key_t key;
    int msgid, ret;
    ssize_t rbtyes;
    struct msgbuf msg;

    key = ftok(PATHNAME, PRO_ID);
    if (key == -1)
    {
		perror("[ERROR] fotk(): ");
		exit(EXIT_FAILURE);
	}

    msgid = msgget(key, IPC_CREAT | 0666);
    if(msgid == -1)
    {
		perror("msgget(): ");
		exit(EXIT_FAILURE);
	}

    printf("msg id : %d\n",msgid);

    msg.mtype = MSG_TYPE;
    strcpy(msg.mtext, "Hello .sg queue");

    ret = msgsnd(msgid, (void *)&msg, strlen(msg.mtext)+1, 0);
    if(ret == -1)
    {
		perror("msgsnd(): ");
		exit(EXIT_FAILURE);
	}
    
    return 0;
}
