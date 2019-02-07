#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <bitset>

using namespace std;


void Swap(int *,int *);
void Swap1(int &,int &);
void Swap2(int &,int &);

void select_sort(int a[],int n)
{
	int i,j, nMinIndex;
	for( i = 0 ; i < n ; ++i )
	{
		nMinIndex = i;
		for(j = i + 1 ; j < n ; ++j )
		{
			if( a[j] < a[nMinIndex] )
			{
				nMinIndex = j;
			}
		}
		Swap(&a[i],&a[nMinIndex]);

	}
}

void Swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Swap1(int &a,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Swap2(int &a,int &b)
{
	/*
		a ^= b : a = a^b
		b ^= a : b = b^(a^b) = a^(b^b) = a ^ 0 = a
		a ^= b : a = (a^b)^a = a^a^b = 0^b = b
		有前提条件：a b不是同一个元素
		如果是同一个元素
		a ^= b : a = a ^ a = 0;
		b ^= a : b = b ^ b = 0;
		a ^= b : a = b ^ b = 0;
	*/
	if( a != b)
	{
		//cout<<"binary of a: "<<bitset<sizeof(int)*8>(a)<<endl;
		//cout<<"binary of b: "<<bitset<sizeof(int)*8>(b)<<endl;
		a ^= b;
		//cout<<bitset<sizeof(int)*8>(a)<<endl;
		b ^= a;
		//cout<<bitset<sizeof(int)*8>(b)<<endl;
		a ^= b;
		//cout<<bitset<sizeof(int)*8>(a)<<endl;
	}

}

void Swap3(int &a,int &b)
{
	/*
		a = a + b
		b = a - b : b = a + b - b = a;
		a = a - b : a = a + b - a = b
		有一个前提条件：a b不是同一个元素
		如果是同一个元素
		b = a - b : b = b - b = 0;
		a = a - b : a = a - a = 0;
	*/
	if( a != b )
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}

}

void print(int a[],int n)
{
	for(int i = 0 ; i < n ; ++i )
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main()
{
	int a[10] = {0,1,2,3,4,5,6,7,8,9};
	select_sort(a,10);
	print(a,10);
	

	int c = 5;
	int d = 10;
	Swap3(c,c);
	printf("%d %d\n",c,d);


	system("pause");
	return 0;
}