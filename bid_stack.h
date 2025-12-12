/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Sergio López Fontenla LOGIN 1: sergio.lopez.fontenla@udc.es
 * AUTHOR 2: Jorge Neira Cociña LOGIN 2: jorge.neirac@udc.es
 * GROUP: 2.4
 * DATE: 09/04/2025
*/
#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdbool.h>

/* Write your code here... */

#define SMAX 25
#define SNULL -1

typedef int tPosS;

typedef struct {
 tUserId bidder;
 tConsolePrice consolePrice;
}tItemS;

typedef struct {
 tItemS data[SMAX];
 tPosS top;
}tStack;


void createEmptyStack(tStack *S);
/*
    Objetivo: Inicializar una pila de pujas vacía.
    Entradas:
       S: Pila que se desea inicializar.
    Salidas: La pila vacia.
*/

bool isEmptyStack(tStack S);

/*
 Objetivo: Comprobar si la pila de pujas está vacía.
 Entradas:
    S: Pila a verificar.
 Salidas: Booleano comprobando si la lista esta vacia.
 Precondiciones:La pila debe estar correctamente inicializada.
*/

tItemS peek(tStack S);
/*
 Objetivo: Obtener el elemento que está en la cima de la pila sin eliminarlo.
 Entradas:
     S: La pila donde quieres obtener el objeto.
 Salidas: Elemento en la cima de la pila.
 Precondiciones: La pila no debe estar vacía.
*/
bool push(tItemS d, tStack *S);
/*
 Objetivo: Insertar una nueva puja en la cima de la pila.

 Entradas:
    d: Objeto a insertar.
    S: La pila donde se inserta el objeto.
 Salidas: Un booleano indocando si fue la insercion posible.
 Precondiciones: La pila debe estar correctamente inicializada.
*/
void pop(tStack *S);
/*
 Objetivo: Eliminar el elemento situado en la cima de la pila.
 Entradas:
    S: Puntero a la pila (tStack*) de la cual se elimina el tope.
 Salidas: La pila con la primera posicion eliminada.
 Precondiciones:La pila no debe estar vacía.
*/

#endif
