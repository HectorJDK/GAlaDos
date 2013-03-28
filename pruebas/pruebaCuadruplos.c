#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"


//Pila generica
pila *p;
nodo *aux;
nodo *aux2;
nodo *operador;

cuadruplos *listaCuadruplos = NULL;

int main()
{   
    p = malloc(sizeof(pila));           
    p->tamanio = 0;                     
    p->primero = NULL;

    nodoOperando prueba;
    prueba.temp = 0;
    prueba.tipo = 2;
    strcpy(prueba.nombre, "variables");
    prueba.direccion = 1152;

    push(p,&prueba);
    
    nodoOperando prueba2;
    prueba2.temp = 0;
    prueba2.tipo = 3;
    strcpy(prueba2.nombre, "direccion");
    prueba2.direccion = 1153;

    push(p,&prueba2);


    aux = pop(p);
    
    nodoOperando resultado;

    resultado = *(nodoOperando*)(aux->dato);
    printf("Ya sabemos temp : %d\n", resultado.temp);
    printf("Ya sabemos direccion : %d\n", resultado.direccion);


    aux2 = pop(p);

    resultado = *(nodoOperando*)(aux2->dato);
    printf("Ya sabemos temp : %d\n", resultado.temp);
    printf("Ya sabemos direccion : %d\n", resultado.direccion);


    nodoOperador prueba3;
    prueba3.operador = 1;

    push(p, &prueba3);

    operador = pop(p);


    listaCuadruplos = generaCuadruplo(listaCuadruplos, aux, aux2, operador, 1, 0);
    listaCuadruplos = generaCuadruplo(listaCuadruplos, aux, aux2, operador, 1, 1);
    imprimeCuadruplos(listaCuadruplos);
    free(p);

    return 0;
}
