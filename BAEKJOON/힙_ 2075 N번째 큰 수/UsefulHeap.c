#include "UsefulHeap.h"

void HeapInit(Heap * ph, PriorityComp pc)
{
	ph->numOfData = 0;
	ph->comp = pc;	// ���� �켱���� �Ǵ� ����
}

int HIsEmpty(Heap * ph)
{
	if(ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;
}

int GetParentIDX(int idx) 
{ 
	return idx/2; 
}

int GetLChildIDX(int idx) 
{ 
	return idx*2; 
}

int GetRChildIDX(int idx) 
{ 
	return GetLChildIDX(idx)+1; 
}

int GetHiPriChildIDX(Heap * ph, int idx)	// �켱 ���� ���� �ڽ��� �ε��� �� ��ȯ
{
	if(GetLChildIDX(idx) > ph->numOfData)	// �ڽ� ��尡 �������� �ʴ´ٸ�
		return 0;

	else if(GetLChildIDX(idx) == ph->numOfData)		// �ڽ� ��尡 �ϳ��� �����Ѵٸ�
		return GetLChildIDX(idx);

	else		// �ڽ� ��尡 �� �� �����Ѵٸ�
	{
	//	if(ph->heapArr[GetLChildIDX(idx)].pr > ph->heapArr[GetRChildIDX(idx)].pr)	// ������ �ڽ� �켱������ ���ٸ�
		if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0)
			return GetRChildIDX(idx);
		else
			return GetLChildIDX(idx);
	}
}

void HInsert(Heap * ph, HData data)
{
	int idx = ph->numOfData+1;		// �� ��尡 ����� �ε��� �� ����

	while(idx != 1)
	{
	//	if(pr < (ph->heapArr[GetParentIDX(idx)].pr))	// �� ����� �켱������ ���ٸ�
		if(ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];	// �θ� ��带 �� ���� ����
			idx = GetParentIDX(idx);	// �� ��带 �� ���� �ø�
		}
		else	// �� ����� �켱������ ���� �ʴٸ�
		{
			break;
		}
	}
	
	ph->heapArr[idx] = data;
	ph->numOfData += 1;
}

HData HDelete(Heap * ph)
{
	HData retData = ph->heapArr[1];		// ������ ������ ����
	HData lastElem = ph->heapArr[ph->numOfData];	// ���� ������ ��� ����

	int parentIdx = 1;		// ��Ʈ ��尡 ��ġ�ؾ��� �ε��� �� ����
	int childIdx;

	while(childIdx = GetHiPriChildIDX(ph, parentIdx))	// ��Ʈ ����� �켱������ ���� �ڽ� ��带 ����
	{
	//	if(lastElem.pr <= ph->heapArr[childIdx].pr)		// ������ ����� �켱������ �� ���ٸ�
		if(ph->comp(lastElem, ph->heapArr[childIdx]) >= 0)
			break;
		
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];		// �� ��� ��� ��ġ �� ���� �ø�
		parentIdx = childIdx;	// ������ ��尡 ����� ��ġ������ �� ���� ����
	}

	ph->heapArr[parentIdx] = lastElem;	// ������ ��� ���� ����
	ph->numOfData -= 1;
	return retData;
}
