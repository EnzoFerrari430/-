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

    //�������Ĭ�ϵĿ������캯��  �򵥵ĸ���
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
    A b(a);  //�����д�������캯����Ĭ����ǳ����

    return 0;
}
