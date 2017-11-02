#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// structure for better organization of data
struct Node {
    int data; 
    struct Node *next; // Pointer to next node in DLL
    struct Node *prev; // Pointer to previous node.
};

void printReverse(struct Node* last);
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
struct Node* addNode(struct Node *r, int val, struct Node* last){
    struct Node* root = r;
    while(root != NULL){
        // if data of the current element in iterative traversal matches the required data 
        // we insert a new node
        if(root->data == val){
            struct Node* temp = root->next;
            struct Node* new1 = (struct Node*) malloc (sizeof(struct Node));
            new1->data = 1000;//rand();
            new1->next = root->next;
            new1->prev = root;
            if(temp != NULL){
                temp->prev = new1;
            }
            root->next = new1;

            if(temp == NULL){
                //*last = *new1;
                last = new1;
            }
            return last;
        }    
        root = root->next;
    }
    // If the value was not find even when the linked list reached its end.
    printf("Didn't find val\n");
    return last;
}

// delete a node with the given value.
struct Node* delNode(struct Node *r, int val, struct Node* last){
    //struct Node copy = *r;
    struct Node* back = last;
    struct Node* root = r;
    struct Node* head = r;
    struct Node* current = root;
    int flag = 0;
    // if root is to be deleted.
    while(current != NULL && current->data == val){
        struct Node* del = current;
        root = current->next;
        free (del);
        current = root;
        head = current;
        flag = 1;
        if(current != NULL)
            current->prev = NULL;
    }
    r = current;
    back = current;
    // Iteratively checking the value to be deleted.
    while(root!= NULL && root->next != NULL){
        // checking if the required data is found in the next node.
        if(root->next->data == val){
            struct Node* temp = root->next;
            // re-establishing the linked list pointers.
            root->next = root->next->next;
            if(root -> next != NULL){
                back = root->next;
                root->next->prev = root;
            }
            else {
                back = root;
            }
            // freeing memory to prevent leaks.
            free(temp);
            flag = 1;
        }    
        else{
            root = root->next;
            if(root != NULL){
                back = root;
            }
            
        }
    }
    if(back != NULL)
        *last = *back;
    if(flag == 0) printf("Didn't find val\n");
    r = head;
    return r;
}

// reversing the list with some temporary variables.
struct Node* reverseList(struct Node *root, struct Node* last){
    struct Node* temp = root;
    struct Node* next;
    struct Node* current = root;
    struct Node* prev = root;
    // reversing the list by simply reversing the direction of pointers.
    while(current!=NULL){
        temp = current;
        next = current->next;
        prev = current->prev;
        current->next = prev;
        current->prev = next;
        current = next;
    }
    root = temp;
    return root;
}

// function though not required but just checks if everything is working all right 
void printReverse (struct Node* last){
    int i = 0;
    struct Node* current = last;
    while(current != NULL && i < 10){
        printf("%d ", current->data);
        current = current->prev;
        i++;
    }
    printf("\n");
    return;
}
int main(){
    printf("In this program every input is printed twice one using forward traversal and the 2nd one is done using backward traversal.\nIt shows that the program is running perfectly.\n");
    printf("Input n: ");
    int n;
    scanf("%d", &n);
    printf("Input %d numbers: ", n);
    // root node created dynamically
    struct Node* root = (struct Node*) malloc (sizeof(struct Node));
    struct Node* last = (struct Node*) malloc (sizeof(struct Node));
    int i = 0;
    scanf("%d", &root->data);
    root->next = NULL;
    last = root;
    // iteratively inputting data in front of the list so that 
    //the newly entered elements becomes the root
    for(i=1; i<n; i++){
        struct Node* current = (struct Node*) malloc (sizeof(struct Node));
        scanf("%d", &current->data);
        if(i==1){
            last -> prev = current;
        }
        root->prev = current;
        current->next = root;
        root = current;
    }
    print(root);
    printReverse(last);
    int val;
    printf("Enter val to be added: ");
    scanf("%d", &val); last = addNode(root, val, last); print(root); printReverse(last);
    printf("Val to be del: ");
    scanf("%d", &val); root = delNode(root, val, last); print(root); 
    if(root == NULL) last = NULL; printReverse(last);
    last = root; root = reverseList(root, last); print(root); printReverse(last);
    return 0;
}
