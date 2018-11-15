#include <stdio.h>
#include "lexical.h"
#include "nextInputChar.h"

/* lexTester.c */

int main(int argc, char *argv[])
{

  setFile(stdin);
  while(1) {
    struct lexToken *token;

    token = nextToken();
    dumpToken(stdout, token);
    if(token->kind == LEX_TOKEN_EOF)
	{
		break;
	}    
	else if (token->kind == LEX_TOKEN_NUMBER) 
	{
		printToken(stdout, token);
	}
	else if (token->kind == LEX_TOKEN_OPERATOR) 
	{
		if (LEX_TOKEN_OPERATOR == '+') 
		{
			
		}
	}
    freeToken(token);
  }
}
