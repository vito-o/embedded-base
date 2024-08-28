#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    char *pret = NULL;
    char buffer[64] = {0};

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
        pret = fgets(buffer, sizeof(buffer), fp);
        if (pret == NULL)
        {
            break;
        }

        fputs(buffer, stdout);
    }


    fclose(fp);

    return 0;
}
