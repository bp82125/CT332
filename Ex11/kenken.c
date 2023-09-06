#include <stdio.h>
#include <limits.h>

#define GRID_SIZE 4
#define INF INT_MAX

typedef enum Operation{
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	NONE
}Operation;

typedef struct Cell{
	int value;
	int target_value;
	Operation operation;
}Cell;

typedef struct Grid{
	Cell grid[GRID_SIZE][GRID_SIZE];
}Grid;

void print_grid(Grid G){
	printf("Kenken puzzle:");
	for(int i = 0; i < GRID_SIZE; ++i){
		printf("\n-----------------");
		printf("\n|               |\n");
		printf("|");
		for(int j = 0; j < GRID_SIZE; ++j){
			printf(" %d |", G.grid[i][j].value);
		}
		printf("\n|               |");
	}
}

void init_grid(Grid *G){
	for(int i = 0; i < GRID_SIZE; ++i){
		for(int j = 0; j < GRID_SIZE; ++j){
			G->grid[i][j] = (Cell){.value = 0, .target_value = INF, .operation = NONE};
		}
	}
}

int main(void){
	Grid G;
	init_grid(&G);
	
	G.grid[0][0] = (Cell){.value = 0, .target_value = 2, .operation = ADD};
	G.grid[0][1] = (Cell){.value = 0, .target_value = 2, .operation = ADD};
	G.grid[0][2] = (Cell){.value = 0, .target_value = 7, .operation = ADD};
	G.grid[0][3] = (Cell){.value = 0, .target_value = 4, .operation = NONE};
	
	G.grid[1][0] = (Cell){.value = 0, .target_value = 1, .operation = SUBTRACT};
	G.grid[1][1] = (Cell){.value = 0, .target_value = 3, .operation = SUBTRACT};
	G.grid[1][2] = (Cell){.value = 0, .target_value = 7, .operation = ADD};
	G.grid[1][3] = (Cell){.value = 0, .target_value = 2, .operation = SUBTRACT};
	
	G.grid[2][0] = (Cell){.value = 0, .target_value = 1, .operation = SUBTRACT};
	G.grid[2][1] = (Cell){.value = 0, .target_value = 3, .operation = SUBTRACT};
	G.grid[2][2] = (Cell){.value = 0, .target_value = 4, .operation = MULTIPLY};
	G.grid[2][3] = (Cell){.value = 0, .target_value = 2, .operation = SUBTRACT};

	G.grid[3][0] = (Cell){.value = 0, .target_value = 1, .operation = SUBTRACT};
	G.grid[3][1] = (Cell){.value = 0, .target_value = 1, .operation = SUBTRACT};
	G.grid[3][2] = (Cell){.value = 0, .target_value = 4, .operation = MULTIPLY};
	G.grid[3][3] = (Cell){.value = 0, .target_value = 4, .operation = MULTIPLY};
	
	print_grid(G);
	
	return 0;
}
