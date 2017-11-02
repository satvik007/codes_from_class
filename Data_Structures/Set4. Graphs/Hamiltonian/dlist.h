#ifndef DLIST_H
#define DLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
};
typedef struct Node* Node;

struct Dlist{
	Node root1;
	Node root2;
	int size;
};
typedef struct Dlist* Dlist;

Dlist DlistCreateNew();
void DlistAddAtBack(Dlist current, int val);
void DlistAddAtFront(Dlist current, int val);
void DlistPrintForward(Dlist current);
void DlistPrintReverse(Dlist current);


#endif