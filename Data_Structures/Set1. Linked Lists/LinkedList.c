#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// structure for better organization of data
struct Node {
    int data; 
    struct Node *next; // Pointer to next node in DLL
};

// prints the linked list
void print(struct Node *root){
    struct Node *current = root;
    // iterative traversal of a linked list
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// inserting a node after a node with the given data value is found
void addNode(struct Node *r, int val){
    struct Node* root = r;
    while(root != NULL){
    	// if data of the current element in iterative traversal matches the required data 
    	// we insert a new node
        if(root->data == val){
            struct Node* new1 = (struct Node*) malloc (sizeof(struct Node));
            new1->data = 1000;//rand();
            new1->next = root->next;
            root->next = new1;
            return;
        }    
        root = root->next;
    }
    // If the value was not find even when the linked list reached its end.
    printf("Didn't find val\n");
    return;
}

// delete a node with the given value.
struct Node* delNode(struct Node *r, int val){
	//struct Node copy = *r;
    struct Node* root = r;
    struct Node* head = r;
    struct Node* current = root;
    int flag = 0;
    // if root is to be deleted.
    while(current->data == val){
    	struct Node* del = current;
    	root = current->next;
    	free (del);
    	current = root;
    	head = current;
    	flag = 1;
    }
    // Iteratively checking the value to be deleted.
    while(root!= NULL && root->next != NULL){
    	// checking if the required data is found in the next node.
        if(root->next->data == val){
            struct Node* temp = root->next;
            // re-establishing the linked list pointers.
            root->next = root->next->next;
            // freeing memory to prevent leaks.
            free(temp);
            flag = 1;
        }    
        else
            root = root->next;
    }
    if(flag == 0) printf("Didn't find val\n");
    return head;
}

// reversing the list with some temporary variables.
struct Node* reverseList(struct Node *root){
    struct Node*temp = root;
    struct Node* next;
    struct Node* current = NULL;
    // reversing the list by simply reversing the direction of pointers.
    while(temp!=NULL){
        next = temp->next;
        temp->next = current;
        current = temp;
        temp = next;
    }
    return current;
}

int main(){
    printf("Input n: ");
    int n;
    scanf("%d", &n);
    printf("Input %d numbers: ", n);
    // root node created dynamically
    struct Node* root = (struct Node* ) malloc (sizeof(struct Node));
    int i = 0;
    scanf("%d", &root->data);
    root->next = NULL;
    // iteratively inputting data in front of the list so that 
    //the newly entered elements becomes the root
    for(i=1; i<n; i++){
        struct Node* current = (struct Node*) malloc (sizeof(struct Node));
        scanf("%d", &current->data);
        current->next = root;
        root = current;
    }
    print(root);
    int val;
    printf("Enter val to be added: ");
    scanf("%d", &val); addNode(root, val); print(root);
    printf("Val to be del: ");
    scanf("%d", &val); root = delNode(root, val); print(root);
    root = reverseList(root); print(root);
    return 0;
}
