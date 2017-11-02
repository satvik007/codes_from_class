// Including the required libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// structure is created to better organize data
typedef struct{
    char name[100];
    int ID;
}Student;

int main(){
    int n;
    int i=0;
    scanf("%d", &n);
    // dynamically allocating array
    Student* list = (Student*) malloc (sizeof(Student)*n);
    // taking input
    for(i=0; i<n; i++){
        scanf("%s %d", list[i].name, &list[i].ID);
    }
    Student max;
    max.ID = INT_MIN;
    // finding out max
    for(i=0; i<n; i++){
        if(list[i].ID > max.ID){
            max = list[i];
        } 
    }
    //printing max
    printf("%s\n", max.name);
    return 0;
}
    
    
