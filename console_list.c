/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Sergio López Fontenla LOGIN 1: sergio.lopez.fontenla@udc.es
 * AUTHOR 2: Jorge Neira Cociña LOGIN 2: jorge.neirac@udc.es
 * GROUP: 2.4
 * DATE: 09/04/2025
*/

#include "console_list.h"

/* Write your code here... */


#include <stdio.h>
#include <string.h>

/* Escribe tu código aquí... */

bool createNode(tPosL *p) {
    *p = (tPosL) malloc(sizeof(struct tNode));
    return *p != LNULL;
}

void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tPosL first(tList L) {
    return L;
}

tPosL last(tList L) {
    tPosL p = L;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

tPosL next(tPosL p, tList L) {
    return p->next;
}

tPosL previous(tPosL p, tList L) {
    tPosL pAux = L;
    if (p == L) {
        pAux = LNULL;
    } else {
        while (pAux->next != p) {
            pAux = pAux->next;
        }
    }
    return pAux;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    p->data = d;
}

bool insertItem(tItemL d, tList *L) {
    bool aux = false;
    tPosL q;
    if (!createNode(&q)) {
        // Si el nodo no se pudo crear devuelve false
        aux = true;
    } else {
        tPosL p = *L;
        q->data = d;
        q->next = LNULL;
        if (isEmptyList(*L) || strcmp(p->data.consoleId,d.consoleId) > 0) {
            // Si la lista esta vacia crea el nodo y lo añade manualmente
            q->next = *L;
            *L = q;
        } else {;
            for (p = *L; (p->next != LNULL) && strcmp(p->next->data.consoleId, d.consoleId) < 0; p = p->next) {
                //compara si es el ultimo o lo encontro
            }
            q->next = p->next;
            p->next = q;
        }
    }
    return aux;
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL q = p;
    if (p == *L) {
        *L = p->next;
    } else {
        if (p->next == LNULL) {
            // Va al ultimo elemento y lo borras
            previous(p, *L)->next = LNULL;
        } else {
            // En lugar de hallar el anterior de p, lo añadimos despues e intercambiamos informacion entre ellos para poder borrarlos
            p = p->next;
            q->data = p->data;
            q->next = p->next;
        }
    }
    free(p);
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

tPosL findItem(tConsoleId c, tList L) {
    tPosL p;

    if (isEmptyList(L) || strcmp(L->data.consoleId, c) > 0) {
        p = LNULL;
    } else {
        for (p = L; (p != LNULL) && strcmp(p->data.consoleId, c) < 0; p = p->next) {
        }
        if((p != LNULL) && strcmp(p->data.consoleId, c) != 0) p=LNULL ;
    }
    return p;
}
