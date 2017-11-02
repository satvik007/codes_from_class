// Satvik Choudhary
// 111601021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node is the element of the stack
struct Node{
    struct Node* next; // Pointer to the next element in stack
    int data; // data in the node
};

struct Stack{
    struct Node* top; // The top element of the stack
    int size; // Size of the stack
};

typedef struct Stack* stack; // typedef for shortening the name to a more convenient one.

stack createStack(); // manually allocates a new stack struct
void stackPush(stack* stk, int x); // Push a new element on top of the stack
int stackPop(stack* stk); // Popping an element from top of the stack
int stackIsEmpty(stack stk); // Checking if stack is empty
int stackSize(stack stk); // Returns stack size
void print(stack* stk); // Prints the elements in the stack using stackPop.
int stackTop(stack stk); // returns the top element of the stack.

int main(){
    stack stk = createStack(); // new element is created.
    char a[50];
    scanf("%s", a);
    int i =0;
    for(i =0; i<strlen(a); i++){
        if(a[i]>='0' && a[i] <='9') stackPush(&stk, a[i]-'0');
        else{
            int x = stackPop(&stk);
            int y = stackPop(&stk);
            if(a[i] == '+') stackPush(&stk, x+y);
            else if(a[i] == '*') stackPush(&stk, x*y);
            else if(a[i] == '-') stackPush(&stk, y-x);
        }
    }
    printf("%d\n", stackTop(stk));
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
void stackPush(stack* stk, int x){
    struct Node* new1 = (struct Node*) malloc (sizeof(struct Node*));
    new1->data = x;
    new1->next = (*stk)->top;
    (*stk)->top = new1;
    (*stk)->size += 1;
    return;
}
int stackPop(stack* stk){
    static int b; // Because returning outside of the function
    b = -1;
    if((*stk)->size == 0){
        printf("The stack is empty. Cannot pop!\n");
    }
    else {
        struct Node* temp = (*stk)->top;
        b = temp->data;
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
int stackTop(stack stk){
    return stk->top->data;
}