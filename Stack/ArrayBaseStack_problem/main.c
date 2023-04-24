#include <stdio.h>
#include "ArrayBaseStack.h"
#pragma warning(disable:4996)

int main(void)
{
	// Stack�� ���� �� �ʱ�ȭ ///////
	Stack stack;
	StackInit(&stack);
	int K, n, result=0;
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d", &n);
		if (n == 0) SPop(&stack);
		else SPush(&stack, n);
	}
	// ������ ������ ///////
	while (!SIsEmpty(&stack))
		result += SPop(&stack);
	
	printf("%d", result);

	return 0;
}