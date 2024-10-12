#include <iostream>
// 模板非类型参数

// 限制
// 非类型参数只能是整数、枚举类型、指向外部链接的指针
// 非类型参数不能是一个浮点类型和类类型


using namespace std;

template<typename T, int size>
class SeqList
{
    public:
        SeqList()
        {
            if (size <= 0) {
                cout << "Invalid argument: " << size << endl;
                return;
            }

            buf = new T[size];
            this->buf = buf;
            this->index = 0;
        }

        ~SeqList() 
        {
            if (buf)
                delete [] buf;
        }

        int addData(const T &data)
        {
            if (index >= size) {
                cout << "The seqlist is full" << endl;
                return -1;
            }
            buf[index] = data;
            index++;

            return index;
        }

        void show() const
        {
            for (int i = 0; i < index; i++) {
                cout << buf[i] << endl;
            }
        }
    
    private:
        T *buf;
        int index;
};

int main(int argc, char const *argv[])
{
    SeqList<string, 10> list;  

    list.addData("hell");
    list.addData("word");
    list.show();
    return 0;
}
