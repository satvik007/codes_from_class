#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include"arithmatic.h"
#include"stack.h"
#define LEN 101

//function to evaluate a postfix expression
int evalPost(char str[], int size)
{
	if(size<=0)
		return INT_MIN;
	else 
	{
		stack st=newStack();
		if(!st)
			return INT_MIN;
		else
		{
			int ind=0,x,y,z;
			while(ind<size)
			{
				switch(str[ind])
				{
					case '*':	x=popStack(st);
								y=popStack(st);
								z=x*y;
								pushStack(st,z);
								break;	
					case '/':	x=popStack(st);
								y=popStack(st);
								z=y/x;
								pushStack(st,z);
								break;	
					case '+':	x=popStack(st);
								y=popStack(st);
								z=x+y;
								pushStack(st,z);
								break;
					case '-':	x=popStack(st);
								y=popStack(st);
								z=y-x;
								pushStack(st,z);
								break;
					default:	if(str[ind]<='9' && str[ind]>='0')
								{
									z=0;
									while(str[ind]<='9' && str[ind]>='0')
										z=(z*10+(str[ind++]-'0'));
									pushStack(st,z);
								}
								break;
				}
				ind++;
			}
			z=popStack(st);
			delStack(&st);
			return z;
		}
	}
}

//function to evaluate a prefix expression
int evalPre(char str[], int size)
{
	if(size<=0)
		return INT_MIN;
	else 
	{
		stack st=newStack();
		if(!st)
			return INT_MIN;
		else
		{
			int ind=size-1,x,y,z;
			while(ind>=0)
			{
				switch(str[ind])
				{
					case '*':	x=popStack(st);
								y=popStack(st);
								z=x*y;
								pushStack(st,z);
								break;	
					case '/':	x=popStack(st);
								y=popStack(st);
								z=x/y;
								pushStack(st,z);
								break;	
					case '+':	x=popStack(st);
								y=popStack(st);
								z=x+y;
								pushStack(st,z);
								break;
					case '-':	x=popStack(st);
								y=popStack(st);
								z=x-y;
								pushStack(st,z);
								break;
					default:	if(str[ind]<='9' && str[ind]>='0')
								{
									z=0,x=1;
									while(str[ind]<='9' && str[ind]>='0')
									{
										z=(z+x*(str[ind--]-'0'));
										x*=10;
									}
									pushStack(st,z);
								}
								break;
				}
				ind--;
			}
			z=popStack(st);
			delStack(&st);
			return z;
		}
	}
}

//function to convert an infix expression into a post expression
int In_Post(char str[],int sizeS, char new[], int *sizeN)
{
	if(sizeS<=0)
		INT_MIN;
	else 
	{
		stack st=newStack();
		if(!st)
			return INT_MIN;
		else
		{
			int ind=0,i=0;
			pushStack(st,'(');
			while(ind<sizeS)
			{
				switch(str[ind])
				{
					case '(':	pushStack(st,'(');
								break;
					case ')':	while(topStack(st)!='(')
								{
									new[i++]=(char)popStack(st);
									new[i++]=' ';
								}
								popStack(st);
								break;
					//same operation is performed when '*' or '/' hence no 'break' in between and a common body
					case '*':		
					case '/':	while(((char)topStack(st)=='*')||((char)topStack(st)=='/'))
								{
									new[i++]=popStack(st);
									new[i++]=' ';
								}									
								pushStack(st,str[ind]);
								break;	
					//same operation is performed when '+' or '-' hence no 'break' in between and a common body	
					case '+':	
					case '-':	while(((char)topStack(st)=='+')||((char)topStack(st)=='-')||((char)topStack(st)=='*')||((char)topStack(st)=='/'))
								{
									new[i++]=popStack(st);
									new[i++]=' ';
								}									
								pushStack(st,str[ind]);
								break;
					default:	if((str[ind]<='9' && str[ind]>='0'))
								{
									while(str[ind]<='9' && str[ind]>='0')
										new[i++]=str[ind++];									
									new[i++]=' ';
								}
								break;
				}
				ind++;
			}
			while(topStack(st)!='(')
			{
				new[i++]=(char)popStack(st);
				new[i++]=' ';
			}
			delStack(&st);
			new[i++]='\0';
			*sizeN=i-1;
			return 1;
		}
	}
}

//function to convert an infix expression to a prefix expression
int In_Pre(char str[],int sizeS, char pre[], int *sizeN)
{
	if(sizeS<=0)
		INT_MIN;
	else 
	{
		stack st=newStack();
		if(!st)
			return INT_MIN;
		else
		{
			int ind=sizeS-1,i=0,j;
			char new[LEN];
			pushStack(st,')');
			while(ind>=0)
			{
				switch(str[ind])
				{
					case ')':	pushStack(st,')');
								break;
					case '(':	while(topStack(st)!=')')
								{
									new[i++]=(char)popStack(st);
									new[i++]=' ';
								}
								popStack(st);
								break;
					//same operation is performed when '*' or '/' hence no 'break' in between and a common body
					case '*':		
					case '/':	pushStack(st,str[ind]);
								break;	
					//same operation is performed when '+' or '-' hence no 'break' in between and a common body	
					case '+':	
					case '-':	while(((char)topStack(st)=='*')||((char)topStack(st)=='/'))
								{
									new[i++]=popStack(st);
									new[i++]=' ';
								}									
								pushStack(st,str[ind]);
								break;
					default:	if((str[ind]<='9' && str[ind]>='0'))
								{
									j=0;
									while(str[ind]<='9' && str[ind]>='0')
										new[i++]=str[ind--];
									new[i++]=' ';
								}
								break;
				}
				ind--;
			}
			while(topStack(st)!=')')
			{
				new[i++]=(char)popStack(st);
				new[i++]=' ';
			}
			delStack(&st);
			for(j=0;j<i;j++)
				pre[j]=new[i-j-1];
			pre[i++]='\0';
			*sizeN=i-1;
			return 1;
		}
	}
}
