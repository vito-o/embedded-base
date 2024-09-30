#include "tcpsocket.h"
#include <unistd.h>
#include "file_transfer.h"

int main(int argc, char const *argv[])
{
    int cfd;

    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s < ip > < port > < pathname > .\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    cfd = create_tcp_client_socket(argv[1], atoi(argv[2]));
    if (cfd == -1)
    {
        exit(EXIT_FAILURE);
    }

    upload_file(argv[3], cfd);

    close(cfd);

    return 0;
}
