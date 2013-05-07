/*
*Hector Jesus De La Garza Ponce 	619971
*Oziel Alonzo Garza Lopez 			805074

*Libreria utilerias.h
*/
#include "pilas.h"
#include "cuadruplos.h"
#include "codigosOperaciones.h"

//Definiciones de operadores
#define TIPO_ENTERO			0
#define TIPO_DECIMAL 		1 
#define TIPO_TEXTO 			2
#define TIPO_BOOLEANO 		3
#define TIPO_OBJETO 		4

//Operador error de operacion
#define OP_ERROR 			-1

//Prototipos de funciones
void inicializarSemantica(int cuboSemantico[5][5][14]);
void inicializarAvail(pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean,int *memoriaEnteroTemp, int *memoriaDecimalTemp, int *memoriaTextoTemp, int *memoriaBooleanoTemp);
