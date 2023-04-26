#include <stdio.h>
#include "ArrayList.h"
#pragma warning(disable:4996)
int main(void)
{
	/*** ArrayList의 생성 및 초기화 ***/
	List list;
	int data, n, num[1000], inx=0, a;
	ListInit(&list);
	scanf("%d", &n);
	for (int i = n; i >= 1; i--)
		LInsert(&list, i);

	while (list.numOfData != 1) {
		list.curPosition = list.numOfData - 1;
		data = LRemove(&list);
		num[inx++] = data;
		a = LRemove(&list);
		LAdd(&list, 0, a);
	}

	for (int i = 0; i < inx; i++)
		printf("%d ", num[i]);
	printf("%d", list.arr[0]);

	return 0;
}