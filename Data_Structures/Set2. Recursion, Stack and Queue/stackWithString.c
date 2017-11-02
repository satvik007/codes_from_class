// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node is the element of the stack
struct Node{
	struct Node* next; // Pointer to the next element in stack
	char name[30]; // data in the node
};

struct Stack{
	struct Node* top; // The top element of the stack
	int size; // Size of the stack
};

typedef struct Stack* stack; // typedef for shortening the name to a more convenient one.

stack createStack(); // manually allocates a new stack struct
void stackPush(stack* stk, char* x); // Push a new element on top of the stack
char* stackPop(stack* stk); // Popping an element from top of the stack
int stackIsEmpty(stack stk); // Checking if stack is empty
int stackSize(stack stk); // Returns stack size
void print(stack* stk); // Prints the elements in the stack using stackPop.

int main(){
	stack stk = createStack(); // new element is created.
	while(1){
		printf("Press 0 for exiting.\nPress 1 for pushing.\nPress 2 for popping.\n\
Press 3 for printing size.\nPress 4 to check if stack is empty.\n");
		int n;
		scanf("%d", &n);
		if(n == 0) break;
		if(n == 1){
			char a[30];
			printf("Enter the string: ");
			getchar();
			scanf("%[^\n]", a);
			stackPush(&stk, a);
		}
		else if(n == 2){
			if(stk->size == 0) printf("Cannot pop stack.\n");
			else {
				stackPop(&stk);
			}
		}
		else if(n == 3) printf("The size of string is %d.\n", stackSize(stk));
		else if(n == 4){
			if(stackIsEmpty(stk)) printf("The stack is empty.\n");
			else printf("The stack is NOT empty.\n");
		}
		else printf("INVALID Input.\n");
	}
	print(&stk);
	return 0;
}

void print(stack* stk){
	while(!stackIsEmpty(*stk)){
		printf("%s\n", stackPop(stk));
	}
	return;
}
stack createStack(){
	stack new1 = (stack) malloc (sizeof(stack));
	new1->top = NULL;
	new1->size = 0;
	return new1;
}
void stackPush(stack* stk, char* x){
	struct Node* new1 = (struct Node*) malloc (sizeof(struct Node*));
	strcpy(new1->name, x);
	new1->next = (*stk)->top;
	(*stk)->top = new1;
	(*stk)->size += 1;
	return;
}
char* stackPop(stack* stk){
	static char b[30]; // Because returning outside of the function
	strcpy(b, "NULL");
	if((*stk)->size == 0){
		printf("The stack is empty. Cannot pop!\n");
	}
	else {
		struct Node* temp = (*stk)->top;
		strcpy(b, temp->name);
		(*stk)->top = (*stk)->top->next;
		(*stk)->size -= 1;
		free(temp);
	}
	return b;
}

int stackIsEmpty(stack stk){
	if(stk->size == 0) return 1;
	else return 0;
}
int stackSize(stack stk){
	return stk->size;
}