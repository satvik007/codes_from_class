#ifndef ARITHMATIC_H_
#define ARITHMATIC_H_

#define LEN 101

//function to evaluate a postfix expression
int evalPost(char str[], int size);

//function to evaluate a prefix expression
int evalPre(char str[], int size);

//function to convert an infix expression into a post expression
int In_Post(char str[],int sizeS, char new[], int *sizeN);

//function to convert an infix expression to a prefix expression
int In_Pre(char str[],int sizeS, char pre[], int *sizeN);

#endif
