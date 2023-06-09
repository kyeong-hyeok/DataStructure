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
	int numV;   // 정점의 수
	int numE;   // 간선의 수
	List* adjList;   // 간선의 정보
	int* visitInfo;
} ALGraph;

// 그래프의 초기화
void GraphInit(ALGraph* pg, int nv);

// 그래프의 리소스 해제
void GraphDestroy(ALGraph* pg);

// 간선의 추가
void AddEdge(ALGraph* pg, int fromV, int toV);

// 유틸리티 함수: 간선의 정보 출력
void ShowGraphEdgeInfo(ALGraph* pg);

// Breadth First Search: 정점의 정보 출력
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

// 그래프의 초기화
void GraphInit(ALGraph* pg, int nv)
{
	int i;

	pg->adjList = (List*)malloc(sizeof(List) * nv);
	pg->numV = nv;
	pg->numE = 0;     // 초기의 간선 수는 0개

	for (i = 0; i < nv; i++)
	{
		ListInit(&(pg->adjList[i]));
	}

	// 탐색 정보 등록을 위한 공간의 할당 및 초기화
	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

// 그래프의 리소스 해제
void GraphDestroy(ALGraph* pg)
{
	if (pg->adjList != NULL)
		free(pg->adjList);

	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

// 간선의 추가
void AddEdge(ALGraph* pg, int fromV, int toV)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

// 유틸리티 함수: 간선의 정보 출력
void ShowGraphEdgeInfo(ALGraph* pg)
{
	int i;
	int vx;

	for (i = 0; i < pg->numV; i++)
	{
		printf("%d와 연결된 정점: ", i);

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
		//printf("%d ", visitV);    // 방문 정점 출력
		return TRUE;
	}

	return FALSE;
}

// Breadth First Search: 정점의 정보 출력
int BFShowGraphVertex(ALGraph* pg, int startV)
{
	Queue queue;
	int visitV = startV;
	int nextV;
	int result = 0;
	int link = 0;
	// DFS를 위한 큐의 초기화
	QueueInit(&queue);

	// 시작 정점 탐색
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

		if (QIsEmpty(&queue) == TRUE)    // 큐가 비면 BFS 종료
			break;
		else
			visitV = Dequeue(&queue);
	}

	//// 탐색 정보 초기화
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