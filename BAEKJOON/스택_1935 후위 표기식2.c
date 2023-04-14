#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct _node {
	double data;
	struct _node* next;
} Node;

typedef struct stack {
	Node* head;
} Stack;

void SPush(Stack* pstack, double data);
double SPop(Stack* pstack);
void StackInit(Stack* pstack);

int main() {
	int N, alpha[27], index = 0, l;
	Stack stack;
	char val[100], tok;
	double op1, op2, result;
	scanf("%d", &N);
	scanf("%s", val);
	for (int i = 0; i < N; i++)
		scanf("%d", &alpha[i]);
	l = strlen(val);
	StackInit(&stack);
	for (int i = 0; i < l; i++) {
		tok = val[i];
		if (tok >= 'A' && tok < 'A' + N)
			SPush(&stack, (double)alpha[tok-'A']);
		else {
			op2 = SPop(&stack);
			op1 = SPop(&stack);

			if (tok == '+')
				SPush(&stack, op1 + op2);
			else if (tok == '-')
				SPush(&stack, op1 - op2);
			else if (tok == '*')
				SPush(&stack, op1 * op2);
			else if (tok == '/')
				SPush(&stack, op1 / op2);
		}
	}
	printf("%.2lf", SPop(&stack));
	return 0;
}

void StackInit(Stack* pstack)
{
	pstack->head = NULL;
}

void SPush(Stack* pstack, double data) {
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = pstack->head;
	pstack->head = newNode;

}

double SPop(Stack* pstack) {
	double rdata;
	Node* rnode;

	if (pstack->head == NULL) {
		exit(-1);
	}
	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);

	return rdata;
}
