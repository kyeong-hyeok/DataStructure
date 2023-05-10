#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#include "BinaryTree2.h"

#define TRUE	1
#define FALSE	0

// typedef int Data;
typedef BTreeNode * Data;	// 컴파일은 되지만 저장되는 데이터형이 달라 infixToPostfix.c는 int형으로 해야함 -> 다른 stack.h를 include 받기 (분리해주기)

typedef struct _node
{
	Data data;
	struct _node * next;
} Node;

typedef struct _listStack
{
	Node * head;
} ListStack;


typedef ListStack Stack;

void StackInit(Stack * pstack);
int SIsEmpty(Stack * pstack);

void SPush(Stack * pstack, Data data);
Data SPop(Stack * pstack);
Data SPeek(Stack * pstack);

#endif