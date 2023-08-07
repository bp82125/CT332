#include "state.c"

typedef struct Node {
	State state;
	struct Node *parent;
	int noFunction;
}Node;
