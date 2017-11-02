#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "dlist.h"

Dlist DlistCreateNew(){
	Dlist new1 = (Dlist) malloc (sizeof (Dlist));
	new1->root1 = NULL;
	new1->root2 = NULL;
	new1->size = 0;
	return new1;
}

void DlistAddAtBack(Dlist current, int val){
	Node new1 = (Node) malloc (sizeof (Node));
	new1->data = val;
	current->size += 1;
	new1->next = NULL;
	new1->prev = NULL;
	if(current->root1 == NULL){
		current->root1 = new1;
		current->root2 = new1;
	}
	else{
		current->root2->next = new1;
		new1->prev = current->root2;
		current->root2 = new1;
	}
}

void DlistAddAtFront(Dlist current, int val){
	Node new1 = (Node) malloc (sizeof (Node));
	new1->data = val;
	new1->prev = NULL;
	new1->next = NULL;
	current->size += 1;
	if(current->root1 == NULL){
		current->root1 = new1;
		current->root1 = new1;
	}
	else{
		current->root1->prev = new1;
		new1->next = current->root1;
		current->root1 = new1;
	}
}

void DlistPrintForward(Dlist current){
	if(current == NULL) return;
	Node temp = current->root1;
	int flag = 1;
	while(temp != NULL && (temp != current->root1 || flag)){
		flag = 0;
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void DlistPrintReverse(Dlist current){
	if(current == NULL) return;
	Node temp = current->root2;
	int flag = 1;
	while(temp != NULL && (temp != current->root2 || flag)){
		flag = 0;
		printf("%d ", temp->data);
		temp = temp->prev;
	}
	printf("\n");
}
