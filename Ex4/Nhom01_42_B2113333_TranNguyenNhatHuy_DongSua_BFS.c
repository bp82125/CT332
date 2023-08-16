#include <stdio.h>
#include <malloc.h>

#define TANK_CAPACITY_X 10
#define TANK_CAPACITY_Y 5
#define TANK_CAPACITY_Z 6
#define GOAL 8
#define EMPTY 0

#define max(a,b) (a>b) ? a : b
#define min(a,b) (a<b) ? a : b

typedef struct State {
	int x;
	int y;
	int z;
}State;

const char* actions[] = {
	"First State", 
	"Pour milk X to Y",
	"Pour milk Y to X",
	"Pour milk Y to Z",
	"Pour milk Z to Y",
	"Pour milk X to Z",
	"Pour milk Z to X"
};

void makeNullState(State *state) {
	state->x = 0;
	state->y = 0;
	state->z = 0;
}

void printState(State state) {
	printf("\n	X:%d --- Y:%d -- Z:%d", state.x, state.y, state.z);
}

int goalCheck(State state) {
	return (state.x == GOAL || state.y == GOAL || state.z == GOAL);
}

int pourWaterXY(State currentState, State *result) {
	if(currentState.x > 0 && currentState.y < TANK_CAPACITY_Y) {
		result->x = max(currentState.x - (TANK_CAPACITY_Y - currentState.y), EMPTY);
		result->y = min(currentState.x + currentState.y, TANK_CAPACITY_Y);
		result->z = currentState.z;
		return 1;
	}
	return 0;
}

int pourWaterYX(State currentState, State *result) {
	if(currentState.y > 0 && currentState.x < TANK_CAPACITY_X) {
		result->x = min(currentState.x + currentState.y, TANK_CAPACITY_X);
		result->y = max(currentState.y - (TANK_CAPACITY_X - currentState.x), EMPTY);
		result->z = currentState.z;
		return 1;
	}
	return 0;
}


int pourWaterXZ(State currentState, State *result) {
	if(currentState.x > 0 && currentState.z < TANK_CAPACITY_Z) {
		result->x = max(currentState.x - (TANK_CAPACITY_Z - currentState.z), EMPTY);
		result->y = currentState.y;
		result->z = min(currentState.x + currentState.z, TANK_CAPACITY_Z);
		return 1;
	}
	return 0;
}

int pourWaterZX(State currentState, State *result) {
	if(currentState.z > 0 && currentState.x < TANK_CAPACITY_X) {
		result->x = min(currentState.x + currentState.z, TANK_CAPACITY_X);
		result->y = currentState.y;
		result->z = max(currentState.z - (TANK_CAPACITY_X - currentState.x), EMPTY);
		return 1;
	}
	return 0;
}

int pourWaterZY(State currentState, State *result) {
	if(currentState.z > 0 && currentState.y < TANK_CAPACITY_Y) {
		result->x = currentState.x;
		result->y = min(currentState.z + currentState.y, TANK_CAPACITY_Y);
		result->z = max(currentState.z - (TANK_CAPACITY_Y - currentState.y), EMPTY);
		return 1;
	}
	return 0;
}

int pourWaterYZ(State currentState, State *result) {
	if(currentState.y > 0 && currentState.z < TANK_CAPACITY_Z) {
		result->x = currentState.x;
		result->y = max(currentState.y - (TANK_CAPACITY_Z - currentState.z), EMPTY);
		result->z = min(currentState.z + currentState.y, TANK_CAPACITY_Z);
		return 1;
	}
	return 0;
}

int callOperator(
	State currentState,
	State *result,
	int option
) {
	switch (option) {
	    case 1: return pourWaterXY(currentState, result);
	    case 2: return pourWaterYX(currentState, result);
	    case 3: return pourWaterYZ(currentState, result);
	    case 4: return pourWaterZY(currentState, result);
	    case 5: return pourWaterXZ(currentState, result);
	    case 6: return pourWaterZX(currentState, result);
		
		default: printf("Error call operator");
	}
	return 0;
}

int compareState(State u, State v) {
	return u.x == v.x && u.y == v.y && u.z == v.z;
}

typedef struct Node {
	State state;
	struct Node *parent;
	int noFunction;
}Node;

#define MAXN 100

#define MAXN 100

typedef struct Queue{
	Node* elements[MAXN];
	int front, rear;
}Queue;

void makeNullQueue(Queue *queue){
	queue->front = -1;
	queue->rear = -1;
}

int emptyQueue(Queue queue){
	return queue.front == -1;
}

int fullQueue(Queue queue) {
	return (queue.rear - queue.front + 1) % MAXN == 0;
}

Node* front(Queue queue){
	if(emptyQueue(queue)){
		printf("Queue is empty!\n");
		return NULL;
	}else{
		return queue.elements[queue.front];
	}
}

void dequeue(Queue *queue){
	if(!emptyQueue(*queue)){
		if(queue->front == queue->rear){
			makeNullQueue(queue);
		}else{
			queue->front = (queue->front+1)%MAXN;
		}
	}else{
		printf("Error on deleting!\n");
	}
}

void pushQueue(Node *node, Queue *queue){
	if(!fullQueue(*queue)){
		if(emptyQueue(*queue)){
			queue->front = 0;
		}
		queue->rear = (queue->rear + 1) % MAXN;
		queue->elements[queue->rear] = node;
	}else{
		printf("Error on pushing!\n");
	}
}

int findState(State state, Queue openQueue) {
	while(!emptyQueue(openQueue)){
		if(compareState(front(openQueue)->state, state)) {
			return 1;
		}
		dequeue(&openQueue);
	}
	return 0;
}

Node* BFS(State state) {
	Queue openBFS;
	Queue closeBFS;		
	
	makeNullQueue(&openBFS);
	makeNullQueue(&closeBFS);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->noFunction = 0;
	
	pushQueue(root, &openBFS);
	
	while(!emptyQueue(openBFS)) {
		Node* node = front(openBFS);
		dequeue(&openBFS);
		pushQueue(node, &closeBFS);
		
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
				if(findState(newState, closeBFS) || findState(newState, openBFS)) {
					continue;
				}
				
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->parent = node;
				newNode->noFunction = option;
				pushQueue(newNode, &openBFS);
			}
		}
	}
	return NULL;
}

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

void pushStack(Node *node, Stack *pS) {
	if(fullStack(*pS)){
		printf("Error! Stack is full");
	} else {
		pS->topIndex--;
		pS->elements[pS->topIndex] = node;	
	}
}

void printPathwayToGetGoal(Node *node) {
	Stack stackPrint;
	makeNullStack(&stackPrint);
	
	while(node->parent != NULL) {
		pushStack(node, &stackPrint);
		node = node->parent;
	}
	
	pushStack(node, &stackPrint);
	
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
	State currentState = {10, 0, 0};
	Node *result = BFS(currentState);
	printPathwayToGetGoal(result);
	
	return 0;
}









