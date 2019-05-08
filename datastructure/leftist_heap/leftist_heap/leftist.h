#pragma once

typedef int Type;

typedef struct _LeftistNode
{
	Type key;
	int npl;
	struct _LeftistNode *left;
	struct _LeftistNode *right;
}LeftistNode, *LeftistHeap;

//ǰ�����
void preorder_leftist(LeftistHeap heap);
//�������
void inorder_leftist(LeftistHeap heap);
//�������
void postorder_leftist(LeftistHeap heap);

//��ȡ��Сֵ  �ɹ�����0  ʧ�ܷ���-1
int leftist_minimum(LeftistHeap heap, int *pval);

//�ϲ� �����x �������y  �����غϲ��������
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y);

//���ڵ�x���뵽������У������ظ��ڵ�
LeftistNode* insert_leftist(LeftistHeap heap, Type key);

//ɾ���ڵ�(keyΪ�ڵ��ֵ)  �����ظ��ڵ�
LeftistNode* delete_leftist(LeftistHeap heap);

//���������
void destroy_leftist(LeftistHeap heap);

//��ӡ�����
void print_leftist(LeftistHeap heap);