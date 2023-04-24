#include <stdio.h>
#include "ArrayBaseStack.h"
#pragma warning(disable:4996)

int main(void)
{
	// Stack의 생성 및 초기화 ///////
	Stack stack;
	StackInit(&stack);
	int K, n, result=0;
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d", &n);
		if (n == 0) SPop(&stack);
		else SPush(&stack, n);
	}
	// 데이터 꺼내기 ///////
	while (!SIsEmpty(&stack))
		result += SPop(&stack);
	
	printf("%d", result);

	return 0;
}