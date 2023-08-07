#include "node.c"

#define MAXN 100

typedef struct Stack {
	Node* elements[MAXN];
	int topIndex;
}Stack;

void makeNullStack(Stack *S) {
	S->topIndex = MAXN;
}

int emptyStack(Stack S) {
	return S.topIndex == MAXN;
}

int fullStack(Stack S) {
	return S.topIndex == 0;
}

Node* top(Stack S) {
	if(!emptyStack(S)) {
		return S.elements[S.topIndex];
	}
	return NULL;
}

void pop(Stack *pS) {
	if(!emptyStack(*pS)){
		pS->topIndex++;
	} else {
		printf("Error! Stack is empty");
	}
}

void push(Node *node, Stack *pS) {
	if(fullStack(*pS)){
		printf("Error! Stack is full");
	} else {
		pS->topIndex--;
		pS->elements[pS->topIndex] = node;	
	}
}
