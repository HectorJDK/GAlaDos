/*
*Hector Jesus De La Garza Ponce 	619971
*Oziel Alonzo Garza Lopez 			805074

*Libreria pila.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilas.h"

/*
* Función: push
* Parámetros: pila *x, void* dato
* Descripción: Funcion encargada de agregar un valor desconocido a una pila, el valor desconocido solo sera un pointer a este
* Salida: ninguna
*/
void push(pila *x, void* dato){
	//Si la pila tiene elementos, crear un nuevo nodo y ponerlo como la cabeza
	//El nodo siguiente del nuevo nodo es la cabeza actual de la pila.
	if(pilaVacia(x)==1){
		nodo *nuevo = malloc(sizeof(nodo));		
		nuevo->dato = dato;		
		nuevo->siguiente=x->primero;
		x->primero = nuevo;	
		x->tamanio+=1;
	}else{
		//Si la pila no tiene elementos, ingresar el nodo nuevo y ponerlo como la cabeza
		nodo *nuevo = malloc(sizeof(nodo));	
		nuevo->dato = dato;			
		nuevo->siguiente = NULL;
		x->primero = nuevo;
		x->tamanio+=1;
	}	
}

/*
* Función: pop
* Parámetros: pila *x
* Descripción: Saca de la pila el nodo con el apuntador al dato desconocido, al realizar esto el nodo ya se le hizo free
* Salida: Regresa un apuntador a una variable tipo nodo donde se encuentra un apuntador al dato
*/
nodo* pop(pila *x){
	//Si la pila no esta vacia 
	if(pilaVacia(x)==1){					
		//Obtener el nodo cabeza
		nodo *cabeza;
		cabeza = malloc(sizeof(nodo));
		cabeza = x->primero;

		//Crear un nodo auxiliar
		nodo *nuevaCabeza;
		nuevaCabeza = malloc(sizeof(nodo));
		nuevaCabeza = cabeza->siguiente;

		// Regresar el dato de la cabeza
		nodo* temporal;
		temporal = malloc(sizeof(nodo));
		temporal->dato = cabeza->dato;

		//Liberar memoria de la cabeza
		free(x->primero);
		
		//Poner como cabeza al nodo auxiliar
		x->primero = nuevaCabeza;
		x->tamanio = x->tamanio - 1;

		return temporal;
	} else {
		x->primero = NULL;
		return NULL;
	}
}

/*
* Función: pilaVacia
* Parámetros: pila *x
* Descripción: Verifica que la pila no este vacia, regresa un 1 si tiene uno o mas elementos, 0 de lo contrario
* Salida: Regresa un entero con valor 0 o 1
*/
int pilaVacia(pila *x){	
	if(x->tamanio == 0)
		return 0;
	else 
		return 1;
}