#include <stdio.h>
#include <stdlib.h>
#include "pilaChar.h"
/*
*Clase que implementa una estructura de pila en C
*/

/*
*Metodo push
*Ingresa un valor entero a la pila
*/
void push(pilaChar *x, char* dato){
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
		nuevo->siguiente=NULL;
		x->primero = nuevo;
		x->tamanio+=1;
	}	
}

/*
*Metodo pop
*Saca un elemento de la pila
*/
char* pop(pilaChar *x){
	//Si la pila no esta vacia 
	if(pilaVacia(x)==1){					
		//Obtener el nodo cabeza
		nodo *cabeza;
		cabeza= malloc(sizeof(nodo));
		cabeza=x->primero;

		//Crear un nodo auxiliar
		nodo *uno;
		uno = malloc(sizeof(nodo));
		uno = cabeza->siguiente;

		//Regresar el dato de la cabeza
		char* dato;
		dato = cabeza->dato;

		//Liberar memoria de la cabeza
		free(x->primero);
		
		//Poner como cabeza al nodo auxiliar
		x->primero=uno;
		x->tamanio-=1;

		return dato;
	} else {	
		free(x->primero);
		x->primero=NULL;
		return NULL;		
	}
}

/*
*Metodo pilaVacia
*Verifica si la pila tiene uno o mas elementos.
*/
int pilaVacia(pilaChar *x){	
	if(x->tamanio == 0){
		return 0;
	} else return 1;
}

/*
*Metodo imprimirPila
*Imprime los nodos de la pila
*/
void imprimirPilaChar(pilaChar *x){
	
	nodo *aux;
	aux = x->primero;
	while (aux!=NULL){
		printf("---------------\n");
		printf("Dato: %s\n",aux->dato);
		printf("---------------\n");					
		aux=aux->siguiente;
		} 		
}

