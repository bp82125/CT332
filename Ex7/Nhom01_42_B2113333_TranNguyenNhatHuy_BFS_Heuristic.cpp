#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define ROWS 3
#define COLS 3
#define EMPTY 0
#define MAX_OPERATOR 4
#define MAX_LENGTH 500

const char* action[] = {
	"First state",
	"Move cell EMPTY to UP",
	"Move cell EMPTY to LEFT",
	"Move cell EMPTY to DOWN",
	"Move cell EMPTY to RIGHT",
};

typedef struct State{
	int eightPuzzle[ROWS][COLS];
	int emptyRow;
	int emptyCol;
}State;

void printState(State state){
	printf("\n----------\n");
	for(int row = 0; row < ROWS; ++row){
		for(int col = 0; col < COLS; ++col){
			printf("|%d ", state.eightPuzzle[row][col]);
		}
		printf("|\n");
	}
	printf("----------\n");
}

void createInitialState(State *state){
	state->emptyCol = 1;
	state->emptyRow = 1;
	state->eightPuzzle[0][0] = 3;
	state->eightPuzzle[0][1] = 4;
	state->eightPuzzle[0][2] = 5;
	state->eightPuzzle[1][0] = 1;
	state->eightPuzzle[1][1] = 0;
	state->eightPuzzle[1][2] = 2;
	state->eightPuzzle[2][0] = 6;
	state->eightPuzzle[2][1] = 7;
	state->eightPuzzle[2][2] = 8;
}

void createGoal(State *goal){
	goal->emptyRow = 0;
	goal->emptyCol = 0;
	
	goal->eightPuzzle[0][0] = 0;
	goal->eightPuzzle[0][1] = 1;
	goal->eightPuzzle[0][2] = 2;
	goal->eightPuzzle[1][0] = 3;
	goal->eightPuzzle[1][1] = 4;
	goal->eightPuzzle[1][2] = 5;
	goal->eightPuzzle[2][0] = 6;
	goal->eightPuzzle[2][1] = 7;
	goal->eightPuzzle[2][2] = 8;
	
}

int compareStates(State state1, State state2){
	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol){
		return 0;
	}
	
	for(int row = 0; row < ROWS; ++row){
		for(int col = 0; col < COLS; ++col){
			if(state1.eightPuzzle[row][col] != state2.eightPuzzle[row][col]){
				return 0;
			}
		}
	}
	return 1;
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int goalCheck(State state, State goal){
	return compareStates(state, goal);
}

int upOperator(State state, State *result){
	*result = state;
	int currentEmptyRow = state.emptyRow;
	int currentEmptyCol = state.emptyCol;
	
	if(currentEmptyRow > 0){
		result->emptyRow = currentEmptyRow - 1;
		result->emptyCol = currentEmptyCol;
		
		result->eightPuzzle[currentEmptyRow][currentEmptyCol] = state.eightPuzzle[result->emptyRow][result->emptyCol];
		result->eightPuzzle[result->emptyRow][result->emptyCol] = EMPTY;
		
		return 1;
	}
	
	return 0;
}

int leftOperator(State state, State *result){
	*result = state;
	int currentEmptyRow = state.emptyRow;
	int currentEmptyCol = state.emptyCol;
	
	if(currentEmptyCol > 0){
		result->emptyRow = currentEmptyRow;
		result->emptyCol = currentEmptyCol - 1;
		
		result->eightPuzzle[currentEmptyRow][currentEmptyCol] = state.eightPuzzle[result->emptyRow][result->emptyCol];
		result->eightPuzzle[result->emptyRow][result->emptyCol] = EMPTY;
		
		return 1;
	}
	
	return 0;
}

int downOperator(State state, State *result){
	*result = state;
	int currentEmptyRow = state.emptyRow;
	int currentEmptyCol = state.emptyCol;
	
	if(currentEmptyRow < ROWS - 1){
		result->emptyRow = currentEmptyRow + 1;
		result->emptyCol = currentEmptyCol;
		
		result->eightPuzzle[currentEmptyRow][currentEmptyCol] = state.eightPuzzle[result->emptyRow][result->emptyCol];
		result->eightPuzzle[result->emptyRow][result->emptyCol] = EMPTY;
		
		return 1;
	}
	
	return 0;
}

int rightOperator(State state, State *result){
	*result = state;
	int currentEmptyRow = state.emptyRow;
	int currentEmptyCol = state.emptyCol;
	
	if(currentEmptyCol < COLS - 1){
		result->emptyRow = currentEmptyRow;
		result->emptyCol = currentEmptyCol + 1;
		
		result->eightPuzzle[currentEmptyRow][currentEmptyCol] = state.eightPuzzle[result->emptyRow][result->emptyCol];
		result->eightPuzzle[result->emptyRow][result->emptyCol] = EMPTY;
		
		return 1;
	}
	
	return 0;
}

int callOperators(State state, State *result, int option){
	switch (option) {
	case 1: return upOperator(state, result);
	case 2: return leftOperator(state, result);
	case 3: return downOperator(state, result);
	case 4: return rightOperator(state, result);
	default:
		printf("Error calling operators!\n");
	}
	return 0;
}

int heuristic1(State state, State goal){
	int count = 0;
	for(int row = 0; row < ROWS; ++row){
		for(int col = 0; col < COLS; ++col){
			if(state.eightPuzzle[row][col] != goal.eightPuzzle[row][col]){
				count++;
			}
		}
	}
	return count;
}

int heuristic2(State state, State goal){
	int count = 0;
	
	for(int row = 0; row < ROWS; ++row){
		for(int col = 0; col < COLS; ++col){
			if(state.eightPuzzle[row][col] != EMPTY){
				for(int row_g = 0; row_g < ROWS; ++row_g){
					for(int col_g = 0; col_g < COLS; ++col_g){
						if(state.eightPuzzle[row][col] == goal.eightPuzzle[row_g][col_g]){
							count += abs(row - row_g) + abs(col - col_g);
							col_g = COLS;
							row_g = ROWS;
						}
					}
				}
			}
		}
	}
	return count;
}

typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
	int heuristic;
}Node;

Node* findState(vector<Node*> v, State state, vector<Node*>::iterator *position) {
	vector<Node*>::iterator it = v.begin();
	if(v.size() == 0){
		return NULL;
	}
	
	while(it != v.end()){
		if(compareStates((*it)->state, state)){
			*position = it;
			return *it;
		}
		it = v.erase(it);
	}
	return NULL;
}

bool comparatorHeuristic(Node *a, Node *b){
	return a->heuristic > b->heuristic;
}

Node* best_first_search(State state, State goal){
	vector<Node*> openBFS;
	vector<Node*> closeBFS;
	
	openBFS.clear();
	closeBFS.clear();
	
	Node *root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->heuristic = heuristic1(root->state, goal);
	root->no_function = 0;
	
	openBFS.push_back(root);
	
	while(!openBFS.empty()){
		Node *node = openBFS.back();
		openBFS.pop_back();
		closeBFS.push_back(node);
		
		if(goalCheck(node->state, goal)){
			cout << "Goal!\n";
			return node;
		}
		
		for(int option = 1; option <= MAX_OPERATOR; ++option){
			State newState = node->state;
			if(callOperators(node->state, &newState, option)){
				Node *newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->parent = node;
				newNode->no_function = option;
				newNode->heuristic = heuristic1(newState, goal);
				
				vector<Node*>::iterator pos_open, pos_close;
				Node* nodeFoundOpen = findState(openBFS, newState, &pos_open);
				Node* nodeFoundClose = findState(closeBFS, newState, &pos_close);
				
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					openBFS.push_back(newNode);
				}else if(nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic){
					openBFS.erase(pos_open);
					openBFS.push_back(newNode);
				}else if(nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic){
					closeBFS.erase(pos_close);
					openBFS.push_back(newNode);
				}
			}
		}
		sort(openBFS.begin(), openBFS.end(), comparatorHeuristic);
	}
	return NULL;
}

void printWaysToGoal(Node* node){
	vector<Node*> printVector;
	
	while(node->parent != NULL){
		printVector.push_back(node);
		node = node->parent;
	}
	
	printVector.push_back(node);
	
	int no_action = 0;
	for(int i = printVector.size() - 1; i >= 0; --i){
		Node* node = printVector.at(i);
		printf("\nAction %d: %s", no_action, action[node->no_function]);
		printState(node->state);
		no_action++;
	}
}

int main(){
	State initial_state;
	createInitialState(&initial_state);
	
	State goal;
	createGoal(&goal);
	
	Node* result = best_first_search(initial_state, goal);

	printWaysToGoal(result);
	
	return 0;	
}
