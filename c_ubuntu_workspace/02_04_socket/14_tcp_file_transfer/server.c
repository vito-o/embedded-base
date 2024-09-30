#include "tcpsocket.h"
#include <unistd.h>
#include <pthread.h>
#include "debug.h"
#include "file_transfer.h"

void *do_task(void *arg)
{
    int cfd = *(int *)arg;

    client_upload_file(cfd);

    close(cfd);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int sfd, cfd, ret;
    pthread_t tid;
    struct sockaddr_in cli_addr;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s < ip > < port > .\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sfd = create_tcp_server_socket(argv[1], atoi(argv[2]));
    if (sfd == -1)
    {
        exit(EXIT_FAILURE);
    }

    for(;;)
    {
        bzero(&cli_addr, sizeof(struct sockaddr_in));

        cfd = wait_for_connect(sfd, &cli_addr);
        if (cfd == -1)
        {
            exit(EXIT_FAILURE);
        }

        show_tcp_network_address(&cli_addr);

        ret = pthread_create(&tid, NULL, do_task, (void *)&cfd);
        if (ret != 0)
        {
            DEBUG_INFO("[ERROR] Failed to pthread_create: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        pthread_detach(tid);
    }

    close(sfd);

    return 0;
}
