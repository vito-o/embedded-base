#include <stdio.h>

int main()
{
    /*
    char *__restrict __filename: 字符串表示要打开文件的路经和名称
    const char *__restrict __modes：字符串表示访问模式
    1》"r": 只读模式 没有文件打开失败
    2》"w": 只写模式 存在文件写入会清空文件，不存在文件则创建新文件
    3》"a": 只追加写模式 不会覆盖原有内容 新内容写到末尾 如果文件不存在则创建
    4》"r+": 读写模式 文件必须存在 写入是从头一个一个覆盖
    5》"w+": 读写模式 可读取，写入同样会清空文件内容，不存在则创建新文件
    6》"a+": 读写追加模式 可读取，写入从文件末尾开始，如果文件不存在则创建
    return FILE * 结构体指针 表示一个文件
    FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes)
    */
    char *filename = "io.txt";
    FILE *ioFIle = fopen(filename, "r");
    if (ioFIle == NULL)
    {
        printf("FAILED, a+不能打开不存在的文件\n");
    }
    else
    {
        printf("SUCCESS, a+能打开不存在的文件\n");
    }


    /*
        char *__restrict __s: 接收读取的数据字符串
        int __n: 能够接收数据的长度
        FILE *__restrict __stream: 需要读取的文件
        return: 成功返回字符串 失败返回NULL（可以直接用于while）
        fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
    */
    char buffer[100];
    while(fgets(buffer, sizeof(buffer), ioFIle))
    {
        printf("%s", buffer);
    }


    /*
        FILE *__stream: 需要关闭的文件
        return: 成功返回0 失败返回EOF（负数）  通常关闭文件失败会直接报错
        int fclose(FILE *__stream)
    
     */
    int result = fclose(ioFIle);
    if (result == EOF)
    {
        printf("关闭文件失败\n");
    }
    else if (result == 0)
    {
        printf("关闭文件成功\n");
    }


    return 0;
}
