// all libraries included
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// structure is created to better organize data
typedef struct{
    char name[100];
    int ID;
}Student;

// Passing by copy and then printing data within the structure.
void PrintStruc(Student current){
    printf("%s\n", current.name);
    printf("%d\n", current.ID);
}

// Passing by pointer and changing the data stored in the structure.
void srtptr(Student *current){
    char null[100] = "abc";
    strcpy(current->name, null);
    current->ID = 123;
    return;
}

int main(){
    Student stu1; // assigning the structure
    strcpy(stu1.name, "Satvik Choudhary");// assigning the data member name 
    stu1.ID = 111601021; // assigning the data member ID
    PrintStruc(stu1);
    srtptr(&stu1);
    PrintStruc(stu1);
    return 0;
}
    
    
    
