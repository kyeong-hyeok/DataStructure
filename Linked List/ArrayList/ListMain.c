#include <stdio.h>
#include "ArrayList.h"

int main(void)
{
	/*** ArrayList의 생성 및 초기화 ***/
	List list;
	char data;
	ListInit(&list);

	/*** 10개의 데이터 저장 ***/
	LInsert(&list, 'a');  LInsert(&list, 'b');
	LInsert(&list, 'c');  LInsert(&list, 'd');
	LInsert(&list, 'e');  LInsert(&list, 'f'); 
	LInsert(&list, 'g');  LInsert(&list, 'h');  
	LInsert(&list, 'i');  LInsert(&list, 'j');

	/*** 저장된 데이터의 전체 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if(LFirst(&list, &data))    // 첫 번째 데이터 조회
	{
		printf("%c ", data);
		
		while(LNext(&list, &data))    // 두 번째 이후의 데이터 조회
			printf("%c ", data);
	}
	printf("\n\n");

	/*** 'e'를 탐색하여 모두 삭제 ***/
	if(LFirst(&list, &data))
	{
		if(data == 'e')
			LRemove(&list);
		
		while(LNext(&list, &data))
		{
			if(data == 'e')
				LRemove(&list);
		}
	}

	/*** 삭제 후 저장된 데이터 전체 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%c ", data);

		while (LNext(&list, &data))
			printf("%c ", data);
	}
	printf("\n\n");

	/*** 'c'를 탐색하여 모두 삭제 ***/
	if (LFirst(&list, &data))
	{
		if (data == 'c')
			LRemove(&list);

		while (LNext(&list, &data))
		{
			if (data == 'c')
				LRemove(&list);
		}
	}

	/*** 삭제 후 저장된 데이터 전체 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if(LFirst(&list, &data))
	{
		printf("%c ", data);
		
		while(LNext(&list, &data))
			printf("%c ", data);
	}
	printf("\n\n");
	return 0;
}