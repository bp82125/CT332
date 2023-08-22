#include <stdio.h>
#include <malloc.h>

typedef enum{UP, DOWN} GlassState;

#define MAX_GLASSES 6
#define MOVING_GLASSES 3
#define GOAL_GLASS_STATE UP

typedef struct State{
	GlassState glasses[MAX_GLASSES];
}State;

void makeNullState(State *state){
	for(int i = 0; i < MAX_GLASSES; ++i){
		if(i % 2 == 0){
			state->glasses[i] = UP;
		}else {
			state->glasses[i] = DOWN;
		}
	}
}

void printState(State state){
	for(int i = 0; i < MAX_GLASSES; ++i){
		if(state.glasses[i] == UP){
			printf("UP  	");
		}else{
			printf("DOWN	");
		}
	}
	printf("\n");
	for(int i = 0; i < MAX_GLASSES; ++i){
		printf("%d	", i + 1);
	}
	printf("\n");
}

int goalCheck(State state){
	for(int i = 0; i < MAX_GLASSES; ++i){
		if(state.glasses[i] != GOAL_GLASS_STATE){
			return 0;
		}
	}
	return 1;
}

int compareState(State state1, State state2){
	for(int i = 0; i < MAX_GLASSES; ++i){
		if(state1.glasses[i] != state2.glasses[i]){
			return 0;
		}
	}
	return 1;
}

void flipGlass(GlassState *glass){
	*glass = (*glass == UP) ? DOWN : UP;
}

int changeState(State currentState, State *result, int startIndex){
	if(startIndex > MAX_GLASSES - MOVING_GLASSES + 1 || startIndex < 0){
		printf("Index out of bound!\n");
		return 0;
	}
	*result = currentState;
	
	for(int i = 0; i < MOVING_GLASSES; ++i){
		flipGlass(&result->glasses[startIndex + i]);
	}
	return 1;
}

int callOperator(State currentState, State *result, int startIndex){
	return changeState(currentState, result, startIndex - 1);
}

typedef struct Node{
	State state;
	struct Node* parent;
	int startIndex;
}Node;

Node* createNode(State state, Node* parent, int startIndex){
	Node* node = (Node*)malloc(sizeof(Node));
	node->state = state;
	node->parent = parent;
	node->startIndex = startIndex;
	return node;
}

#define MAXN 100 

typedef struct Stack{
	Node* elements[MAXN];
	int top_idx;
}Stack;

void makeNullStack(Stack *stack){
	stack->top_idx = MAXN;
}

int emptyStack(Stack stack){
	return stack.top_idx == MAXN;
}

int fullStack(Stack stack){
	return stack.top_idx <= 0;
}

Node* top(Stack stack){
	if(emptyStack(stack)){
		printf("Stack is empty!\n");
		return NULL;
	}
	return stack.elements[stack.top_idx];
}

void pop(Stack *stack){
	if(emptyStack(*stack)){
		printf("Stack is empty!\n");
		return;
	}
	
	stack->top_idx++;
	
}

void pushStack(Node *node, Stack *stack){
	if(fullStack(*stack)){
		printf("Stack over flow!\n");
	}else{
		stack->top_idx--;
		stack->elements[stack->top_idx] = node;
	}
}

int findState(State state, Stack openStack){
	while(!emptyStack(openStack)){
		if(compareState(top(openStack)->state, state)){
			return 1;
		}
		pop(&openStack);
	}
	return 0;
}

Node* DFS(State startState){
	Stack openDFS;
	Stack closeDFS;
	
	makeNullStack(&openDFS);
	makeNullStack(&closeDFS);
	
	Node* root = createNode(startState, NULL, 0);
	pushStack(root, &openDFS);
	
	while(!emptyStack(openDFS)){
		Node* node = top(openDFS);
		pop(&openDFS);
		pushStack(node, &closeDFS);
		
		if(goalCheck(node->state)){
			return node;
		}
		
		for(
			int startIndex = 1; 
			startIndex <= MAX_GLASSES - MOVING_GLASSES + 1; 
			++startIndex
		){
			State newState;
			makeNullState(&newState);
			
			if(callOperator(node->state, &newState, startIndex)){
				if(findState(newState, closeDFS) || findState(newState, openDFS)){
					continue;
				}
				
				Node *newNode = createNode(newState, node, startIndex);
				pushStack(newNode, &openDFS);
			}
		}
	}
	return NULL;
}

void printNode(Node *node){
	if(node->startIndex == 0){
		printf("First state ");
	}else{
		printf("Flip %d glasses ", MOVING_GLASSES);
		for(int i = 0; i < MOVING_GLASSES; ++i){
			printf("%d ", node->startIndex + i);
		}
	}
	printf("\n");
	printState(node->state);
	printf("\n");
}

void printWaysToGoal(Node *node){
	Stack stackPrint;
	makeNullStack(&stackPrint);
	
	while(node != NULL){
		pushStack(node, &stackPrint);
		node = node->parent;
	}
	
	int action = 0;
	while(!emptyStack(stackPrint)){
		printf("Action %d: ", action);
		printNode(top(stackPrint));
		pop(&stackPrint);
		action++;
	}
}

int main(){
	State initState;
	makeNullState(&initState);
	
	Node* result = DFS(initState);
	if(result == NULL){
		printf("Impossible to solve this!\n");
	}else{
		printWaysToGoal(result);	
	}
	return 0;
}
