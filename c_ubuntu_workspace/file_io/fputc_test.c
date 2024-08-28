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
    FILE *ioFIle = fopen(filename, "w");
    if (ioFIle == NULL)
    {
        printf("FAILED, a+不能打开不存在的文件\n");
    }
    else
    {
        printf("SUCCESS, a+能打开不存在的文件\n");
    }


    /*
        int __c: ASCII码对应的char
        FILE *__stream: 打开的一个文件
        int fputc (int __c, FILE *__stream);
    */
    int put_result = fputc(97, ioFIle);
    if (put_result == EOF)
    {
        printf("写入文件失败\n");
    }
    else 
    {
        printf("写入%c成功\n", put_result);
    }

    /*
        读写权限记录在fopen方法中的参数
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
