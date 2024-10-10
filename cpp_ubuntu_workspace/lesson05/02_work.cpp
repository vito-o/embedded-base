#include <iostream>

using namespace std;

int* create()
{
    int *p = new int[10];
    return p;
}

void insert(int *p, int num)
{
    *p = num;
}

int main(int argc, char const *argv[])
{
    int *p = create();

    int index = 0;
    for (int i = 0x00; i <= 0x99; i = i+0x11)
    {
        insert(&p[index++], i);
    }

    for(int i = 0; i < 10; i++)
    {
        cout << "p[" << i << "] = " << std::hex << p[i] << endl;
    }

    delete [] p;
}