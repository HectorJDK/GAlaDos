#ifndef CUADRUPLOS_H
#define CUADRUPLOS_H
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
	/*Key*/
	char nombre[50];
	int temp;
	int tipo;
	int reciclada;
	int direccion;
}nodoOperando;
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
void imprimeCuadruplos(cuadruplos *listaCuadruplos, int mode);
void reciclarVariable(nodo *variable, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean);
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *operando1, nodo *operando2, int operador, nodo *resultado, int indice);
cuadruplos* generarCuadruploExpresion(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[4][4][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean);
cuadruplos* generarCuadruploAsignacion(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[4][4][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean);
cuadruplos* generarCuadruploLectura(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int *contadorIndice);
cuadruplos* generarCuadruploEscritura(cuadruplos *listaCuadruplos,  pila *operandos, pila *operadores,  int *contadorIndice);
cuadruplos* generarCuadruploAccion1(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice);
cuadruplos* generarCuadruploAccion2Ciclo(cuadruplos *listaCuadruplos, pila *pilaSaltos, int *contadorIndice);
cuadruplos* generarCuadruploAccion2If(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice);
cuadruplos* generarCuadruploAccion3If(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice);
cuadruplos* generarCuadruploGoto(cuadruplos *listaCuadruplos, int *contadorIndice);
cuadruplos* generarCuadruploGotoFalso(cuadruplos *listaCuadruplos, nodo *operando1, int *contadorIndice);
cuadruplos* generarCuadruploEra(cuadruplos *listaCuadruplos, char *nombreFuncion, char *nombreObjeto,int *contadorIndice);
cuadruplos* generarCuadruploEndProc(cuadruplos *listaCuadruplos, int *contadorIndice);
cuadruplos* generarCuadruploParam(cuadruplos *listaCuadruplos, int *cantidadParametros, pila *operandos, int *contadorIndice);
cuadruplos* generarCuadruploGosub(cuadruplos *listaCuadruplos, int direccionFuncion, int *contadorIndice);
cuadruplos* generarCuadruploReturn(cuadruplos *listaCuadruplos, pila *operandos, int tipo, long direccion, char *nombre, int *contadorIndice);
cuadruplos* generarCuadruploTemporalFuncion(cuadruplos *listaCuadruplos, pila *operandos, int tipo, long direccion, char *nombre, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean, int *contadorIndice);
cuadruplos* generarCuadruploEndProgram(cuadruplos *listaCuadruplos, int *contadorIndice);
cuadruplos* generaCuadruploVerifica(cuadruplos *listaCuadruplos, pila *operandos,  int lsuperior, int *contadorIndice );
cuadruplos* generaCuadruploSUMAarreglo (cuadruplos *listaCuadruplos, pila *operandos, int direccionBase, pila *availEntero, int *contadorIndice);
cuadruplos* generarCuadruploMULTIarreglo(cuadruplos *listaCuadruplos, pila *operandos, int m1, pila *availEntero, int *contadorIndice);
cuadruplos* generarCuadruploSequencial(int prioridad, cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[4][4][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean);
void generarObj(cuadruplos *listaCuadruplos); 
#endif