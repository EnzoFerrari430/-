#include <iostream>
#include <string.h>

using namespace std;


class MyString
{
public:
    MyString(const char* str = NULL);  //用字符赋值
    MyString(const MyString &s);       //拷贝构造函数
    MyString& operator= (const MyString& s);  //拷贝赋值运算符
    MyString& operator= (const char* str);    //拷贝赋值运算符


    MyString(const MyString& s,int n);  //从c字符串s开始的n个字符赋值
    MyString(const char* s,int n);

    MyString(int n,char c);  //用n个字符c赋值给当前字符串

    MyString(const MyString& s,int start,int n);  //把字符串s中从start开始的n个字符赋值给当前字符串
    MyString(const char* s,int start,int n);

    int capacity() const;  //返回当前容量

    int max_size() const;  //返回MyString对象可存放的最大字符串的长度

    int size() const;  //返回当前字符串大小

    int length() const;  //返回当前字符串长度

    int empty() const;  //当前字符串是否为空

    void resize(int len,char c);  //把当前字符串大小置为len，并用字符c填充不足的部分

    MyString& assign(const char* s);  //把s拷贝到m_data中

    MyString& assign(const MyString& s);


    const MyString& operator+=(const MyString& s);


private:
    char* m_data;
};

MyString::MyString(const char* str)
{
    if(str)
    {
        m_data = new char[strlen(str) + 1];  //多预留一个空间
        strcpy(m_data,str);
    }
    else
    {
        m_data = NULL;  //
    }
}

MyString::MyString(const MyString& s)
{
    if( s.m_data )
    {
        m_data = new char[s.size() + 1];
        strcpy(m_data,s.m_data);
    }
    else
    {
        m_data = NULL;
    }
}

MyString::~MyString()
{
    if( m_data )
    {
        delete []m_data;
    }
}

//拷贝赋值运算符
MyString& MyString::operator=(const MyString& s)  //返回引用：不返回引用，而返回值会在return *this之后马上调用拷贝构造函数，2个危害：1.资源浪费  2.要小心合成拷贝构造函数造成的浅拷贝
{
    if( s.m_data )
    {
        if(m_data)
        {
            delete []m_data;  //要删除原来的内容  因为原来的内容可能比现在的要拷贝的内容大。
        }
        m_data = new char[s.size() + 1];
        strcpy(m_data,s.m_data);
    }
    return *this;  //返回*this 在连等的时候有用 c = b = a，   b = a 返回一个MyString对象
}

MyString& MyString::operator=(const char* str)
{
    if(str)
    {
        if(m_data)
        {
            delete []m_data;
        }
        m_data = new char[strlen(str)+1];
        strcpy(m_data,str);
    }

    return *this;
}


//构造函数，字符串s的前n个字符
MyString::MyString(const char* s,int n)
{
    if(s)
    {
        if(strlen(s) < n )
        {
            n = strlen(s);
        }
        m_data = new char[n+1];

        //char *strncpy(char *dest, const char *src, int n)，把src所指向的字符串中以src地址开始的前n个字节复制到dest所指的数组中，并返回被复制后的dest
        strncpy(m_data,s,n);
    }
    else
    {
        m_data = NULL;
    }
}

MyString::MyString(const MyString& s)
{
    if(s.m_data)
    {
        if(s.size() < n)
        {
            n = s.size();
        }

        m_data = new char[n+1];
        strncpy(m_data,s.m_data,n);
    }
    else
    {
        m_data = NULL;
    }
}

MyString::MyString(const MyString& s,int start,int n)
{
    if(start < s.size() )
    {
        char* p = s.m_data + start - 1;  //后面多预留了一个位置
        int m = strlen(p);

        if( m < n )
        {
            n = m;
        }
        m_data = new char[n + 1];
        strncpy(m_data,p,n);
    }
}

MyString::MyString(const char* s,int start,int n)
{
    if( start < strlen(s) )
    {
        const char* p = s + start - 1;
        int m = strlen(p);
        if( m < n )
        {
            n = m;
        }
        m_data = new char[n + 1];
        strncpy(m_data,p,n);
    }
}

MyString::MyString(int n,char c)
{
    m_data = new char[n+1];
    memset(m_data,c,n);
}

MyString& MyString::assign(const char* s)
{
    if(s)
    {
        if(m_data)
        {
            delete []m_data;
        }
        m_data = new char[strlen(s)+1];
        strcpy(m_data,s);
    }

    return *this;
}

MyString& MyString::assign(const MyString& s)
{
    if(s.m_data)
    {
        if(m_data)
        {
            delete []m_data;
        }
        m_data = new char[s.size()+1];
        strcpy(m_data,s.m_data);
    }

    return *this;
}

const MyString& MyString::operator+=(const MyString& s)
{
    if(s.m_data)
    {
        int size_l = this->size();
        char* temp = new char[size_l + s.size() + 1];
        if(m_data)
        {
            strcpy(temp,m_data);
            delete []m_data;
        }
        strcat(temp,s.m_data);
        m_data = temp;
    }
    return *this;
}

int MyString::size() const
{
    if(m_data)
    {
        return strlen(m_data);
    }
    return 0;
}
