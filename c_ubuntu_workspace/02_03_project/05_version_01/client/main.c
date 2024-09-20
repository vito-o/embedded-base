#include "client.h"

int main()
{
    client_init();

    // subscribe("hello");

    publish("hello", "ABDEFaaa");

    while (1)
    {
        /* code */
    }
    

    return 0;
}
