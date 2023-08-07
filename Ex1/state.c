#include <stdio.h>

#define TANK_CAPACITY_X 9
#define TANK_CAPACITY_Y 4
#define EMPTY 0
#define GOAL 6

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

typedef struct State {
	int x;
	int y;
}State;

const char* actions[] = {
	"First State", 
	"pour water Full X", 
	"pour water Full Y", 
	"pour water Empty X", 
	"pour water Empty Y", 
	"pour water X to Y",
	"pour water Y to X"
};

void makeNullState(State *state) {
	state->x = 0;
	state->y = 0;
}

void printState(State state) {
	printf("\n   X:%d --- Y:%d", state.x, state.y);
}

int goalCheck(State state) {
	return (state.x == GOAL || state.y == GOAL);
}


int pourWaterFullX(State currentState, State *result) {
	if(currentState.x < TANK_CAPACITY_X) {
		result->x = TANK_CAPACITY_X;
		result->y = currentState.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State currentState, State *result) {
	if(currentState.y < TANK_CAPACITY_Y) {
		result->x = currentState.x;
		result->y = TANK_CAPACITY_Y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyX(State currentState, State *result) {
	if(currentState.x > 0) {
		result->x = EMPTY;
		result->y = currentState.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State currentState, State *result) {
	if(currentState.y > 0) {
		result->x = currentState.x;
		result->y = EMPTY;
		return 1;
	}
	return 0;
}

int pourWaterXY(State currentState, State *result) {
	if(currentState.x > 0 && currentState.y < TANK_CAPACITY_Y) {
		result->x = max(currentState.x - (TANK_CAPACITY_Y - currentState.y), EMPTY);
		result->y = min(currentState.x + currentState.y, TANK_CAPACITY_Y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State currentState, State *result) {
	if(currentState.y > 0 && currentState.x < TANK_CAPACITY_X) {
		result->x = min(currentState.x + currentState.y, TANK_CAPACITY_X);
		result->y = max(currentState.y - (TANK_CAPACITY_X - currentState.x), EMPTY);
		return 1;
	}
	return 0;
}

int callOperator (
	State currentState, 
	State *result, 
	int option
) {
	switch(option) {
		case 1: return pourWaterFullX(currentState, result);
		case 2: return pourWaterFullY(currentState, result);
		case 3: return pourWaterEmptyX(currentState, result);
		case 4: return pourWaterEmptyY(currentState, result);
		case 5: return pourWaterXY(currentState, result);
		case 6: return pourWaterYX(currentState, result);
		
		default: printf("Error call operators");
		return 0;
	}
}

int compareState(State u, State v) {
	return u.x == v.x && u.y == v.y;
}
