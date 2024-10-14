#include <iostream>
#include <string.h>

using namespace std;

template <typename T>
class SharedPtr
{
    public:
        // explicit 的主要作用是避免无意中发生隐式转换，确保构造函数或类型转换运算符只能通过显式调用来使用
        explicit SharedPtr(T *_ptr = NULL): ptr(_ptr), countRef(new long(1))
        {}

        SharedPtr(const SharedPtr<T> &other):
            ptr(other.ptr),
			countRef(other.countRef)
        {
            (*countRef) ++;
        }

        SharedPtr<T> operator=(const SharedPtr<T> &other)
        {
            if (this != &other) {
                this->release();
				ptr = other.ptr;
				countRef = other.countRef;
                (*countRef) ++;
            }
            return *this;
        }

        T & operator*(void) 
        {
            return *ptr;
        }

        T * operator->(void)
        {
            return ptr;
        }

        T *getPtr(void)
        {
            return ptr;
        }

        int getCountRef(void)
		{
			return *countRef;
		}

        ~SharedPtr() 
        {
            release();
        }

    protected:
        void release(void)
        {
            (*countRef) --;

            if(*countRef == 0){
				if(ptr != NULL){
					delete ptr;
				}

				delete countRef;
			}
        }

    private:
        T *ptr;
        long *countRef;
};

// -------------------------------------------------------------------------
class Test{
	public:
		Test(const char *str = NULL)
		{
			cout << "Test(const char *str)" << endl;
			if(str != NULL){
				this->str = new char[strlen(str) + 1];
				strcpy(this->str,str);
			}else{
				this->str = NULL;
			}
		}

		~Test()
		{
			cout << "~Test()" << endl;
			if(str){
				delete[] str;
			}
		}

		void show(void ) const
		{
			cout << str << endl;
		}

	private:
		char *str;
};
// -------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
    SharedPtr<Test> obj1(new Test("hello world"));
	SharedPtr<Test> obj2 = obj1;

    obj1->show();

    obj2 = obj1;
    (*obj2).show();

    return 0;
}
