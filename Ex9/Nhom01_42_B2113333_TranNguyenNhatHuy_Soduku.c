#define MAX_LENGTH 500

typedef struct Coord{
	int x, y;
}Coord;

typedef struct ListCoord{
	Coord data[MAX_LENGTH];
	int size;
}ListCoord;

void initListCoord(ListCoord *list){
	list->size = 0;
}

void appendListCoord(ListCoord *list, Coord coord){
	list->data[list->size++] = coord;
}

#define NB_ROWS 9
#define NB_COLUMNS 9

typedef struct Constrains{
	int data[NB_ROWS * NB_COLUMNS][NB_ROWS * NB_COLUMNS];
	int n;
}Constrains;

void initConstrains(Constrains *constrains){
	for(int i = 0; i < NB_ROWS * NB_COLUMNS;++i){
		for(int j = 0; j < NB_ROWS * NB_COLUMNS;++j){
			constrains->data[i][j] = 0;
		}
	}
	constrains->n = NB_ROWS * NB_COLUMNS;
}

int indexOf(Coord coord){
	return (NB_ROWS*coord.x + coord.y);
}

Coord positionOfVertex(int vertex){
	Coord coord;
	coord.x = vertex / NB_ROWS;
	coord.y = vertex % NB_COLUMNS;
	return coord;
}

int addConstrain(
	Constrains* constrains,
	Coord source, 
	Coord target
){
	int u = indexOf(source);
	int v = indexOf(target);
	
	if(constrains->data[u][v] == 0){
		constrains->data[u][v] = 1;
		constrains->data[v][u] = 1;
		return 1;
	}
	return 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord){
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	
	for(int i = 0; i < constrains.n; ++i){
		if(constrains.data[v][i] == 1){
			appendListCoord(&result, positionOfVertex(i));
		}
	}
	return result;
}

#include <stdio.h>
#include <limits.h>

#define MAX_VALUE 10
#define EMPTY 0
#define AREA_SQUARE_SIZE 3
#define INF INT_MAX

typedef struct Sudoku{
	int cells[NB_ROWS][NB_COLUMNS];
	Constrains constrains;
}Sudoku;

void initSudoku(Sudoku *sudoku){
	for(int i = 0; i < NB_ROWS;++i){
		for(int j = 0; j < NB_COLUMNS;++j){
			sudoku->cells[i][j] = EMPTY;
		}
	}
	initConstrains(&sudoku->constrains);
}

void initSudokuWithValues(Sudoku *sudoku, int inputs[NB_ROWS][NB_COLUMNS]){
	for(int i = 0; i < NB_ROWS;++i){
		for(int j = 0; j < NB_COLUMNS;++j){
			sudoku->cells[i][j] = inputs[i][j];
		}
	}
	initConstrains(&sudoku->constrains);
}

void printSudoku(Sudoku sudoku){
	printf("Sudoku:\n");
	for(int i = 0; i < NB_ROWS;++i){
		if(i % AREA_SQUARE_SIZE == 0){
			printf("-------------------------\n");
		}
		for(int j = 0; j < NB_COLUMNS; ++j){
			if(j % AREA_SQUARE_SIZE == 0){
				printf("| ");
			}
			printf("%d ", sudoku.cells[i][j]);
		}
		printf("|\n");
	}
	printf("-------------------------\n");
}

int isFilledSudoku(Sudoku sudoku){
	for(int i = 0; i < NB_ROWS; ++i){
		for(int j = 0; j < NB_COLUMNS; ++j){
			if(sudoku.cells[i][j] == EMPTY){
				return 0;
			}
		}
	}
	return 1;
}

void spreadConstrainsFrom(Coord position, Constrains* constrains, ListCoord *changeds){
	int row = position.x;
	int column = position.y;
	
	for(int i = 0; i < NB_ROWS; ++i){
		if(i != row){
			Coord pos = {i, column};
			if(addConstrain(constrains, position, pos)){
				appendListCoord(changeds, pos);
			}
		}
	}
	
	for(int i = 0; i < NB_COLUMNS; ++i){
		if(i != column){
			Coord pos = {row, i};
			if(addConstrain(constrains, position, pos)){
				appendListCoord(changeds, pos);
			}
		}
	}
	
	for(int i = 0; i < AREA_SQUARE_SIZE; ++i){
		for(int j = 0; j < AREA_SQUARE_SIZE; ++j){
			int areaX = (row / AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
			int areaY = (column / AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
			
			if(areaX + i != row || areaY + j != column){
				Coord pos = {areaX + i, areaY + j};
				if(addConstrain(constrains, position, pos)){
					appendListCoord(changeds, pos);
				}
			}
		}
	}
}

typedef struct List{
	int elements[MAX_LENGTH];
	int size;
}List;

void initList(List *list){
	list->size = 0;
}

int emptyList(List list){
	return list.size <= 0;
}

int fullList(List list){
	return list.size >= MAX_LENGTH;
}

int elementAt(List list, int position){
	if(position <= 0 || position > MAX_LENGTH){
		printf("Index of out bound!\n");
		return INF;
	}
	return list.elements[position - 1];
}

void appendList(int node, int position, List *list){
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

void pushBack(List *list, int node){
	appendList(node, list->size + 1, list);
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

List getAvailableValues(Coord position, Sudoku sudoku){
	ListCoord posList = getConstrains(sudoku.constrains, position);
	int available[MAX_VALUE];
	
	for(int i = 1; i < MAX_VALUE; ++i){
		available[i] = 1;
	}
	
	for(int i = 0; i < posList.size; ++i){
		Coord pos = posList.data[i];
		if(sudoku.cells[pos.x][pos.y] != EMPTY){
			available[sudoku.cells[pos.x][pos.y]] = 0;
		}
	}
	
	List result;
	initList(&result);
	
	for(int i = 1; i < MAX_VALUE; ++i){
		if(available[i]){
			pushBack(&result, i);
		}
	}
	return result;
}

//Coord getNextEmptyCell(Sudoku sudoku){
//	for(int i = 0; i < NB_ROWS; ++i){
//		for(int j = 0; j < NB_COLUMNS; ++j){
//			Coord pos = {i, j};
//			if(sudoku.cells[i][j] == EMPTY){
//				return pos;
//			}
//		}
//	}
//}

Coord getNextMinDomainCell(Sudoku sudoku){
	int minLength = INF;
	Coord result;
	
	for(int i = 0; i < NB_ROWS; ++i){
		for(int j = 0; j < NB_COLUMNS; ++j){
			if(sudoku.cells[i][j] == EMPTY){
				Coord pos = {i, j};
				int availableLength = getAvailableValues(pos, sudoku).size;
				if(availableLength < minLength){
					minLength = availableLength;
					result = pos;
				}
			}
		}
	}
	return result;
}

int exploredCounter = 0;
int sudokuBackTracking(Sudoku* sudoku){
	if(isFilledSudoku(*sudoku)){
		return 1;
	}
	
	Coord position = getNextMinDomainCell(*sudoku);
	List avaliables = getAvailableValues(position, *sudoku);
	
	if(avaliables.size == 0){
		return 0;
	}
	
	for(int j = 0; j < avaliables.size; ++j){
		int value = avaliables.elements[j];
		sudoku->cells[position.x][position.y] = value;
		exploredCounter++;
		if(sudokuBackTracking(sudoku)){
			return 1;
		}
		sudoku->cells[position.x][position.y] = EMPTY;
	}
	return 0;
}

Sudoku solveSudoku(Sudoku sudoku){
	initConstrains(&sudoku.constrains);
	for(int i = 0; i < NB_ROWS; ++i){
		for(int j = 0; j < NB_COLUMNS; ++j){
			ListCoord history;
			initListCoord(&history);
			Coord pos = {i, j};
			spreadConstrainsFrom(pos, &sudoku.constrains, &history);
		}
	}
	exploredCounter = 0;
	if(sudokuBackTracking(&sudoku)){
		printf("Solved\n");
	}else{
		printf("Can not solve\n");
	}
	printf("Explored %d states\n", exploredCounter);
	return sudoku;
}

int inputs1[9][9] = {
	{0,6,1,0,0,7,0,0,3},
	{0,9,2,0,0,3,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,8,5,3,0,0,0,0},
	{0,0,0,0,0,0,5,0,4},
	{5,0,0,0,0,8,0,0,0},
	{0,4,0,0,0,0,0,0,1},
	{0,0,0,1,6,0,8,0,0},
	{6,0,0,0,0,0,0,0,0},
};

int main(){
	Sudoku sudoku;
	initSudokuWithValues(&sudoku, inputs1);
	printSudoku(sudoku);
	
	Sudoku result = solveSudoku(sudoku);
	printSudoku(result);
	
	return 0;
}



