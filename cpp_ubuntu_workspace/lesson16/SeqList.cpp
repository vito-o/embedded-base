#include <iostream>
// 泛型类
using namespace std;

template<typename T>
class SeqList {
    public:
        SeqList(int size);
        void addData(const T &data) 
        {
            if (index >= size) {
                cout << "The seqlist is full" << endl;
                return;
            }
            buf[index] = data;
            index++;
        }
        void show(void) const
        {
            for (int i = 0; i < index; i++) {
                cout << buf[i] << endl;
            }
        }

        ~SeqList() 
        {
            if (buf)
                delete [] buf;
        }
        

    private:
        int size;
        T *buf;
        int index;
};

// 外部写法，（推荐使用内部写法），外部写法比较麻烦
template<typename T>
SeqList<T>::SeqList(int size)
{
    if (size <= 0) {
        cout << "Invalid argument: " << size << endl;
        return;
    }

    this->size = size;
    buf = new T[size];
    this->buf = buf;
    this->index = 0;
}

int main(int argc, char const *argv[])
{
    
    SeqList<string> list(10);
    list.addData("hell");
    list.addData("word");
    list.show();
    return 0;
}
