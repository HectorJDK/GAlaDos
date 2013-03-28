#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"

/*
* Clase que implementa una estructura de pila en C
*/

/*
*GenerarCuadruplo 
*Crea un cruadruplo y lo guarda en la lista de cuadruplos correspondiente, usa nodos en donde se tiene la informacion general
*/
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *oper1, nodo *oper2, nodo *op, int temp, int indice){
	cuadruplos *existe;

	//Checamos si se ha agregado el cuadruplo anteriromente
	HASH_FIND_INT(listaCuadruplos, &indice, existe);  /* id already in the hash? */
	if (existe==NULL) {
		//Si no se ha agregado el cuadruplo se crea y se llena sus datos
		existe = (cuadruplos*)malloc(sizeof(cuadruplos));
		existe->indice = indice;
		existe->operando1 = oper1;
		existe->operando2 = oper2;
		existe->operador = *(int*)(op->dato);
		existe->resultado = temp;
	//Agregamos el nuevo cuadruplo a la lista de hash y regresamos el nuevo apuntador
 	HASH_ADD_INT(listaCuadruplos, indice, existe);  /* id: name of key field */
	return listaCuadruplos;
	} else {	

		printf("Error en la generacion y adicion de indices en el cuadruplo \n");
		return NULL;
	} 
}

/*
*imprimeCuadruplos
*Imprime todos los datos en orden de la lista de cuadruplos que se da
*/
void imprimeCuadruplos(cuadruplos *listaCuadruplos) {
    cuadruplos *temporal;

    for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
    	printf("---------------------------------------\n");
        printf("Ya sabemos indice : %d\n", temporal->indice);
        printf("Ya sabemos Nombre operador1 : %s\n", ((nodoOperando*)(temporal->operando1->dato))->nombre);
        printf("Ya sabemos Nombre operador2 : %s\n", ((nodoOperando*)(temporal->operando2->dato))->nombre);
        printf("Ya sabemos operador : %d\n", temporal->operador);
        printf("Ya sabemos resultado : %d\n", temporal->resultado);
        printf("---------------------------------------\n");
    }
}