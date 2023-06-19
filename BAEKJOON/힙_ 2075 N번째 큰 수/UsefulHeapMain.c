#include <stdio.h>
#include "UsefulHeap.h"
#pragma warning(disable:4996)

int DataPriorityComp(int ch1, int ch2)
{
	//return ch2-ch1;	// 낮은 수가 위로 오도록
	return ch1-ch2;	// 높은 수가 위로 오도록
}

int main(void)
{
	Heap heap;
	int N, X, a, result = 0;
	HeapInit(&heap, DataPriorityComp);
	scanf("%d", &N);
	for (int i = 0; i < N*N; i++) {
		scanf("%d", &a);
		HInsert(&heap, a);
	}

	while (!HIsEmpty(&heap)) {
		result++;
		X = HDelete(&heap);
		if(result == N) {
			printf("%d", X);
			break;
		}
	}

	return 0;
}