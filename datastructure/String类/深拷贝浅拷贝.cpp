#include <iostream>
#include <string>
using namespace std;


class A
{
public:
    A( int i )
    {
        data = new int;
        *data = i;
    }

    //这个就是默认的拷贝构造函数  简单的复制
    /*
    A(const A &b)
    {
        this->data = b.data;
    }
    */
    A(const A &b)
    {
        data = new int;
        *data = *(b.data);
    }

    ~A()
    {
        delete data;
    }
private:
    int* data;
};


int main()
{
    A a(1);
    A b(a);  //如果不写拷贝构造函数，默认是浅拷贝

    return 0;
}
