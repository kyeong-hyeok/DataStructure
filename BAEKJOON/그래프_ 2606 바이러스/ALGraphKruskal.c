#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALGraphKruskal.h"
#include "DLinkedList.h"
#include "ArrayBaseStack.h"

int WhoIsPrecede(int data1, int data2);
int PQWeightComp(Edge d1, Edge d2);

void GraphInit(ALGraph * pg, int nv)
{
	int i;	

	pg->adjList = (List*)malloc(sizeof(List)*nv);
	pg->numV = nv;
	pg->numE = 0;

	for(i=0; i<nv; i++)
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede);
	}

	pg->visitInfo= (int *)malloc(sizeof(int) * pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);

	// �켱���� ť�� �ʱ�ȭ
	PQueueInit(&(pg->pqueue), PQWeightComp);	// ����ġ �������� 
}

void GraphDestroy(ALGraph * pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph * pg, int fromV, int toV, int weight)
{
	Edge edge = {fromV, toV, weight};     // ������ ���� ����

	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;

	// ������ ������ �켱���� ť�� ����
	PEnqueue(&(pg->pqueue), edge);
}

// ConKruskalMST Helper function
void RecoverEdge(ALGraph * pg, int fromV, int toV, int weight)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}

// ���� ������ ���� �Ҹ�: ConKruskalMST Helper function
void RemoveWayEdge(ALGraph * pg, int fromV, int toV)
{
	int edge;

	if(LFirst(&(pg->adjList[fromV]), &edge))
	{
		if(edge == toV)
		{
			LRemove(&(pg->adjList[fromV]));
			return;
		}

		while(LNext(&(pg->adjList[fromV]), &edge))
		{
			if(edge == toV)
			{
				LRemove(&(pg->adjList[fromV]));
				return;
			}
		}
	}
}

// ������ �Ҹ�: ConKruskalMST Helper function
void RemoveEdge(ALGraph * pg, int fromV, int toV)	// ������ �׷����� �� ���� ���� ��� ����
{
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}
 
void ShowGraphEdgeInfo(ALGraph * pg)
{
	int i;
	int vx;

	for(i=0; i<pg->numV; i++)
	{
		printf("%d�� ����� ����: ", i);
		
		if(LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%d ", vx);
			
			while(LNext(&(pg->adjList[i]), &vx))
				printf("%d ", vx);
		}
		printf("\n");
	}
}

void ShowGraphEdgeWeightInfo(ALGraph * pg)
{
	PQueue copyPQ = pg->pqueue;
	Edge edge;

	while(!PQIsEmpty(&copyPQ))
	{
		edge = PDequeue(&copyPQ);
		printf("(%d-%d), w:%d \n", edge.v1, edge.v2, edge.weight);
	}
}

int WhoIsPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}

int PQWeightComp(Edge d1, Edge d2)	// ����ġ ���� ������������ ���� ������ ���� �Լ�
{
	return d1.weight - d2.weight;
}

int VisitVertex(ALGraph * pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;
		//printf("%c ", visitV + 65);
		return TRUE;
	}
	
	return FALSE;
}


void DFShowGraphVertex(ALGraph * pg, int startV)
{
	Stack stack;
	int visitV = startV;
	int nextV;

	StackInit(&stack);
	VisitVertex(pg, visitV);
	SPush(&stack, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE;

		if(VisitVertex(pg, nextV) == TRUE)
		{
			SPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				if(VisitVertex(pg, nextV) == TRUE)
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		
		if(visitFlag == FALSE)
		{
			if(SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = SPop(&stack);	
		}
	}

	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

// �� ������ ����Ǿ� �ִٸ� TRUE, �׷��� �ʴٸ� FALSE ��ȯ
int IsConnVertex(ALGraph * pg, int v1, int v2)
{
	Stack stack;
	int visitV = v1;
	int nextV;

	StackInit(&stack);
	VisitVertex(pg, visitV);
	SPush(&stack, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE;

		if(nextV == v2)		// ��ǥ�� ã�´ٸ� TRUE ��ȯ
		{
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);	// ��ȯ �� �ʱ�ȭ
			return TRUE;
		}

		if(VisitVertex(pg, nextV) == TRUE)	// �湮 �õ� �����ϸ�
		{
			SPush(&stack, visitV);	// �湮�� ���� �����鼭 �ش� ���� ��������
			visitV = nextV;
			visitFlag = TRUE;
		}
		else		// �湮�� �� �ִ� ���̶��
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)	// ����� �ٸ� ���� �湮
			{
				
				if(nextV == v2)
				{
					memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
					return TRUE;
				}

				if(VisitVertex(pg, nextV) == TRUE)
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		
		if(visitFlag == FALSE)
		{
			if(SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = SPop(&stack);	
		}
	}

	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE;
}


// MST ������ �� + 1 == ������ ��
// ũ�罺Į �˰��� ��� �ּ� ��� ���� Ʈ���� ����
void ConKruskalMST(ALGraph * pg)
{
	Edge recvEdge[20];    // ������ ������ ���� ����
	Edge edge;
	int eidx = 0;
	int i;

	// MST�� ������ ������ �Ʒ��� while���� �ݺ�
	while(pg->numE+1 > pg->numV-1)	// adjList 0���� �����̾��ٸ� while(pg->numE+1 > pg->numV)
	{
		edge = PDequeue(&(pg->pqueue));		// ����ġ ������ ���� ȹ��
		RemoveEdge(pg, edge.v1, edge.v2);	// �ش� ���� ����

		if(!IsConnVertex(pg, edge.v1, edge.v2))		// ���� �� �� ���� ����Ǿ��ִ��� Ȯ��
		{
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight);		// ���� ��� ���ٸ� ����
			recvEdge[eidx++] = edge;
		}
	}

	// �켱���� ť���� ������ ������ ������ ȸ��
	for(i=0; i<eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);

}