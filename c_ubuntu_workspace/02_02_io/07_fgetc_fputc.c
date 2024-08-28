#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    char ch;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname> \n", argv[0]);
        return -1;
    }

    fp = fopen(argv[1], "r");  // 
    if (fp == NULL)
    {
        perror("Error fopen(): ");
        return -1;
    }
    
    for (;;)
    {
        ch = fgetc(fp);
        if (ch == EOF)
        {
            break;
        }

        fputc(ch, stdout);
    }


    fclose(fp);

    return 0;
}
