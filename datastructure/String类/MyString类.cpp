#include <iostream>
#include <string.h>

using namespace std;


class MyString
{
public:
    MyString(const char* str = NULL);  //���ַ���ֵ
    MyString(const MyString &s);       //�������캯��
    MyString& operator= (const MyString& s);  //������ֵ�����
    MyString& operator= (const char* str);    //������ֵ�����


    MyString(const MyString& s,int n);  //��c�ַ���s��ʼ��n���ַ���ֵ
    MyString(const char* s,int n);

    MyString(int n,char c);  //��n���ַ�c��ֵ����ǰ�ַ���

    MyString(const MyString& s,int start,int n);  //���ַ���s�д�start��ʼ��n���ַ���ֵ����ǰ�ַ���
    MyString(const char* s,int start,int n);

    int capacity() const;  //���ص�ǰ����

    int max_size() const;  //����MyString����ɴ�ŵ�����ַ����ĳ���

    int size() const;  //���ص�ǰ�ַ�����С

    int length() const;  //���ص�ǰ�ַ�������

    int empty() const;  //��ǰ�ַ����Ƿ�Ϊ��

    void resize(int len,char c);  //�ѵ�ǰ�ַ�����С��Ϊlen�������ַ�c��䲻��Ĳ���

    MyString& assign(const char* s);  //��s������m_data��

    MyString& assign(const MyString& s);


    const MyString& operator+=(const MyString& s);


private:
    char* m_data;
};

MyString::MyString(const char* str)
{
    if(str)
    {
        m_data = new char[strlen(str) + 1];  //��Ԥ��һ���ռ�
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

//������ֵ�����
MyString& MyString::operator=(const MyString& s)  //�������ã����������ã�������ֵ����return *this֮�����ϵ��ÿ������캯����2��Σ����1.��Դ�˷�  2.ҪС�ĺϳɿ������캯����ɵ�ǳ����
{
    if( s.m_data )
    {
        if(m_data)
        {
            delete []m_data;  //Ҫɾ��ԭ��������  ��Ϊԭ�������ݿ��ܱ����ڵ�Ҫ���������ݴ�
        }
        m_data = new char[s.size() + 1];
        strcpy(m_data,s.m_data);
    }
    return *this;  //����*this �����ȵ�ʱ������ c = b = a��   b = a ����һ��MyString����
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


//���캯�����ַ���s��ǰn���ַ�
MyString::MyString(const char* s,int n)
{
    if(s)
    {
        if(strlen(s) < n )
        {
            n = strlen(s);
        }
        m_data = new char[n+1];

        //char *strncpy(char *dest, const char *src, int n)����src��ָ����ַ�������src��ַ��ʼ��ǰn���ֽڸ��Ƶ�dest��ָ�������У������ر����ƺ��dest
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
        char* p = s.m_data + start - 1;  //�����Ԥ����һ��λ��
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
