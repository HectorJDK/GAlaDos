#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
/*
*Tabla de variables
*/

/*
*Metodo search
*Busca un valor en la fila
*/
int search(fila *x, char* nombre){
	int encontrado = 0;
	nodo *aux;
	aux = x->primero;
	int cursor = 1;
	while (cursor <= x->tamanio){
		if(strcmp(aux->nombre,nombre)==0){
			encontrado = 1;
			cursor = x->tamanio +1;
		} else {
			aux=aux->siguiente;
		} 
		cursor ++;
}
return encontrado;
}

/*
*Metodo imprimirFila
*Imprime los nodos de la fila
*/
void imprimirFila(fila *x){
	
	nodo *aux;
	aux = x->primero;
	while (aux!=NULL){
		printf("---------------\n");
		printf("Variable: %s\n",aux->nombre);
		printf("Tipo: %s\n",aux->tipo);
		printf("Valor: %s\n",aux->dato);
		printf("---------------\n");					
		aux=aux->siguiente;
		} 		
}

/*
*Metodo push
*Ingresa un valor entero a la fila
*/
void push(fila *x, char* nombre, char* dato, char* tipo){
	//Si la fila tiene elementos, crear un nuevo nodo y ponerlo al ultimo
	//El nodo siguiente del nuevo nodo es vacio.
	if(filaVacia(x)==1){
		nodo *nuevo;
		nuevo = malloc(sizeof(nodo));
		
		nuevo->nombre = nombre;
		nuevo->dato = dato;
		nuevo->tipo = tipo;

		nuevo->siguiente=NULL;
	
		nodo *aux;
		aux = x->ultimo;
		aux->siguiente=nuevo;
		//x->ultimo=aux;	
		x->ultimo=aux->siguiente;	
		x->tamanio+=1;
	}else{
		//Si la fila no tiene elementos, ingresar el nodo nuevo y ponerlo como cabeza y ultimo
		nodo *nuevo;
		nuevo = malloc(sizeof(nodo));
		nuevo->nombre = nombre;
		nuevo->dato = dato;
		nuevo->tipo = tipo;
		nuevo->siguiente=NULL;
		x->primero=nuevo;
		x->ultimo=nuevo;
		x->tamanio+=1;
	}	
}

/*
*Metodo pop
*Saca un elemento de la fila
*/
void pop(fila *x){
	//Si la fila no esta vacia 
	if(filaVacia(x)==1){					
		//Obtener el primer nodo 
		nodo *primero;
		primero=x->primero;

		//Crear un nodo auxiliar 
		nodo *uno;
		uno = primero->siguiente;
		//Liberar memoria de la cabeza
		free(x->primero);
		//Poner como cabeza al nodo auxiliar
		x->primero=uno;
		x->tamanio-=1;
	} else {	
		free(x->primero);
		x->primero=NULL;		
	}
}

/*
*Metodo filaVacia
*Verifica si la fila tiene uno o mas elementos.
*/
int filaVacia(fila *x){	
	if(x->tamanio == 0){
		return 0;
	} else return 1;
}