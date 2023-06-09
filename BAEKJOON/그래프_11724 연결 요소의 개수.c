#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define TRUE	1
#define FALSE	0

#define QUE_LEN	1000

typedef int Data;

typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next;
} Node;

typedef struct _linkedList
{
	Node* head;
	Node* cur;
	Node* before;
	int numOfData;
	int (*comp)(LData d1, LData d2);
} LinkedList;


typedef LinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, LData data);

int LFirst(List* plist, LData* pdata);
int LNext(List* plist, LData* pdata);

LData LRemove(List* plist);
int LCount(List* plist);

typedef struct _cQueue
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
} CQueue;

typedef CQueue Queue;

void QueueInit(Queue* pq);
int QIsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data QPeek(Queue* pq);

typedef struct _ual
{
	int numV;   // ������ ��
	int numE;   // ������ ��
	List* adjList;   // ������ ����
	int* visitInfo;
} ALGraph;

// �׷����� �ʱ�ȭ
void GraphInit(ALGraph* pg, int nv);

// �׷����� ���ҽ� ����
void GraphDestroy(ALGraph* pg);

// ������ �߰�
void AddEdge(ALGraph* pg, int fromV, int toV);

// ��ƿ��Ƽ �Լ�: ������ ���� ���
void ShowGraphEdgeInfo(ALGraph* pg);

// Breadth First Search: ������ ���� ���
int BFShowGraphVertex(ALGraph* pg, int startV);


int main(void)
{
	ALGraph graph;
	int result = 0;
	int N, M, u, v;
	scanf("%d %d", &N, &M);
	GraphInit(&graph, N+1);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		AddEdge(&graph, u, v);
	}
	for (int i = 1; i <= N; i++) {
		if (BFShowGraphVertex(&graph, i) > 1)
			result++;
	}
	if (M == 0) result = N;
	printf("%d", result);
	return 0;
}

void QueueInit(Queue* pq)
{
	pq->front = 0;
	pq->rear = 0;
}

int QIsEmpty(Queue* pq)
{
	if (pq->front == pq->rear)
		return TRUE;
	else
		return FALSE;
}

int NextPosIdx(int pos)
{
	if (pos == QUE_LEN - 1)
		return 0;
	else
		return pos + 1;
}

void Enqueue(Queue* pq, Data data)
{
	if (NextPosIdx(pq->rear) == pq->front)
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);
	pq->queArr[pq->rear] = data;
}

Data Dequeue(Queue* pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);
	return pq->queArr[pq->front];
}

Data QPeek(Queue* pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	return pq->queArr[NextPosIdx(pq->front)];
}

// �׷����� �ʱ�ȭ
void GraphInit(ALGraph* pg, int nv)
{
	int i;

	pg->adjList = (List*)malloc(sizeof(List) * nv);
	pg->numV = nv;
	pg->numE = 0;     // �ʱ��� ���� ���� 0��

	for (i = 0; i < nv; i++)
	{
		ListInit(&(pg->adjList[i]));
	}

	// Ž�� ���� ����� ���� ������ �Ҵ� �� �ʱ�ȭ
	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

// �׷����� ���ҽ� ����
void GraphDestroy(ALGraph* pg)
{
	if (pg->adjList != NULL)
		free(pg->adjList);

	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

// ������ �߰�
void AddEdge(ALGraph* pg, int fromV, int toV)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

// ��ƿ��Ƽ �Լ�: ������ ���� ���
void ShowGraphEdgeInfo(ALGraph* pg)
{
	int i;
	int vx;

	for (i = 0; i < pg->numV; i++)
	{
		printf("%d�� ����� ����: ", i);

		if (LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%d ", vx);

			while (LNext(&(pg->adjList[i]), &vx))
				printf("%d ", vx);
		}
		printf("\n");
	}
}


int VisitVertex(ALGraph* pg, int visitV)
{
	if (pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;
		//printf("%d ", visitV);    // �湮 ���� ���
		return TRUE;
	}

	return FALSE;
}

// Breadth First Search: ������ ���� ���
int BFShowGraphVertex(ALGraph* pg, int startV)
{
	Queue queue;
	int visitV = startV;
	int nextV;
	int result = 0;
	int link = 0;
	// DFS�� ���� ť�� �ʱ�ȭ
	QueueInit(&queue);

	// ���� ���� Ž��
	VisitVertex(pg, visitV);
	result ++;
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		link = 1;
		if (VisitVertex(pg, nextV) == TRUE) {
			Enqueue(&queue, nextV);
			result ++;
		}

		while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
		{
			if (VisitVertex(pg, nextV) == TRUE) {
				Enqueue(&queue, nextV);
				result += 1;
			}
		}

		if (QIsEmpty(&queue) == TRUE)    // ť�� ��� BFS ����
			break;
		else
			visitV = Dequeue(&queue);
	}

	//// Ž�� ���� �ʱ�ȭ
	//memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	if (result == 1 && link == 0)
		result++;
	return result;
}

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;
	newNode->data = data;

	while (pred->next != NULL &&
		plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;
}


void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)
		FInsert(plist, data);
	else
		SInsert(plist, data);
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List* plist)
{
	return plist->numOfData;
}