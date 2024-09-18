#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 非阻塞型 io
int main(int argc, char const *argv[])
{
    
    int flags;
    char buffer[16] = { 0 };

    flags = fcntl(0, F_GETFL);  // 获取原来文件状态标志
    flags |= O_NONBLOCK;        // 追加阻塞标志

    fcntl(0, F_SETFL, flags);   // 重新设置文件状态标志

    while(1) 
    {
        fgets(buffer, sizeof(buffer), stdin);
        printf("buffer : %s\n", buffer);
    }


    return 0;
}
