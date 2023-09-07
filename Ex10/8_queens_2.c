#include <stdio.h>

#define MAX_QUEENS 8

typedef struct Coordinate{
	int row, col;
}Coordinate;

typedef struct Board{
	int grid[MAX_QUEENS][MAX_QUEENS];
	int constraints[MAX_QUEENS][MAX_QUEENS];
	Coordinate placed_queens[MAX_QUEENS];
	int number_of_queens;
}Board;

void spread_constraints(Board *board, Coordinate coord){
	for (int col = coord.col; col < MAX_QUEENS; col++) {
		board->constraints[coord.row][col] = 1;
	}
	
	for (int row = coord.row, col = coord.col; row < MAX_QUEENS && col < MAX_QUEENS; row++, col++) {
		board->constraints[row][col] = 1;
	}
	
	for (int row = coord.row, col = coord.col; row >= 0 && col < MAX_QUEENS; row--, col++) {
		board->constraints[row][col] = 1;
	}
}

void reset_constraints(Board *board){
	for(int i = 0; i < MAX_QUEENS; ++i){
		for(int j = 0; j < MAX_QUEENS; ++j){
			board->constraints[i][j] = 0;
		}
	}
	
	for(int i = 0; i < board->number_of_queens; ++i){
		spread_constraints(board, board->placed_queens[i]);
	}
}

void init_board(Board *board){
	for(int i = 0; i < MAX_QUEENS; ++i){
		for(int j = 0; j < MAX_QUEENS; ++j){
			board->grid[i][j] = 0;
		}
	}
	
	board->number_of_queens = 0;
	
	reset_constraints(board);
}

void print_board(Board *board){
	for(int i = 0; i < MAX_QUEENS; ++i){
		for(int j = 0; j < MAX_QUEENS; ++j){
			if(board->grid[i][j] == 1){
				printf("W ");
			}else{
				printf("0 ");
			}
		}
		printf("\n");
	}
}

void print_constraints(Board *board){
	for(int i = 0; i < MAX_QUEENS; ++i){
		for(int j = 0; j < MAX_QUEENS; ++j){
			printf("%d ", board->constraints[i][j]);
		}
		printf("\n");
	}
}

int check_conflict(Board *board, Coordinate coord){
	return board->constraints[coord.row][coord.col];
}

int place_queen(Board *board, Coordinate coord){
	if(check_conflict(board, coord)){
		return 0;
	}
	
	board->placed_queens[board->number_of_queens] = coord;
	board->number_of_queens++;
	board->grid[coord.row][coord.col] = 1;
	spread_constraints(board, coord);
	
	return 1;
}

void remove_queen(Board *board, Coordinate coord){
	board->number_of_queens--;
	board->grid[coord.row][coord.col] = 0;
	reset_constraints(board);
}

void print_debug_board(Board *board){ //DEBUG
	printf("Current board:\n");
	print_board(board);
	
	printf("\nConstraints board:\n");
	print_constraints(board);
	
	printf("\nNumber of placed queen: %d\n", board->number_of_queens);
	printf("Coordinate of all placed queens:\n");
	for(int i = 0; i < board->number_of_queens; ++i){
		printf("(%d, %d) ", board->placed_queens[i].row, board->placed_queens[i].col);
	}
	printf("\n\n");
	
}

int solve(Board *board, int col){
	if(col >= MAX_QUEENS){
		return 1;
	}
	
	for(int row = 0; row < MAX_QUEENS; ++row){
		Coordinate current_coord = (Coordinate){row, col};
		
		if(place_queen(board, current_coord)){
			if(solve(board, col + 1)){
				return 1;
			}else{
				remove_queen(board, current_coord);	
			}
		}
	}
	return 0;
}

int main(){
	Board board;
	init_board(&board);
	
	if(solve(&board, 0)){
		print_debug_board(&board);
	}else{
		printf("Cannot solve!");
	}
	
	return 0;
}
