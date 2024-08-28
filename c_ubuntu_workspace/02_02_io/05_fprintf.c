#include <stdio.h>
// stdout: 标准输出，所谓标准是兼容个平台如mac linux
// 注意：在上述程序中，将\n去掉之后，在添加一个死循环后，则程序运行的结果则不同，这里与标准I/O的缓冲区有关系
int main()
{   
    // stdout默认是个行缓存， 有换行换行了就可以输出来了
    fprintf(stdout, "hello,linux io ~ stdout\n");
    fprintf(stderr, "hello,linux io ~ stderr\n");

    // 强制刷新缓冲区，
    // fflush(stdout);

    while (1) {}
    
    return 0;
}
