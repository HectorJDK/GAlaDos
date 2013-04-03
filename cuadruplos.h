#include "uthash.h"
#include "pilas.h"
#ifndef CUADRUPLOS_H
#define CUADRUPLOS_H
/*
Hector Jesus De La Garza Ponce 	619971
Oziel Alonzo Garza Lopez 		805074

Libreria cuadruplos.c
Esta estructura almacenara dos nodos operandos en una estructura hash la cual le permitira poder realizar los chequeos
sintacticos asi como checar cual sera el resultado de la operacion que realizara

*/

//Estructura Nodo Operadores---------------------------------------------------------------------------------------------
typedef struct nodoOperador
{	
	int operador;
}nodoOperador;
//--------------------------------------------------------------------------------------------------------------------

//Estructura Nodo Operandos---------------------------------------------------------------------------------------------
typedef struct nodoOperando
{	
	int temp;
	int tipo;
	char nombre[25];
	int direccion;
}nodoOperando;
//--------------------------------------------------------------------------------------------------------------------

//Estructura Nodo Saltos---------------------------------------------------------------------------------------------
typedef struct nodoSalto
{	
	int indice;
}nodoSalto;
//--------------------------------------------------------------------------------------------------------------------

//Estructura Cuadruplos---------------------------------------------------------------------------------------------
typedef struct cuadruplos
{
	/*Key*/
	int indice; 
	nodoOperando *operando1;
	nodoOperando *operando2;
	int operador;
	nodoOperando *resultado;
	UT_hash_handle hh;
} cuadruplos;
#endif

//Firmas de los metodos
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *operando1, nodo *operando2, nodo *operador, nodo *resultado, int indice);
void imprimeCuadruplos(cuadruplos *listaCuadruplos, int mode);
cuadruplos* verificacionGeneracionCuadruplo (int prioridad, cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[4][4][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean);