#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"


/*
* Clase que implementa una estructura de pila en C
*/

/*
*Metodo push
*Ingersa un valor entero a la pila
*/
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *oper1, nodo *oper2, nodo *op, int temp, int indice){
	cuadruplos *existe;
	cuadruplos *existeSeguroQueSi;
	HASH_FIND_INT(listaCuadruplos, &indice, existe);  /* id already in the hash? */
	if (existe==NULL) {
		printf("Entre\n");
		existe = (cuadruplos*)malloc(sizeof(cuadruplos));
		existe->indice = indice;
		existe->operando1 = oper1;
		existe->operando2 = oper2;
		//existe->operador = *(int*)(op->dato);
		existe->resultado = temp;
 	HASH_ADD_INT(listaCuadruplos, indice, existe);  /* id: name of key field */
	return listaCuadruplos;
	} else {	
		printf("Error en la generacion y adicion de indices en el cuadruplo \n");
		return NULL;
	} 
}

void imprimeCuadruplos(cuadruplos *listaCuadruplos) {
    cuadruplos *temporal;

    for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
    	printf("---------------------------------------");
        printf("Ya sabemos indice : %d\n", temporal->indice);
        printf("Ya sabemos Nombre operador1 : %s\n", ((nodoOperando*)(temporal->operando1->dato))->nombre);
        printf("Ya sabemos Nombre operador2 : %s\n", ((nodoOperando*)(temporal->operando2->dato))->nombre);
        printf("Ya sabemos direccion : %d\n", temporal->operador);
        printf("Ya sabemos direccion : %d\n", temporal->resultado);
        printf("---------------------------------------");
    }
}