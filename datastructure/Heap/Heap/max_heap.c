/*
�ѵĶ���:
	��(heap),������˵�Ķ������ݽṹ�еĶѣ��������ڴ�ģ���еĶѣ���ͨ����һ�����Ա�����һ��������������������
		1.�����������ֵ���ǲ����ڣ���С�ڣ����ӽڵ��ֵ
		2.������һ����ȫ��

����ѵĶ��壺
	���������ȫ���������߽�����ȫ������������Ϊ���֣����Ѻ���С��
	���ѣ����ڵ�ļ�ֵ���Ǵ��ڻ�����κ�һ���ӽڵ�ļ�ֵ
	��С�ѣ����ڵ�ļ�ֵ����С�ڻ�����κ�һ���ӽڵ�ļ�ֵ

�����һ����������ʵ��
	int a[9] = {90,80,70,60,40,30,20,10,50};
	���ѵ�����(��һ��Ԫ�ص�����Ϊ0)
	1.����Ϊi�����ӵ�������2*i+1
	2.����Ϊi���Һ��ӵ�������2*i+2
	3.����Ϊi�ĸ��ڵ�������� (i-1)/2  �����������ʡȥС�����֣�



���
	����������[90,80,70,60,40,30,20,10,50]�����85 ��������
		1.��85�ӵ�ĩβ
		2.85���ڸ��ڵ�(40)�������͸��ڵ㽻��
		3.�ظ��ڶ�����ֱ��С�ڸ��ڵ����ڵ�


ɾ��
	���������[90,85,70,60,80,30,20,10,50,40]��ɾ��90 ��������
		1.��90�Ӷ������ɾ��
		2.��ĩβԪ���滻��ɾ��������
		3.40С���ӽڵ㣬ѡȡ�ϴ���ӽڵ��������
		4.�ظ�����3��ֱ��40��С���ӽڵ����40����ĩβ

	
*/
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a))/sizeof((a[0])))

static int m_heap[30];			//����
static int m_capacity = 30;		//�ܵ�����
static int m_size = 0;			//ʵ������

/*
���ѵ����ϵ����㷨(��start��ʼ���ϣ�ֱ��0��������)

����:start���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
*/

static void maxheap_filterup(int start)
{
	int c = start;
	int p = (c - 1) / 2;
	int tmp = m_heap[c];  //��ǰ�ڵ�current��С
	while (c > 0)
	{
		if (m_heap[p] >= tmp)
			break;
		else
		{
			m_heap[c] = m_heap[p];
			c = p;
			p = (p - 1) / 2;
		}
	}
	m_heap[c] = tmp;
}

/*
��data���뵽��������

����0 ��ʾ�ɹ�
����-1��ʾʧ��

*/

int maxheap_insert(int data)
{
	if (m_size == m_capacity)
		return -1;
	m_heap[m_size] = data;
	maxheap_filterup(m_size);
	m_size++;

	return 0;
}



/*
���ѵ�ɾ������

����data�ڶ�����е�����

����ֵ��
	����		����data�������е�����
	������	����-1

*/
int get_index(int data)
{
	int i = 0;
	for (i = 0; i < m_size; ++i)
	{
		if (data == m_heap[i])
		{
			return i;
		}
	}
	return -1;
}

/*

���ѵ����µ����㷨

ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1),�Һ��ӵ�����ֵ��(2N+2)

����˵��
	start		���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�i��Ԫ�ؿ�ʼ)
	end			������Χ(һ��Ϊ���������һ��Ԫ�ص�����)

*/
static void maxheap_filterdown(int start, int end)
{
	int c = start;			//��ǰ�ڵ��λ��
	int l = 2 * c + 1;		//���ӵ�λ��
	int tmp = m_heap[c];	//��ǰ�ڵ�Ĵ�С

	while (l <= end)
	{
		//l������  l+1���Һ���
		if (l < end && m_heap[l] < m_heap[l + 1])
		{
			l++;  //���Һ�����ѡ��ϴ��ߣ��� m_heap[l+1]
		}
		if (tmp >= m_heap[l])
			break;  //��������
		else
		{
			m_heap[c] = m_heap[l];
			c = l;
			l = 2 * l + 1;
		}
	}
	m_heap[c] = tmp;
}

/*

ɾ�������е�data

����0 ��ʾ�ɹ�
����-1��ʾʧ��

*/

int maxheap_remove(int data)
{
	int index;
	//������ѿվͷ���-1
	if (m_size == 0)
		return -1;

	//��ȡdata�������е�����
	index = get_index(data);
	if (index == -1)
		return -1;

	m_heap[index] = m_heap[--m_size];  //������Ԫ�ز�
	maxheap_filterdown(index, m_size - 1);
	
	return 0;
}

void maxheap_print()
{
	int i;
	for (i = 0; i < m_size; ++i)
	{
		printf("%d ", m_heap[i]);
	}
}

//int main()
//{
//	int a[] = { 10,40,30,60,90,70,20,50,80 };
//	int i, len = LENGTH(a);
//	printf("== �������: ");
//	for (i = 0; i < len; ++i)
//	{
//		printf("%d ", a[i]);
//		maxheap_insert(a[i]);
//	}
//
//	printf("\n====  ����: ");
//	maxheap_print();
//
//	return 0;
//}