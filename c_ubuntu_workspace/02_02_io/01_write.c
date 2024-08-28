#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    write(0, "helloworld\n", 11);
    return 0;
}
