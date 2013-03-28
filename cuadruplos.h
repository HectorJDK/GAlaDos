#include "uthash.h"
#include "pilas.h"

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


//Firmas de los metodos
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *oper1, nodo *oper2, nodo *op, int temp, int indice);
void imprimeCuadruplos(cuadruplos *listaCuadruplos, int mode);