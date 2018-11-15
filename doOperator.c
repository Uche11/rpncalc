#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);

static int op_add(struct tokenStack *stack);
static int op_sub(struct tokenStack *stack);
static int op_multi(struct tokenStack *stack);
static int op_div(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"HELP", op_help},
  {"+", op_add},
  {"-", op_sub},
  {"*", op_multi},
  {"/", op_div},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"MOD", op_mod}, 
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
	int value = 0;
	if (emptyTokenStack(s))
	{
		fprintf(stderr, "Popping an empty stack is not allowed! \n");
		exit(1);
	}
	else 
	{
		value = atoi(popTokenStack(s)->symbol);		
	}
	return value;
}

/*YOU WRITE THIS*/
static void pushInt(struct tokenStack *s, int v)
{
	struct lexToken *t;
	char ph[200];
	int i = 0;
	t = allocToken();
	t->kind = LEX_TOKEN_NUMBER;
	sprintf(ph, "%d", v);
	while(ph[i] < sizeof(ph)){
	t->symbol[i] = ph[i];
	i++;
	}
	pushTokenStack(s, t);
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}


static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_help(struct tokenStack *stack) 
{
	printf("- ( n1 n2 — diff) \n");
	printf("+ (n1 n2 - sum) \n");
	printf("* (n1 n2 — product) - push n1*n2 \n");
	printf("/ (n1 n2 — quotient) - push n1/n2 \n");
	printf("GT (n1 n2 — gt) - push 1 if n1 > n2 and 0 otherwise \n");
	printf("LT (n1 n2 — lt) - push 1 if n1 < n2 and 0 otherwise \n");
	printf("GE (n1 n2  —  ge) - push 1 if n1 >= n2 and 0 otherwise \n");
	printf("LE (n1 n2 — le) - push 1 if n1 <= n2 and 0 otherwise \n");
	printf("EQ (n1 n2 — eq) - push 1 if n1 == n2 and 0 otherwise \n");
	printf("MOD (n1 - n1 n1) - push two copies of n1 onto the stack \n");
	printf("HELP (—) - print out all commands plus a line of documentation. Note: This is made easier due to the help string in the table. \n");
	return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_sub(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return(0);
}

static int op_multi(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2*v1);
  return(0);
}

static int op_div(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 =  popInt(stack);

  if(v1 == 0)
  { 
	printf("undefined \n");
  }
  else
  {
	pushInt(stack, v2/v1);
  }
	return(0);
}

static int op_gt(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 > v2) 
  {
	  pushInt(stack, 1);
  }
  else 
  {
	  pushInt(stack, 0);
  }
  return(0);
}

static int op_lt(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 < v2) 
  {
	  pushInt(stack, 1);
  }
  else 
  {
	  pushInt(stack, 0);
  }
  return(0);
}

static int op_ge(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 >= v2) 
  {
	  pushInt(stack, 1);
  }
  else 
  {
	  pushInt(stack, 0);
  }
  return(0);
}

static int op_le(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 <= v2) 
  {
	  pushInt(stack, 1);
  }
  else 
  {
	  pushInt(stack, 0);
  }
  return(0);
}

static int op_eq(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 == v2) 
  {
	  pushInt(stack, 1);
  }
  else 
  {
	  pushInt(stack, 0);
  }
  return(0);
}

static int op_mod(struct tokenStack *stack)
{
  int v1;
  v1 = popInt(stack);
  
  pushInt(stack, v1);
  pushInt(stack, v1);
  
  return(0);
}
