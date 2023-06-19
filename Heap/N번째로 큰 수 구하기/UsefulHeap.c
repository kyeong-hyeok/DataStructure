#include "UsefulHeap.h"

void HeapInit(Heap * ph, PriorityComp pc)
{
	ph->numOfData = 0;
	ph->comp = pc;	// 힙의 우선순위 판단 기준
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

int GetHiPriChildIDX(Heap * ph, int idx)	// 우선 순위 높은 자식의 인덱스 값 반환
{
	if(GetLChildIDX(idx) > ph->numOfData)	// 자식 노드가 존재하지 않는다면
		return 0;

	else if(GetLChildIDX(idx) == ph->numOfData)		// 자식 노드가 하나만 존재한다면
		return GetLChildIDX(idx);

	else		// 자식 노드가 둘 다 존재한다면
	{
	//	if(ph->heapArr[GetLChildIDX(idx)].pr > ph->heapArr[GetRChildIDX(idx)].pr)	// 오른쪽 자식 우선순위가 높다면
		if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0)
			return GetRChildIDX(idx);
		else
			return GetLChildIDX(idx);
	}
}

void HInsert(Heap * ph, HData data)
{
	int idx = ph->numOfData+1;		// 새 노드가 저장될 인덱스 값 저장

	while(idx != 1)
	{
	//	if(pr < (ph->heapArr[GetParentIDX(idx)].pr))	// 새 노드의 우선순위가 높다면
		if(ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];	// 부모 노드를 한 레벨 내림
			idx = GetParentIDX(idx);	// 새 노드를 한 레벨 올림
		}
		else	// 새 노드의 우선순위가 높지 않다면
		{
			break;
		}
	}
	
	ph->heapArr[idx] = data;
	ph->numOfData += 1;
}

HData HDelete(Heap * ph)
{
	HData retData = ph->heapArr[1];		// 삭제할 데이터 저장
	HData lastElem = ph->heapArr[ph->numOfData];	// 힙의 마지막 노드 저장

	int parentIdx = 1;		// 루트 노드가 위치해야할 인덱스 값 저장
	int childIdx;

	while(childIdx = GetHiPriChildIDX(ph, parentIdx))	// 루트 노드의 우선순위가 높은 자식 노드를 시작
	{
	//	if(lastElem.pr <= ph->heapArr[childIdx].pr)		// 마지막 노드의 우선순위가 더 높다면
		if(ph->comp(lastElem, ph->heapArr[childIdx]) >= 0)
			break;
		
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];		// 비교 대상 노드 위치 한 레벨 올림
		parentIdx = childIdx;	// 마지막 노드가 저장될 위치정보를 한 레벨 내림
	}

	ph->heapArr[parentIdx] = lastElem;	// 마지막 노드 최종 저장
	ph->numOfData -= 1;
	return retData;
}
