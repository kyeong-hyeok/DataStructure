#include <stdio.h>
#pragma warning(disable:4996)
#include "ALGraphKruskal.h"

int main(void)
{
	ALGraph graph;
	int N, M, u, v, X, result = 0;
	scanf("%d", &N);
	GraphInit(&graph, N+1);      // A, B, C, D, E, F, G의 정점 생성
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		AddEdge(&graph, u, v, 0);
	}
	scanf("%d", &X);
	for (int i = 1; i < N + 1; i++) {
		if (i != X && IsConnVertex(&graph, X, i) == TRUE)
			result++;
	}
	printf("%d", result);
	//ConKruskalMST(&graph);
	//ShowGraphEdgeInfo(&graph);
	//ShowGraphEdgeWeightInfo(&graph);

	GraphDestroy(&graph);
	return 0;
}