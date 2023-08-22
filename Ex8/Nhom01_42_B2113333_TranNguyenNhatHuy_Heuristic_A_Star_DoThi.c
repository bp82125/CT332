#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 5
#define MAX_LENGTH 500

typedef struct Vertices{
	int neightbors[MAX_VERTICES];
	int h;
}Vertices;

typedef struct Graph{
	int num_vertices;
	Vertices v[MAX_VERTICES];
}Graph;

void initGraph(Graph *G, int num_vertices){
	G->num_vertices = num_vertices;
	
	for(int i = 0; i < num_vertices; ++i){
		for(int j = 0; j < num_vertices; ++j){
			G->v[i].neightbors[j] = 0;
			G->v[i].h = 0;
		}
	}
}

const char name[] = {'A', 'B', 'C', 'D', 'G'};

typedef struct State{
	int vertex;
}State;

void printState(State state){
	printf("%c", name[state.vertex]);
}

int compareState(State state1, State state2){
	return state1.vertex == state2.vertex;
}

typedef struct Node{
	State state;
	struct Node* parent;
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

Node* findState(List list, State state, int *position){
	for(int i = 1; i <= list.size; ++i){
		if(compareState(elementAt(list, i)->state, state)){
			*position = i;
			return elementAt(list, i);
		}
	}
	return NULL;
}

int goalCheck(State state, State goal){
	return compareState(state, goal);
}

Node* A_Star(Graph graph, State state, State goal){
	List open_A_Star;
	List close_A_Star;
	
	makeNullList(&open_A_Star);
	makeNullList(&close_A_Star);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->g = 0;
	root->h = graph.v[state.vertex].h;
	root->f = root->g + root->h;
	
	pushList(root, open_A_Star.size + 1, &open_A_Star);
	
	while(!emptyList(open_A_Star)){
		
		Node* node = elementAt(open_A_Star, 1);
		deleteList(&open_A_Star, 1);
		pushList(node, close_A_Star.size + 1, &close_A_Star);
		
		if(goalCheck(node->state, goal)){
			return node;
		}
		
		for(int vertex = 0; vertex < graph.num_vertices; ++vertex){
			if(graph.v[node->state.vertex].neightbors[vertex] > 0){
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state.vertex = vertex;
				newNode->parent = node;
				newNode->g = node->g + graph.v[node->state.vertex].neightbors[vertex];
				newNode->h = graph.v[vertex].h;
				newNode->f = newNode->g + newNode->h;
				
				int pos_open, pos_close;
				Node* nodeFoundOpen = findState(open_A_Star, newNode->state, &pos_open);
				Node* nodeFoundClose = findState(close_A_Star, newNode->state, &pos_close);
				
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

void printWaysToGoal(Node *node){
	List printList;
	makeNullList(&printList);
	
	while(node->parent != NULL){
		pushList(node, printList.size + 1, &printList);
		node = node->parent;
	}
	
	pushList(node, printList.size + 1, &printList);
	
	int no_action = 0;
	for(int i = printList.size; i > 0; --i){
		printState(elementAt(printList, i)->state);
		if(i!=1){
			printf("->");
		}
		no_action++;
	}
}

int main(){
	Graph graph;
	freopen("text.txt", "r", stdin);
	initGraph(&graph, MAX_VERTICES);
	for(int i = 0; i < MAX_VERTICES; ++i){
		int temp;
		scanf("%d", &temp);
		graph.v[i].h = temp;
		for(int j = 0; j < MAX_VERTICES; ++j){
			scanf("%d", &temp);
			graph.v[i].neightbors[j] = temp;
		}
	}
	
//	for(int i = 0; i < graph.num_vertices; ++i){
//		for(int j = 0; j < graph.num_vertices; ++j){
//			printf("%d ", graph.v[i].neightbors[j]);
//		}
//		printf("\n");
//	}
	
//	for(int i = 0; i < graph.num_vertices; ++i){
//		printf("h(%c) = %d\n",name[i], graph.v[i].h);
//		printf("neightbors(%c): ", name[i]);
//		for(int j = 0; j < graph.num_vertices; ++j){
//			if(graph.v[i].neightbors[j] == 0){
//				continue;
//			}
//			printf("(%c, %c, %d) ", name[i], name[j], graph.v[i].neightbors[j]);
//		}
//		printf("\n");
//	}

//	for(int i = 0; i < graph.num_vertices; ++i){
//		for(int j = 0; j < graph.num_vertices; ++j){
//			printf("%d ", graph.v[i].neightbors[j]);
//		}
//		printf("\n");
//	}
	
	State A, G;
	A.vertex = 0;
	G.vertex = 4;
	
	Node* result = A_Star(graph, A, G);
	
	printWaysToGoal(result);
	
	return 0;

}
