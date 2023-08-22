#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

typedef struct List{
	Node* elements[MAX_LENGTH];
	int size;
}List;

void makeNullList(List *list){
	list->size = 0;
}

int emptyList(List list){
	return list.size <= 0;
}

int fullList(List list){
	return list.size >= MAX_LENGTH;
}

Node* elementAt(List list, int position){
	if(position <= 0 || position > MAX_LENGTH){
		printf("Index of out bound!\n");
		return NULL;
	}
	return list.elements[position - 1];
}

void pushList(Node *node, int position, List *list){
	if(!fullList(*list)){
		for(int q = list->size; q >= position; q--){
			list->elements[q] = list->elements[q-1];
		}
		list->elements[position-1] = node;
		list->size++;
	}else{
		printf("List is full!\n");
	}
}

void deleteList(List *list, int position){
	if(emptyList(*list)){
		printf("List is empty!\n");
		return;
	}
	
	if(position < 1 || position > list->size){
		printf("Position out of bound!\n");
		return;
	}
	
	for(int i = position - 1; i < list->size; ++i){
		list->elements[i] = list->elements[i+1];
	}
	list->size--;
}

Node* findState(List list, State state, int *position){
	for(int i = 1; i <= list.size; ++i){
		if(compareStates(elementAt(list, i)->state, state)){
			*position = i;
			return elementAt(list, i);
		}
	}
	return NULL;
}

void sortList(List *list){
	for(int i = 0; i < list->size - 1; i++){
		for(int j = i + 1; j < list->size; ++j){
			if(list->elements[i]->heuristic > list->elements[j]->heuristic){
				Node* temp = list->elements[i];
				list->elements[i] = list->elements[j];
				list->elements[j] = temp;
			}
		}
	}
}

Node* best_first_search(State state, State goal){
	List openBFS;
	List closeBFS;
	
	makeNullList(&openBFS);
	makeNullList(&closeBFS);
	
	Node *root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->heuristic = heuristic1(root->state, goal);
	root->no_function = 0;
	
	pushList(root, openBFS.size + 1, &openBFS);
	
	while(!emptyList(openBFS)){
		Node *node = elementAt(openBFS, 1);
		deleteList(&openBFS, 1);
		pushList(node, closeBFS.size + 1, &closeBFS);
		
		if(goalCheck(node->state, goal)){
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
				
				int pos_open, pos_close;
				Node* nodeFoundOpen = findState(openBFS, newState, &pos_open);
				Node* nodeFoundClose = findState(closeBFS, newState, &pos_close);
				
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					pushList(newNode, openBFS.size + 1, &openBFS);
				}else if(nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic){
					deleteList(&openBFS, pos_open);
					pushList(newNode, openBFS.size + 1, &openBFS);
				}else if(nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic){
					deleteList(&openBFS, pos_close);
					pushList(newNode, openBFS.size + 1, &openBFS);
				}
				sortList(&openBFS);
			}
		}
		
	}
	return NULL;
}

void printWaysToGoal(Node* node){
	List printList;
	makeNullList(&printList);
	
	while(node != NULL){
		pushList(node, printList.size + 1, &printList);
		node = node->parent;
	}
	
	int no_action = 0;
	for(int i = printList.size; i > 0; --i){
		Node* node = elementAt(printList, i);
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
