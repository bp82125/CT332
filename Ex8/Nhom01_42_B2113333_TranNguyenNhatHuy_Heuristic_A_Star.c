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
	"Move cell EMPTY to DOWN",
	"Move cell EMPTY to LEFT",
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
	state->eightPuzzle[0][0] = 1;
	state->eightPuzzle[0][1] = 2;
	state->eightPuzzle[0][2] = 3;
	state->eightPuzzle[1][0] = 8;
	state->eightPuzzle[1][1] = 0;
	state->eightPuzzle[1][2] = 4;
	state->eightPuzzle[2][0] = 7;
	state->eightPuzzle[2][1] = 6;
	state->eightPuzzle[2][2] = 5;
}

void createGoal(State *goal){
	goal->emptyRow = 1;
	goal->emptyCol = 0;
	
	goal->eightPuzzle[0][0] = 2;
	goal->eightPuzzle[0][1] = 8;
	goal->eightPuzzle[0][2] = 1;
	goal->eightPuzzle[1][0] = 0;
	goal->eightPuzzle[1][1] = 4;
	goal->eightPuzzle[1][2] = 3;
	goal->eightPuzzle[2][0] = 7;
	goal->eightPuzzle[2][1] = 6;
	goal->eightPuzzle[2][2] = 5;
	
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
	case 2: return downOperator(state, result);
	case 3: return leftOperator(state, result);
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
	int f;
	int g;
	int h;
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
			if(list->elements[i]->h > list->elements[j]->h){
				Node* temp = list->elements[i];
				list->elements[i] = list->elements[j];
				list->elements[j] = temp;
			}
		}
	}
}

Node* A_Star(State state, State goal){
	List open_A_Star;
	List close_A_Star;
	
	makeNullList(&open_A_Star);
	makeNullList(&close_A_Star);
	
	Node *root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_function = 0;
	root->g = 0;
	root->h = heuristic1(root->state, goal);
	root->f = root->g + root->h;
	
	pushList(root, open_A_Star.size + 1, &open_A_Star);
	
	while(!emptyList(open_A_Star)){
		Node *node = elementAt(open_A_Star, 1);
		deleteList(&open_A_Star, 1);
		pushList(node, close_A_Star.size + 1, &close_A_Star);
		
		if(goalCheck(node->state, goal)){
			return node;
		}
		
		for(int option = 1; option <= MAX_OPERATOR; ++option){
			State newState;
			if(callOperators(node->state, &newState, option)){
				Node *newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->parent = node;
				newNode->no_function = option;
				newNode->g = node->g + 1;
				newNode->h = heuristic1(newState, goal);
				newNode->f = newNode->g + newNode->h;
				
				int pos_open, pos_close;
				Node* nodeFoundOpen = findState(open_A_Star, newState, &pos_open);
				Node* nodeFoundClose = findState(close_A_Star, newState, &pos_close);
				
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					pushList(newNode, open_A_Star.size + 1, &open_A_Star);
				}else if(nodeFoundOpen != NULL && nodeFoundOpen->g > newNode->g){
					deleteList(&open_A_Star, pos_open);
					pushList(newNode, pos_open, &open_A_Star);
				}else if(nodeFoundClose != NULL && nodeFoundClose->g > newNode->g){
					deleteList(&close_A_Star, pos_close);
					pushList(newNode, open_A_Star.size + 1, &open_A_Star);
				}
			}
		}
		sortList(&open_A_Star);
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
	
	Node* result = A_Star(initial_state, goal);

	printWaysToGoal(result);
	
	return 0;	
}
