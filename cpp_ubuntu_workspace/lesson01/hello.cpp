#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    
    cout << "c++: hello world" << endl;

    printf("c: hello world\n");

    int data = 100;
    const char *str = "hello world";
    int a[] = {1,2,3,4,5,6};

    cout << data << endl;
    cout << str << endl;
    cout << a[0] << endl;

    return 0;
}
