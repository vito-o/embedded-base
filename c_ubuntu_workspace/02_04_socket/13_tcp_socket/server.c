#include "tcpsocket.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sfd, cfd;
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

    bzero(&cli_addr, sizeof(struct sockaddr_in));

    cfd = wait_for_connect(sfd, &cli_addr);
    if (cfd == -1)
    {
        exit(EXIT_FAILURE);
    }

    show_tcp_network_address(&cli_addr);

    close(cfd);
    close(sfd);

    return 0;
}
