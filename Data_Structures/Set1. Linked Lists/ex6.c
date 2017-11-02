#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// structure for better organization of data
struct Node {
    int data; // data stored in the current node.
    struct Node *next; // Pointer to next node in DLL
};

// prints the linked list
void print(struct Node *root){
    struct Node *current = root;
    int flag = 0; // for preventing cyclic traversal of the linked list.
    // iteratively going over the circular linked list and printing the current node.
    while(current != root || flag == 0){
        flag = 1;
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Merges two circular linked lists in an alternate fashion.
struct Node* merge(struct Node* root1, struct Node* root2){
    struct Node* temp1 = root1;
    struct Node* temp2 = root2;
    struct Node* current1 = root1;
    struct Node* current2 = root2;
    int flag = 0;
    // iteratively inserts the elements of the smaller linked list into the bigger list in alternate positions.
    while(temp1!=root1 || flag == 0){
        flag = 1;
        current2 = temp2->next;
        current1 = temp1->next;
        temp2->next = temp1;
        temp1->next = current2;
        temp1 = current1;
        temp2 = current2;
    }
    return root2;
}

int main(){
    printf("Input big n: ");
    int n1;
    scanf("%d", &n1);
    struct Node* root1 = (struct Node* ) malloc (sizeof(struct Node));// dynamic allocation of the root node of the bigger circular linked list.
    int i = 0;
    scanf("%d", &root1->data);
    struct Node* temp = root1; 
    // iteratively adding new elements to the linked list.
    for(i=1; i<n1; i++){
        struct Node* current = (struct Node*) malloc (sizeof(struct Node));
        temp->next = current;
        scanf("%d", &current->data);
        temp = current;
    }
    temp->next = root1; // making the list circular by making the pointer of the last element to point towards the first one.
    print(root1);

    int n2;
    printf("Input small n: ");
    scanf("%d", &n2);
    struct Node* root2 = (struct Node* ) malloc (sizeof(struct Node)); // dynamic allocation of the root node of the smaller circular linked list.
    scanf("%d", &root2->data);
    temp = root2; 
    // iteratively adding new elements to the linked list.
    for(i=1; i<n2; i++){
        struct Node* current = (struct Node*) malloc (sizeof(struct Node));
        temp->next = current;
        scanf("%d", &current->data);
        temp = current;
    }
    temp->next = root2;// makes the list circular.
    print(root2);
    if(n1 <= n2){
        printf("First one should have greater number of elements so try again.\n");
        return 0;
    }
    struct Node* root = merge(root2, root1);
    print(root);
    return 0;
}