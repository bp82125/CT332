#include "stack.c"
#include <malloc.h>

int findState(State state, Stack openStack) {
	while(!emptyStack(openStack)){
		if(compareState(top(openStack)->state, state)) {
			return 1;
		}
		pop(&openStack);
	}
	return 0;
}

Node* DFS(State state) {
	Stack openDFS;
	Stack closeDFS;
	
	makeNullStack(&openDFS);
	makeNullStack(&closeDFS);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->noFunction = 0;
	
	push(root, &openDFS);
	
	while(!emptyStack(openDFS)) {
		Node* node = top(openDFS);
		pop(&openDFS);
		push(node, &closeDFS);
		
		if(goalCheck(node->state)) {
			return node;
		}
		
		for (
			int option = 1;
			option <= 6;
			++option
		) {
			State newState;
			makeNullState(&newState);
			
			if(callOperator(node->state, &newState, option)) {
				if(findState(newState, closeDFS) || findState(newState, openDFS)) {
					continue;
				}
				
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->parent = node;
				newNode->noFunction = option;
				push(newNode, &openDFS);
			}
		}
	}
	
	return NULL;
}

void printPathwayToGetGoal(Node *node) {
	Stack stackPrint;
	makeNullStack(&stackPrint);
	
	while(node->parent != NULL) {
		push(node, &stackPrint);
		node = node->parent;
	}
	
	push(node, &stackPrint);
	
	int noAction = 0;
	while(!emptyStack(stackPrint)){
		Node* currentNode = top(stackPrint);
		printf("\nAction %d: %s", noAction, actions[currentNode->noFunction]);
		printState(currentNode->state);
		pop(&stackPrint);
		noAction++;
	}
}

int main() {
	State currentState = {0, 0};
	Node *result = DFS(currentState);
	printPathwayToGetGoal(result);
	
	return 0;
}
