#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>

using namespace std;

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

int findState(State state, queue<Node*> openStack){
	while(!openStack.empty()){
		if(compareState(openStack.front()->state, state)){
			return 1;
		}
		openStack.pop();
	}
	return 0;
}

Node* BFS(State startState){
	queue<Node*> openDFS;
	queue<Node*> closeDFS;
	
	Node* root = createNode(startState, NULL, 0);
	openDFS.push(root);
	
	while(!openDFS.empty()){
		Node* node = openDFS.front();
		openDFS.pop();
		closeDFS.push(node);
		
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
				openDFS.push(newNode);
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
	stack<Node*> stackPrint;
	
	while(node != NULL){
		stackPrint.push(node);
		node = node->parent;
	}
	
	int action = 0;
	while(!stackPrint.empty()){
		printf("Action %d: ", action);
		printNode(stackPrint.top());
		stackPrint.pop();
		action++;
	}
}

int main(){
	State initState;
	makeNullState(&initState);
	
	Node* result = BFS(initState);
	if(result == NULL){
		printf("Impossible to solve this!\n");
	}else{
		printWaysToGoal(result);	
	}
	return 0;
}
