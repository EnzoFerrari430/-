/*
�������һ�ö����������Ľڵ������������ָ��֮�⣬����2�����ԣ���ֵ�������
	1.��ֵ�������ǱȽϽڵ�Ĵ�С���Ӷ��Խڵ��������
	2.�����(NPL Null Path Length)���Ǵ�һ���ڵ㵽һ��"����Ĳ����ڵ�"��·�����ȡ������ڵ���ָ�ýڵ�����Һ���������һ��ΪNULL��Ҷ�ڵ��NPLΪ0��NULL�ڵ��NPLΪ-1

����ѵĻ�������
	1.�ڵ�ļ�ֵС�ڻ�����������Һ��ӽڵ�ļ�ֵ
	2.�ڵ�����ӵ�NPL >= �Һ��ӵ�NPL
	3.�ڵ��NPL = �����Һ��ӵ�NPL + 1

������ܺܺõĽ�� "�ϲ��������ȶ���" �����⡣  ����ѵĺϲ�������ƽ̯ʱ�临�Ӷ���O(logn),����ȫ�����ΪO(n)
�ϲ���������ѵ��ص㣬 �����ɾ���Ĳ��������Ժϲ�Ϊ����   ��������Ϳ��Կ���2�ö������ϲ�  ɾ�������Ϳ��Կ����Ƴ����ڵ���ٺϲ���������������

�ϲ�2������ѵĻ���˼��
	1.���һ�����������һ���ǿ�����Ѻϲ������طǿ������
	2.�����������Ѷ��ǿգ���ô�Ƚ��������ڵ㣬ȡ��С�ѵĸ��ڵ�Ϊ�µĸ��ڵ㡣��"��С�ѵĸ��ڵ���Һ���"��"�ϴ��"���кϲ�
	3.����¶ѵ��Һ��ӵ�NPL > ���ӵ�NPL�� �򽻻����Һ���
	4.�����¶ѵĸ��ڵ��NPL = ���Ӷѵ�NPL + 1

*/
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "leftist.h"

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

int main()
{
	int i;
	int a[] = { 10,40,24,30,36,20,12,16 };
	int b[] = { 17,13,11,15,19,21,23 };
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	LeftistHeap ha, hb;
	ha = hb = NULL;

	printf("\n== �����(ha)�������: ");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		ha = insert_leftist(ha, a[i]);
	}
	printf("\n== �����(ha)����ϸ��Ϣ: \n");
	print_leftist(ha);

	printf("\n== �����(hb)�������: ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = insert_leftist(hb, b[i]);
	}
	printf("\n== �����(ha)����ϸ��Ϣ: \n");
	print_leftist(hb);

	ha = merge_leftist(ha, hb);
	printf("\n== �ϲ�ha��hb�����ϸ��Ϣ: \n");
	print_leftist(ha);


	destroy_leftist(ha);

	system("pause");
	return 0;

}

