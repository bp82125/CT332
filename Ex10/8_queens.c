#include <stdio.h>

#define MAX_QUEEN 8

typedef struct Board{
	int grid[MAX_QUEEN][MAX_QUEEN];
}Board;

void init_board(Board *board){
	for(int i = 0; i < MAX_QUEEN; ++i){
		for(int j = 0; j < MAX_QUEEN; ++j){
			board->grid[i][j] = 0;
		}
	}
}

void print_board(Board board){
	for(int i = 0; i < MAX_QUEEN; ++i){
		for(int j = 0; j < MAX_QUEEN; ++j){
			if(board.grid[i][j] == 1){
				printf("[W]");
			}else{
				printf("[ ]");
			}
		}
		printf("\n");
	}
}

int check_conflict(Board board, int row, int col){
	for (int i = 0; i < col; i++) {
		if(board.grid[row][i]) {
			return 1;
		}
	}

	//Lower left
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board.grid[i][j]) {
			return 1;
		}
	}
	
	//Upper left
	for (int i = row, j = col; i < MAX_QUEEN && j >= 0; i++, j--) {
		if (board.grid[i][j]) {
			return 1;
		}
	}
	
	return 0;
}

int solve(Board *board, int col){
	if(col >= MAX_QUEEN){
		return 1;
	}
	
	for(int row = 0; row < MAX_QUEEN; ++row){
		if(!check_conflict(*board, row, col)){
			board->grid[row][col] = 1;
			if(solve(board, col + 1)) {
				return 1; // Solution found
				
			}
			board->grid[row][col] = 0; //Backtracking
		}
	}
	return 0;
}

int main(){
	Board chessBoard;
	init_board(&chessBoard);
	
	if(solve(&chessBoard, 0)){
		printf("Solution found:\n");
		print_board(chessBoard);
	}else{
		printf("Can't solve");
	}
	return 0;
}
