#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef int Data;

typedef struct _node {
	Data data;
	struct _node* next;
}Node;

typedef struct _CLL
{
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
} CList;

typedef CList List;
void ListInit(List* plist);
void ListInsert(List* plist, Data data);
int ListRemove(List* plist);
int LFirst(List* plist);
int LNext(List* plist);

int main() {
	Data N, K, a=1, k=0;
	List list;
	Data* result;
	scanf("%d %d", &N, &K);
	result = (Data*)malloc(N * sizeof(Data));
	ListInit(&list);		// �ʱ�ȭ
	for (int i = N; i >= 1; i--) {
		ListInsert(&list, i);		// N������ 1������ ������� ����
	}
	LFirst(&list);
	while (1) {
		for (int i = 0; i < K; i++)
			a = LNext(&list);
		if (a == 0) break;		// ����� ��尡 ���ٸ� ����������
		result[k] = ListRemove(&list);	// ���� ��� ��ȣ ����
		k++;
	}
	printf("<");
	for (int i = 0; i < N; i++) {
		printf("%d", result[i]);
		if (i != N - 1)
			printf(", ");
		else
			printf(">");
	}
	return 0;
}

void ListInit(List* plist) {
	plist->before = NULL;
	plist->cur = NULL;
	plist->numOfData = 0;
	plist->tail = NULL;
}

void ListInsert(List* plist, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	if (plist->tail == NULL) {
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
	}
	(plist->numOfData)++;
}

int ListRemove(List* plist) {
	Node* rpos = plist->cur;
	Data data = rpos->data;
	if (rpos == plist->tail) {
		if (plist->tail == plist->tail->next) {
			plist->tail = NULL;
			return data;
		}
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return data;
}

int LFirst(List* plist)
{
	if (plist->tail == NULL)
		return 0;
	plist->cur = plist->tail;
	return 1;
}

int LNext(List* plist)
{
	if (plist->tail == NULL)    // ����� ��尡 ���ٸ�
		return 0;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;
	return 1;
}
