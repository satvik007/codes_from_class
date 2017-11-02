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
    int flag = 0; // flag to make sure we are detecting the front and exiting the loop correctly.
    // iteratively printing the next element in the linked list.
    while(current != root || flag == 0){
        flag = 1;
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Simply returns if the element is present in the list or not.
int search(struct Node* root, int val){
    struct Node *current = root;
    int flag = 0; // flag for front detection of the circular linked list to prevent cycling.
    while(current != root || flag == 0){
        flag = 1;
        if(current->data == val) return 1;
        current = current->next;
    }
    return 0;
}

int main(){
    printf("Input n: ");
    int n;
    scanf("%d", &n);
    struct Node* root = (struct Node* ) malloc (sizeof(struct Node));// dynamically creating the root of the linked list first.
    int i = 0;
    scanf("%d", &root->data);
    struct Node* temp = root; 
    // iteratively adding next elements to the linked list.
    for(i=1; i<n; i++){
        struct Node* current = (struct Node*) malloc (sizeof(struct Node));
        temp->next = current;
        scanf("%d", &current->data);
        temp = current;
    }
    temp->next = root;
    print(root);
    int val;
    printf("Enter value: ");
    scanf("%d", &val);
    int found = search(root, val);
    if(found == 1) printf("Found\n");
    else printf("Not found\n");
    return 0;
}
