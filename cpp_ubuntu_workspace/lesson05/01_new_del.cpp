#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int *p = (int *)malloc(4);
    int *q = new int;

    cout << "p value is : " << p << endl;
    cout << "a value is : " << q << endl;

    *p = 100;
    *q = 200;
    cout << "p value is : " << *p << endl;
    cout << "a value is : " << *q << endl;

    free(p);
    delete q;

    cout << "------------------------" << endl;

    int *m = new int[3];

    for (int i = 0; i < 3; i++)
    {
        m[i] = i+1;
    }
    
    for (int i = 0; i < 3; i++)
    {
        cout << "a value is : " << m[i] << endl;
    }

    delete [] m;

    return 0;
}
