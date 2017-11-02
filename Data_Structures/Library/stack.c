// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <stdlib.h>

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