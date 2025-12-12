/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Sergio López Fontenla LOGIN 1: sergio.lopez.fontenla@udc.es
 * AUTHOR 2: Jorge Neira Cociña LOGIN 2: jorge.neirac@udc.es
 * GROUP: 2.4
 * DATE: 01/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "console_list.h"

#define MAX_BUFFER 255


void strToEnum(const char *original, tConsoleBrand *copy);


void enumToStr(tConsoleBrand original, char *copy);


void new(tList *L, tConsoleId id, tUserId user, tConsoleBrand brand, tConsolePrice price);


/* {Tipo: Generadora.
    Objetivo: Añadir una consola a la lista.
    Entrada:
        L: Lista donde vamos a eliminar la posicion.
        id: Id de la consola.
        user: Vendedor de la consola.
        brand: Marca de la consola.
        price: Precio por que que se va a vender inicialmente.
    Salida: La lista sin la posicion eliminada.
    Precondicion: El precio debe ser un valor positivo.
} */


void delete(tList *L, tConsoleId id);

/* {Tipo: Destructora.
    Objetivo: Eliminar el contenido la consola que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a eliminar la consola.
        id: Id de la consola que vamos a eliminar.
    Salida: La lista con la consola eliminada.} */

void invalidateBids(tList *L);


/* {Tipo: Destructora.
    Objetivo: Eliminar las pujas si una consola tiene mas de la media.
    Entrada:
        L: Lista donde vamos a eliminar las pujas.
    Salida: La lista con las pujas eliminada.} */


void removeC(tList *L);

/* {Tipo: Destructora.
    Objetivo: Eliminar el contenido las consolas sin pujas en la lista.
    Entrada:
        L: Lista donde vamos a eliminar la consola.
    Salida: La lista con las consolas eliminada.} */

void bid(tList *L, tConsoleId id, tUserId user, tConsolePrice price);

/*{
    Tipo: Modificadora.
    Objetivo: Añadir una puja a una consola de la lista.
    Entrada:
        L: Lista donde vamos a pujar.
        id: id de la consola donde queremos pujar.
        user: Usuario que puja en la consola
        price: Precio por el que se puja
    Salida: La consola con la puja realizada.}

*/

void award(tList *L, tConsoleId id);


/* {Tipo: Destructora.
    Objetivo: Eliminar la consola y dar el ganador de la puja.
    Entrada:
        L: Lista donde vamos a eliminar la consola.
        id: Id de la consola que va a elegirse ganador.
    Salida: La lista con la posicion eliminada.} */


void stats(tList L);


/* {Tipo: Observadora.
    Objetivo: Mostrar los elementos de la lista, el numero de cada marca la suma de precios y la media.
    Entrada:
        L: Lista de donde vamos a obtener la informacion.
    Salida: Informacion de la lista.
    Precondicion: La posicion debe de ser valida.
    Postcondicion: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.} */


void processCommand(tList *L, char *commandNumber, char command, char *param1, char *param2, char *param3,
                    char *param4) {
    printf("********************\n");

    tConsoleBrand brand;
    tConsolePrice price;


    switch (command) {
        case 'N':
            printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, param1, param2,
                   param3, param4);
            price = atof(param4);
            strToEnum(param3, &brand);
            new(L, param1, param2, brand, price);
            break;
        case 'D':
            printf("%s %c: console %s\n", commandNumber, command, param1);
            delete(L, param1);
            break;
        case 'B':
            printf("%s %c: console %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);

            price = atof(param3);
            bid(L, param1, param2, price);
            break;
        case 'A':
            printf("%s %c: console %s\n", commandNumber, command, param1);
            award(L, param1);
            break;
        case 'R':
            printf("%s %c\n", commandNumber, command);
            removeC(L);
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        case 'I':
            printf("%s %c\n", commandNumber, command);
            invalidateBids(L);
            break;
        default:
            break;
    }
}


void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    tList L;

    createEmptyList(&L);

    f = fopen(filename, "r");

    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(&L, commandNumber, command[0], param1, param2, param3, param4);
        }

        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}

// Convierte una cadena de texto a un valor del enum tConsoleBrand
void strToEnum(const char *original, tConsoleBrand *copy) {
    if (strcmp(original, "nintendo") == 0) {
        *copy = nintendo;
    } else *copy = sega; // Si no es "nintendo", se asume que es "sega"
}

// Convierte un valor del enum tConsoleBrand a una cadena de texto
void enumToStr(tConsoleBrand original, char *copy) {
    if (original == nintendo) {
        strcpy(copy, "nintendo");
    } else {
        strcpy(copy, "sega");
    }
}

// Añade una nueva consola a la lista si no existe ya
void new(tList *L, tConsoleId id, tUserId user, tConsoleBrand brand, tConsolePrice price) {
    bool error;
    tItemL item;
    char brandC[10];

    if (findItem(id, *L) != LNULL) {
        error = true; // Si ya existe el ID, es un error
    } else {
        // Copia los parámetros y crea un nuevo item
        strcpy(item.seller, user);
        strcpy(item.consoleId, id);
        item.consolePrice = price;
        item.consoleBrand = brand;
        item.bidCounter = 0;
        createEmptyStack(&item.bidStack); // Inicializa pila de pujas
        enumToStr(brand, brandC); // Convierte enum a string para impresión
        error = insertItem(item, L); // Inserta el item en la lista
    }

    // Muestra mensaje dependiendo del resultado
    error
        ? printf("+ Error: New not possible\n")
        : printf("* New: console %s seller %s brand %s price %.2f\n", id, user, brandC, price);
}

// Elimina una consola de la lista y sus pujas si existe
void delete(tList *L, tConsoleId id) {
    tItemL d;
    char brand[10];
    tPosL p = findItem(id, *L); // Busca la consola

    if (p != LNULL) {
        // Si existe la consola
        d = getItem(p, *L);
        enumToStr(d.consoleBrand, brand);
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n", d.consoleId, d.seller, brand,
               d.consolePrice, d.bidCounter);
        while (!isEmptyStack(d.bidStack)) {
            pop(&d.bidStack); // Vacía la pila de pujas
        }
        updateItem(d, p, L); // Actualiza la lista
        deleteAtPosition(p, L); // Elimina el item
    } else {
        printf("+ Error: Delete not possible\n");
    }
}

// Realiza una puja si se cumplen las condiciones necesarias
void bid(tList *L, tConsoleId id, tUserId user, tConsolePrice price) {
    bool error;
    char brand[10];
    tPosL pAux = findItem(id, *L);
    tItemL dAux;
    tItemS sAux;

    if (pAux != LNULL) {
        dAux = getItem(pAux, *L);
        enumToStr(dAux.consoleBrand, brand);
        if ((isEmptyStack(dAux.bidStack) || peek(dAux.bidStack).consolePrice < price) &&
            dAux.consolePrice < price && strcmp(user, dAux.seller) != 0) {
            // Verifica que la puja sea válida

            strcpy(sAux.bidder, user);
            sAux.consolePrice = price;

            error = push(sAux, &dAux.bidStack); // Añade la puja
            if (!error)
                dAux.bidCounter++; // Aumenta el contador si se añadió correctamente
            updateItem(dAux, pAux, L);
        } else error = true;
    } else error = true;

    // Imprime el resultado
    error
        ? printf("+ Error: Bid not possible\n")
        : printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n", dAux.consoleId, user, brand,
                 peek(dAux.bidStack).consolePrice, dAux.bidCounter);
}

// Otorga la consola al mejor postor y elimina todas las pujas
void award(tList *L, tConsoleId id) {
    bool error = false;
    char brand[10];
    char bidder[10];
    float price = 0;
    tItemL dAux;
    tPosL pAux = findItem(id, *L);

    if (pAux != LNULL) { // Encontramos el objeto

        dAux = getItem(pAux, *L);

        enumToStr(dAux.consoleBrand, brand);
        strcpy(bidder, peek(dAux.bidStack).bidder);
        price = peek(dAux.bidStack).consolePrice; // Obtiene datos de la última puja


        if (!isEmptyStack(dAux.bidStack)) {
            // Si tiene pujas las vaciamos y eliminamos la consola
            while (!isEmptyStack(dAux.bidStack)) {
                pop(&dAux.bidStack); // Borra las pujas
            }

            updateItem(dAux, pAux, L);
            deleteAtPosition(pAux, L); // Elimina la consola
        } else error = true;
    } else error = true;

    // Imprime resultado
    error
        ? printf("+ Error: Award not possible\n")
        : printf("* Award: console %s bidder %s brand %s price %.2f\n", id, bidder, brand, price);
}

// Elimina todas las consolas sin pujas
void removeC(tList *L) {
    int nbid = 0;
    tPosL p, aux;
    tItemL d, dAux;
    char brand[10];

    if (isEmptyList(*L)) {
        printf("+ Error: Remove not possible\n");
    } else {
        p = first(*L);
        while (p != LNULL) {
            aux = next(p, *L);
            if(aux!=LNULL)
                    dAux = getItem(aux, *L);
            d = getItem(p, *L);
            enumToStr(d.consoleBrand, brand);
            if (isEmptyStack(d.bidStack)) {
                nbid++; // Contamos las consolas eliminadas
                printf("Removing console %s seller %s brand %s price %.2f bids %d\n", d.consoleId, d.seller, brand,
                       d.consolePrice,
                       d.bidCounter);
                deleteAtPosition(p, L); // Elimina la consola

                if (aux != LNULL) {
                    // Consigo la informacion de lo que apunta ahora p
                    d = getItem(p, *L);
                    if (strcmp(dAux.consoleId, d.consoleId) != 0) {
                        // si el siguiente de p paso a ser p p no avanza
                        p = aux;
                    }
                }else p = aux;
            } else p = aux;
        }
        if (nbid == 0)
            printf("+ Error: Remove not possible\n");
    }
}

// Invalida las pujas de consolas con un número de pujas mayor al doble de la media
void invalidateBids(tList *L) {
    tItemL d;
    tPosL p;
    char brand[10];
    float media = 0;
    int aux = 0;
    int nconsol = 0;

    // Calcula la media de pujas
    for (p = first(*L); p != LNULL; p = next(p, *L)) {
        d = getItem(p, *L);
        media += (float) d.bidCounter;
        nconsol++;
    }
    media /= (float) nconsol;

    // Invalida las pujas si superan el doble de la media
    for (p = first(*L); p != LNULL; p = next(p, *L)) {
        d = getItem(p, *L);
        if (media * 2 < (float) d.bidCounter) {

            while (!isEmptyStack(d.bidStack)) {
                pop(&d.bidStack); // Elimina pujas
            }

            enumToStr(d.consoleBrand, brand);
            printf("* InvalidateBids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n",
                   d.consoleId, d.seller, brand,
                   d.consolePrice, d.bidCounter, media);

            d.bidCounter = 0; // Reinicia contador
            updateItem(d, p, L);
            aux += 1;
        }
    }
    if (aux == 0) {
        printf("+ Error: InvalidateBids not possible\n");
    }
}

// Imprime estadísticas del sistema
void stats(tList L) {
    tPosL i;
    tItemL d;
    tItemL Max_bid;
    tItemS bid;
    int bids = 0;
    int cntNin = 0, cntSeg = 0;
    float priceNin = 0, priceSeg = 0;
    float RR = 0;
    float MAX_RR = 0;
    char brand[10];
    char MAX_brand[10];

    if (isEmptyList(L)) {
        printf("+ Error: Stats not possible\n");
    } else {
        for (i = first(L); i != LNULL; i = next(i, L)) {
            d = getItem(i, L);
            enumToStr(d.consoleBrand, brand);
            if (strcmp(brand, "nintendo") == 0) {
                cntNin++;
                priceNin += d.consolePrice;
            } else {
                cntSeg++;
                priceSeg += d.consolePrice;
            }
            if (d.bidCounter == 0) {
                printf("Console %s seller %s brand %s price %.2f. No bids\n", d.consoleId, d.seller, brand,
                       d.consolePrice);
            } else {
                bid = peek(d.bidStack);
                printf("Console %s seller %s brand %s price %.2f bids %d top bidder %s\n", d.consoleId, d.seller,
                       brand,
                       d.consolePrice,
                       d.bidCounter, bid.bidder);
                RR = (bid.consolePrice - d.consolePrice) / d.consolePrice * 100;
                if (RR > MAX_RR) {
                    strcpy(MAX_brand, brand);
                    MAX_RR = RR;
                    Max_bid = d;
                }
                bids += 1;
            }
        }
        printf("\n");

        // Imprime resumen por marca
        printf("Brand     Consoles    Price  Average\nNintendo  %8d %8.2f %8.2f\nSega      %8d %8.2f %8.2f\n",
               cntNin, priceNin, cntNin == 0 ? priceNin : priceNin / cntNin, cntSeg, priceSeg,
               cntSeg == 0 ? priceSeg : priceSeg / cntSeg);
        if (bids != 0) {
            printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   Max_bid.consoleId, Max_bid.seller, MAX_brand, Max_bid.consolePrice,
                   peek(Max_bid.bidStack).bidder,
                   peek(Max_bid.bidStack).consolePrice, MAX_RR);
        } else {
            printf("Top bid not possible\n");
        }
    }
}
