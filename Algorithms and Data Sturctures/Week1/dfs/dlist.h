#ifndef DLIST_H
#define DLIST_H

#include <bits/stdc++.h>

struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
};

struct Dlist{
	Node* root1;
	Node* root2;
	int size;
};

Dlist* DlistCreateNew();
void DlistAddAtBack(Dlist* current, int val);
void DlistAddAtFront(Dlist* current, int val);
void DlistPrintForward(Dlist* current);
void DlistPrintReverse(Dlist* current);
#endif