/*
*Hector Jesus De La Garza Ponce 	619971
*Oziel Alonzo Garza Lopez 			805074

*Libreria pila.h
*/

#ifndef PILAS_H
#define PILAS_H

//Estructuras para los nodos
typedef struct nodo
{
	void* dato;
	struct nodo *siguiente;		
} nodo;

//Estructura para las pilas
typedef struct pila
{	
	int tamanio;
	struct nodo *primero;
}pila;

//Firmas de los metodos
void push(pila *x, void* dato);
nodo* pop(pila *x);
int pilaVacia(pila *x);
#endif