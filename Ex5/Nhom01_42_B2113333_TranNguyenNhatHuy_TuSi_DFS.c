#include <stdio.h>
#include <stdlib.h>

typedef enum {A, B} BoatPosition;

#define MAX_PRIEST 3
#define MAX_DEMON 3

const char* actions[] = {
	"First state",
	"Move one priest",
	"Move one demon",
	"Move two priests",
	"Move two demons",
	"Move one priest and one demon"
};

typedef struct State{
	int numberOfPriest;
	int numberOfDemon;
	BoatPosition boatPosition;
}State;

void makeNullState(State *state) {
	state->numberOfPriest = MAX_PRIEST;
	state->numberOfDemon = MAX_DEMON;
	state->boatPosition = A;
}

void printState(State state){
	for(int i = 0; i < state.numberOfPriest; ++i){
		printf("P ");
	}
	for(int i = 0; i < MAX_PRIEST - state.numberOfPriest; ++i){
		printf("  ");
	}
	printf("|");
	for(int i = 0; i < state.numberOfDemon; ++i){
		printf("D ");
	}
	for(int i = 0; i < MAX_DEMON - state.numberOfDemon; ++i){
		printf("  ");
	}
	printf("|-");
	if(state.boatPosition == A){
		printf("B");	
	}else{
		printf("-");
	}
	printf("--------------------");
	if(state.boatPosition == B){
		printf("B");	
	}else{
		printf("-");
	}
	printf("-|  ");
	for(int i = 0; i < MAX_PRIEST - state.numberOfPriest; ++i){
		printf("P ");
	}
	for(int i = 0; i < state.numberOfPriest; ++i){
		printf("  ");
	}
	printf("|");
	for(int i = 0; i < MAX_DEMON - state.numberOfDemon; ++i){
		printf("D ");
	}
	for(int i = 0; i < state.numberOfDemon; ++i){
		printf("  ");
	}
	printf("\n");
}

int goalCheck(State state){
	return state.numberOfPriest == 0 
			&& state.numberOfDemon == 0 
			&& state.boatPosition == B;
}

int checkAlive(int numberOfPriest, int numberOfDemon){
	if(numberOfPriest < 0 || numberOfPriest > MAX_PRIEST) return 0;
	if(numberOfDemon < 0 || numberOfDemon > MAX_DEMON) return 0;
	
	if(numberOfPriest < numberOfDemon && numberOfPriest > 0) return 0;
	
	return 1;
}

int checkLegalState(State state) {
	return checkAlive(state.numberOfPriest, state.numberOfDemon) && 
		   checkAlive(MAX_PRIEST - state.numberOfPriest, MAX_DEMON - state.numberOfDemon);
}

int moveOnePriest(State currentState, State *result) {
	
	if(currentState.boatPosition == A) {
		
		State temp = currentState;
		temp.numberOfPriest--;
		temp.boatPosition = B;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
		
	if(currentState.boatPosition == B) {
		State temp = currentState;
		temp.numberOfPriest++;
		temp.boatPosition = A;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	return 0;
}

int moveOneDemon(State currentState, State *result) {
	
	if(currentState.boatPosition == A) {
		
		State temp = currentState;
		temp.numberOfDemon--;
		temp.boatPosition = B;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	
	if(currentState.boatPosition == B) {
		State temp = currentState;
		temp.numberOfDemon++;
		temp.boatPosition = A;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	return 0;
}

int moveTwoPriests(State currentState, State *result) {
	
	if(currentState.boatPosition == A) {
		
		State temp = currentState;
		temp.numberOfPriest -= 2;
		temp.boatPosition = B;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	
	if(currentState.boatPosition == B) {
		State temp = currentState;
		temp.numberOfPriest += 2;
		temp.boatPosition = A;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	return 0;
}

int moveTwoDemons(State currentState, State *result) {
	
	if(currentState.boatPosition == A) {
		
		State temp = currentState;
		temp.numberOfDemon -= 2;
		temp.boatPosition = B;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	
	if(currentState.boatPosition == B) {
		State temp = currentState;
		temp.numberOfDemon += 2;
		temp.boatPosition = A;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	return 0;
}

int moveOnePriestOneDemon(State currentState, State *result) {
	if(currentState.boatPosition == A) {
		State temp = currentState;
		temp.numberOfPriest--;
		temp.numberOfDemon--;
		temp.boatPosition = B;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	
	if(currentState.boatPosition == B) {
		State temp = currentState;
		temp.numberOfPriest++;
		temp.numberOfDemon++;
		temp.boatPosition = A;
		
		if(checkLegalState(temp)){
			*result = temp;
			return 1;
		}
	}
	return 0;
}

/*
  TEST
  
  printf("A side:\n");
  for(int i = 0; i <= MAX_PRIEST; ++i){
  for(int j = 0; j <= MAX_DEMON; ++j){
  State temp = {i, j, A};
  printf("%d %d | %d %d: ", temp.numberOfPriest, temp.numberOfDemon, MAX_PRIEST - temp.numberOfPriest, MAX_DEMON - temp.numberOfDemon);
  
  State result;
  makeNullState(&result);
  int action = moveOnePriestOneDemon(temp, &result);
  if(action && checkLegalState(temp)){
  printf("Hanh dong thuc hien duoc\n");
  }else {
  printf("Hanh dong KHONG thuc hien duoc\n");
  }
  }
  }
  
 */

int callOperator(
	State currentState,
	State *result, 
	int option
) {
	switch(option) {
		case 1: return moveOnePriest(currentState, result);
		case 2: return moveOneDemon(currentState, result);
		case 3: return moveTwoPriests(currentState, result);
		case 4: return moveTwoDemons(currentState, result);
		case 5: return moveOnePriestOneDemon(currentState, result);
		
		default: printf("Error calling operator!");
			return 0;
	}
}

int compareState(State state1, State state2){
	return state1.numberOfPriest == state2.numberOfPriest &&
			state1.numberOfDemon == state2.numberOfDemon &&
			state1.boatPosition == state2.boatPosition;
}

typedef struct Node {
	State state;
	struct Node *parent;
	int noFunction;
}Node;

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
			option <= 5;
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
		printf("Action %d: %s", noAction, actions[currentNode->noFunction]);
		
		if(noAction == 0){
			printf("\n");
		}else{
			if(currentNode->state.boatPosition == A){
				printf(" from B to A\n");
			}else {
				printf(" from A to B\n");
			}	
		}
		printState(currentNode->state);
		printf("\n");
		pop(&stackPrint);
		noAction++;
	}
}

int main(){
	State currentState = {MAX_PRIEST, MAX_DEMON, A};
	Node *result = DFS(currentState);
	printPathwayToGetGoal(result);
	
	return 0;
}



