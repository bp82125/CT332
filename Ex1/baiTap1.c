#include "state.c"

int main() {
	State currentState = {5, 4};
	State result;
	
	printf("Trang thai bat dau: ");
	printState(currentState);
	
	for (
		int option = 1;
		option <= 6;
		option++
	) {
		int action = callOperator(currentState, &result, option);
		if(action) {
			printf("\nHanh dong %s thanh cong", actions[option]);
			printState(result);
		} else {
			printf("\nHanh dong %s KHONG thanh cong", actions[option]);
		}
	}
	
	return 0;
}
