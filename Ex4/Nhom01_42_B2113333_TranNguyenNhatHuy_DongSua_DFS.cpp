#include <stdio.h>
#include <malloc.h>
#include <stack>

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
	printf("	X:%d --- Y:%d -- Z:%d\n", state.x, state.y, state.z);
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

int findState(State state, std::stack<Node*> openStack) {
	while(!openStack.empty()){
		if(compareState(openStack.top()->state, state)) {
			return 1;
		}
		openStack.pop();
	}
	return 0;
}

Node* DFS(State state) {
	std::stack<Node*> openDFS;
	std::stack<Node*> closeDFS;
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->noFunction = 0;
	
	openDFS.push(root);
	
	while(!openDFS.empty()) {
		Node* node = openDFS.top();
		openDFS.pop();
		closeDFS.push(node);
		
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
				openDFS.push(newNode);
			}
		}
	}
	
	return NULL;
}

void printPathwayToGetGoal(Node *node) {
	std::stack<Node*> stackPrint;
	
	while(node != NULL) {
		stackPrint.push(node);
		node = node->parent;
	}
	
	int noAction = 0;
	
	while(!stackPrint.empty()){
		Node* currentNode = stackPrint.top();
		printf("Action %d: %s\n", noAction, actions[currentNode->noFunction]);
		printState(currentNode->state);
		stackPrint.pop();
		noAction++;
	}
}






int main() {
	State currentState = {10, 0, 0};
	Node *result = DFS(currentState);
	printPathwayToGetGoal(result);
	
	return 0;
}









