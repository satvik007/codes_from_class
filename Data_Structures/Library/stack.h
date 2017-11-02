#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include "queue.h"

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

#endif