#include <stdio.h>
#include "ArrayList.h"

int main(void)
{
	/*** ArrayList�� ���� �� �ʱ�ȭ ***/
	List list;
	char data;
	ListInit(&list);

	/*** 10���� ������ ���� ***/
	LInsert(&list, 'a');  LInsert(&list, 'b');
	LInsert(&list, 'c');  LInsert(&list, 'd');
	LInsert(&list, 'e');  LInsert(&list, 'f'); 
	LInsert(&list, 'g');  LInsert(&list, 'h');  
	LInsert(&list, 'i');  LInsert(&list, 'j');

	/*** ����� �������� ��ü ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if(LFirst(&list, &data))    // ù ��° ������ ��ȸ
	{
		printf("%c ", data);
		
		while(LNext(&list, &data))    // �� ��° ������ ������ ��ȸ
			printf("%c ", data);
	}
	printf("\n\n");

	/*** 'e'�� Ž���Ͽ� ��� ���� ***/
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

	/*** ���� �� ����� ������ ��ü ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%c ", data);

		while (LNext(&list, &data))
			printf("%c ", data);
	}
	printf("\n\n");

	/*** 'c'�� Ž���Ͽ� ��� ���� ***/
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

	/*** ���� �� ����� ������ ��ü ��� ***/
	printf("���� �������� ��: %d \n", LCount(&list));

	if(LFirst(&list, &data))
	{
		printf("%c ", data);
		
		while(LNext(&list, &data))
			printf("%c ", data);
	}
	printf("\n\n");
	return 0;
}