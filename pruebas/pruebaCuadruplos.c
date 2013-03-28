#include "cuadruplos.h"
#include "cuboSemantico.h"
#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Pila generica
pila *p;
pila *op;
nodo *aux;
nodo *aux2;
nodo *operador;

cuadruplos *listaCuadruplos = NULL;
static int cuboSemantico[4][4][14];

int main()
{   
    inicializarSemantica(cuboSemantico);

    p = malloc(sizeof(pila));           
    p->tamanio = 0;                     
    p->primero = NULL;

    op = malloc(sizeof(pila));           
    op->tamanio = 0;                     
    op->primero = NULL;

    nodoOperando prueba;
    prueba.temp = 0;
    prueba.tipo = 1;
    strcpy(prueba.nombre, "operando1");
    prueba.direccion = 1152;

    push(p,&prueba);
    
    nodoOperando prueba2;
    prueba2.temp = 0;
    prueba2.tipo = 0;
    strcpy(prueba2.nombre, "operando2");
    prueba2.direccion = 1153;

    push(p,&prueba2);

    nodoOperador prueba3;
    prueba3.operador = 2;

    push(op, &prueba3);

    aux2 = pop(p);
    aux = pop(p);
    operador = pop(op);


    int operando1 = ((nodoOperando*)(aux->dato))->tipo;
    int operando2 = ((nodoOperando*)(aux2->dato))->tipo;
    int op = *(int*)(operador->dato);
    printf("%i\n", cuboSemantico[operando1][operando2][op]);

    if (cuboSemantico[operando1][operando2][op] >= 0)
    {

        listaCuadruplos = generaCuadruplo(listaCuadruplos, aux, aux2, operador, cuboSemantico[operando1][operando2][op], 0);
        strcpy(((nodoOperando*)aux->dato)->nombre, "chingate");
        listaCuadruplos = generaCuadruplo(listaCuadruplos, aux, aux2, operador, cuboSemantico[operando1][operando2][op], 1);
        imprimeCuadruplos(listaCuadruplos);
    } else {
        printf("Operacion Invalida\n");
    }
    
    free(p);
    return 0;
}
