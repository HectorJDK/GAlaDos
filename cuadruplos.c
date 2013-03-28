#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"

/*
* que implementa una estructura de pila en C
*/

/*
*GenerarCuadruplo 
*Crea un cruadruplo y lo guarda en la lista de cuadruplos correspondiente, usa nodos en donde se tiene la informacion general
*/
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *oper1, nodo *oper2, nodo *op, int temp, int indice){
	cuadruplos *existe;
	nodoOperando *tempOper1;
	nodoOperando *tempOper2;
	nodoOperando *tempResultado;
	
	//Obtenemos una nueva direccion reservada para nuestro resultado, asi obtenemos independencia
	tempOper1 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempOper2 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempResultado = (nodoOperando*)malloc(sizeof(nodoOperando));
	

	//Checamos si se ha agregado el cuadruplo anteriromente
	HASH_FIND_INT(listaCuadruplos, &indice, existe);  /* id already in the hash? */
	if (existe==NULL) {
		//Si no se ha agregado el cuadruplo se crea y se llena sus datos
		existe = (cuadruplos*)malloc(sizeof(cuadruplos));

		//Pasamos todos los datos de oper1
		tempOper1->temp = ((nodoOperando*)oper1->dato)->temp;
		tempOper1->tipo = ((nodoOperando*)oper1->dato)->tipo;
		strcpy(tempOper1->nombre, ((nodoOperando*)oper1->dato)->nombre);
		tempOper1->direccion = ((nodoOperando*)oper1->dato)->tipo;

		//Pasamos todos los datos de oper2
		tempOper2->temp = ((nodoOperando*)oper2->dato)->temp;
		tempOper2->tipo = ((nodoOperando*)oper2->dato)->tipo;
		strcpy(tempOper2->nombre, ((nodoOperando*)oper2->dato)->nombre);
		tempOper2->direccion = ((nodoOperando*)oper2->dato)->tipo;

		//Genera el nodo resultado y lo asigna como temporal
		tempResultado->temp = indice;
		tempResultado->tipo = temp;
		strcpy(tempResultado->nombre, "temporal");		
		//Sacar direccion del avail
		//tempResultado.direccion = 1152;

		//Pasar todos los datos al recien creado cuadruplo
		existe->indice = indice;
		existe->operando1 = tempOper1;
		existe->operando2 = tempOper2;
		existe->operador = *(int*)(op->dato);
		existe->resultado = tempResultado;

	//Agregamos el nuevo cuaruplo a la lista de hash y regresamos el nuevo apuntador
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
		printf("Ya sabemos Nombre operador1 : %s\n", temporal->operando1->nombre);
		printf("Ya sabemos Nombre operador2 : %s\n", temporal->operando2->nombre);
		printf("Ya sabemos operador : %d\n", temporal->operador);
		printf("Ya sabemos Resultado tipo : %d\n", temporal->resultado->tipo);
		printf("Ya sabemos Resultado temp : %d\n", temporal->resultado->temp);
		printf("Ya sabemos Resultado nombre : %s\n", temporal->resultado->nombre);
		printf("---------------------------------------\n");
	}
}