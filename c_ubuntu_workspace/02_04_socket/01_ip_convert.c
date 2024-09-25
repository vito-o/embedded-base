#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

// 将ip字符串 转变为 网络字节序列
// 第一种方法有bug，将255.255.255.255转变时会报-1
void ip_convert_first(const char *ip)
{
    in_addr_t net_addr;

    net_addr = inet_addr(ip);
    if (net_addr == INADDR_NONE)
    {
        perror("Fail to inet_addr(): ");
        exit(EXIT_FAILURE);
    }
    printf("net_addr = %#x\n", net_addr);
}

// 将ip字符串 转变为 网络字节序列
void ip_convert_second(const char *ip)
{
    struct in_addr net_addr;
    int ret;

    ret = inet_aton(ip, &net_addr);
    if (0 == ret)
    {
        perror("Fail to inet_aton(): ");
        exit(EXIT_FAILURE);
    }
    printf("net_addr = %#x\n", net_addr.s_addr);
}

// ./a.out 192.168.0.11
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s ip!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ip_convert_first(argv[1]);
    ip_convert_second(argv[1]);


    return 0;
}
