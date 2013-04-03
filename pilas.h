#ifndef PILAS_H
#define PILAS_H
//Encabezado pilaChar.h
//La estructura almacena un dato tipo char
//Estructuras para los nodos y la pila
typedef struct nodo
{
	void* dato;
	struct nodo *siguiente;		
} nodo;

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