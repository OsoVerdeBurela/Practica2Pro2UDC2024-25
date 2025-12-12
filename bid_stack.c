/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Sergio López Fontenla LOGIN 1: sergio.lopez.fontenla@udc.es
 * AUTHOR 2: Jorge Neira Cociña LOGIN 2: jorge.neirac@udc.es
 * GROUP: 2.4
 * DATE: 09/04/2025
*/

#include "bid_stack.h"

/* Write your code here... */


void createEmptyStack(tStack *S) {
 S->top = SNULL;
}

bool isEmptyStack(tStack S) {
 return S.top == SNULL;
}

tItemS peek(tStack S) {
 return S.data[S.top];
}

bool push(tItemS d, tStack *S) {
 bool error = false;

 if (S->top != SMAX-1) {
  S->top++;
  S->data[S->top] = d;
 }else error = true;
 return error;
}

void pop(tStack *S) {
 S->top--;
}

