#include <stdio.h>
#include "DBLinkedList.h"

int main(void)
{
	// ����� ���� ����Ʈ�� ���� �� �ʱ�ȭ  ///////
	List list;
	int data;
	ListInit(&list);

	// 8���� ������ ����  ///////
	LInsert(&list, 1);  LInsert(&list, 2);
	LInsert(&list, 3);  LInsert(&list, 4);
	LInsert(&list, 5);  LInsert(&list, 6);
	LInsert(&list, 7);  LInsert(&list, 8);

	// ����� �������� ��ȸ  ///////
	if(LFirst(&list, &data))
	{
		printf("%d ", data);

		while(LNext(&list, &data)) 
			printf("%d ", data);
		
		while(LPrevious(&list, &data))
			printf("%d ", data);
		
		printf("\n\n");
	}

	// ù �׸� ����
	if (LFirst(&list, &data))
		LRemove(&list);

	// ù �׸��� �����ϰ� ����� ������ ���
	if (LFirst(&list, &data))
	{
		printf("ù �׸� ���� �� : ");
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	// ������ �׸� ����
	if (LFirst(&list, &data)) {
		while (LNext(&list, &data));
		LRemove(&list);
	}

	if (LFirst(&list, &data))
	{
		printf("������ �׸� ���� �� : ");
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	// �� ��° �׸� ����
	if (LFirst(&list, &data)) {
		for (int i = 0; i < 2; i++)
			LNext(&list, &data);
		LRemove(&list);
	}

	if (LFirst(&list, &data))
	{
		printf("�� ��° �׸� ���� �� : ");
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);

		printf("\n\n");
	}

	return 0;
}