#include <stdio.h>
#include "DBLinkedList.h"

int main(void)
{
	// 양방향 연결 리스트의 생성 및 초기화  ///////
	List list;
	int data;
	ListInit(&list);

	// 8개의 데이터 저장  ///////
	LInsert(&list, 1);  LInsert(&list, 2);
	LInsert(&list, 3);  LInsert(&list, 4);
	LInsert(&list, 5);  LInsert(&list, 6);
	LInsert(&list, 7);  LInsert(&list, 8);

	// 저장된 데이터의 조회  ///////
	if(LFirst(&list, &data))
	{
		printf("%d ", data);

		while(LNext(&list, &data)) 
			printf("%d ", data);
		
		while(LPrevious(&list, &data))
			printf("%d ", data);
		
		printf("\n\n");
	}

	// 첫 항목 제거
	if (LFirst(&list, &data))
		LRemove(&list);

	// 첫 항목을 제거하고 저장된 데이터 출력
	if (LFirst(&list, &data))
	{
		printf("첫 항목 제거 후 : ");
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	// 마지막 항목 제거
	if (LFirst(&list, &data)) {
		while (LNext(&list, &data));
		LRemove(&list);
	}

	if (LFirst(&list, &data))
	{
		printf("마지막 항목 제거 후 : ");
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	// 세 번째 항목 제거
	if (LFirst(&list, &data)) {
		for (int i = 0; i < 2; i++)
			LNext(&list, &data);
		LRemove(&list);
	}

	if (LFirst(&list, &data))
	{
		printf("세 번째 항목 제거 후 : ");
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	return 0;
}