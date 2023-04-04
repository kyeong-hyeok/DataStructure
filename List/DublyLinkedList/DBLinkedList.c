#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void ListInit(List * plist)
{
	plist->head = NULL;
	plist->numOfData = 0;
}

void LInsert(List * plist, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head;
	if(plist->head != NULL)
		plist->head->prev = newNode;

	newNode->prev = NULL;
	plist->head = newNode;

	(plist->numOfData)++;
}

int LFirst(List * plist, Data * pdata)
{
	if(plist->head == NULL)
		return FALSE;

	plist->cur = plist->head;
	*pdata = plist->cur->data;

	return TRUE;
}

int LNext(List * plist, Data * pdata)
{
	if(plist->cur->next == NULL)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;

	return TRUE;
}

int LPrevious(List * plist, Data * pdata)
{
	if(plist->cur->prev == NULL)
		return FALSE;

	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;

	return TRUE;
}

int LCount(List * plist)
{
	return plist->numOfData;
}

Data LRemove(List* plist) {
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->head) {		// ù ����� ��
		plist->head = rpos->next;
		rpos->next->prev = NULL;
		plist->cur = plist->head;
	}
	else if (rpos->next == NULL) {	// ������ ����� ��
		rpos->prev->next = NULL;
		plist->cur = rpos->prev;
	}
	else {							// �߰� ����� ��
		rpos->next->prev = rpos->prev;
		rpos->prev->next = rpos->next;
		plist->cur = rpos->prev;
	}

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}
