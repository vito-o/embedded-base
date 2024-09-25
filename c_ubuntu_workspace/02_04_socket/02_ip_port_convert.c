#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

// 将ip字符串 转变为 网络字节序列
// 将port字符串 转变为 网络字节序列
void ip_port_convert(const char *ip, const char *port)
{
    in_addr_t net_addr;
    uint16_t net_port;
    uint16_t host_port;

    // 将ip字符串 转变为 网络字节序列
    net_addr = inet_addr(ip);
    if (net_addr == INADDR_NONE)
    {
        perror("Fail to inet_addr(): ");
        exit(EXIT_FAILURE);
    }
    printf("net_addr = %#x\n", net_addr);

    // 将port字符串 转变为 网络字节序列
    net_port = htons(atoi(port));
    printf("net_port = %#x\n", net_port);

    // 将网络字节序列的ip 转变为 host ip
    struct in_addr addr;
    addr.s_addr = net_addr;
    printf("host_ip = %s\n", inet_ntoa(addr));
}

// ./a.out 192.168.0.11 8979
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s ip port!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ip_port_convert(argv[1], argv[2]);


    return 0;
}
