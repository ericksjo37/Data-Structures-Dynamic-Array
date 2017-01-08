/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	if (s == NULL)
		return 0;

	
	char test;		//Test character to test for the different parentheses types
	int capacity = strlen(s);		//Getting the length of the string in order to set the capacity when a new array is created
	struct DynArr *paren = newDynArr(capacity);
	struct DynArr *brack = newDynArr(capacity);
	struct DynArr *sqrBrack = newDynArr(capacity);


	while ((test = nextChar(s)) != '\0')	//Once test == \0, we've reached the end of the string
	{
		if (test == '(')
		{
			pushDynArr(paren, test);
		}
			
		else if (test == ')')
		{
			if (sizeDynArr(paren) == 0)		//If size here is 0, then there was no ( paren, so the string is not balanced, quit here and return 0
						{
							deleteDynArr(paren);
							deleteDynArr(brack);
							deleteDynArr(sqrBrack);
							return 0;
						}
						popDynArr(paren);
		}

		else if (test == '{')
		{
			pushDynArr(brack, test);
		}
			
		else if (test == '}')
		{
			if (sizeDynArr(brack) == 0)		//If size here is 0, then there was no { paren, so the string is not balanced, quit here and return 0
						{
							deleteDynArr(paren);
							deleteDynArr(brack);
							deleteDynArr(sqrBrack);
							return 0;
						}
						popDynArr(brack);
		}
			
		else if (test == '[')
		{
			pushDynArr(sqrBrack, test);
		}
			
		else if (test == ']')
		{
			if (sizeDynArr(sqrBrack) == 0)		//If size here is 0, then there was no { paren, so the string is not balanced, quit here and return 0
			{
				deleteDynArr(paren);
				deleteDynArr(brack);
				deleteDynArr(sqrBrack);
				return 0;
			}
			popDynArr(sqrBrack);
		}
		
		}

		if (isEmptyDynArr(paren) && isEmptyDynArr(brack) && isEmptyDynArr(sqrBrack))	//If all of the arrays are empty, then the string is balanced, so free the arrays, return 1
		{
			deleteDynArr(paren);
			deleteDynArr(brack);
			deleteDynArr(sqrBrack);
			return 1;
		}
		deleteDynArr(paren);		//If one or more of the strings were not empty, then the string is not balanced, so return 0
		deleteDynArr(brack);
		deleteDynArr(sqrBrack);
		return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

