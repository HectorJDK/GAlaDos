//Libreria para las estructuras de pila
#include "pilas.h"
//Libreria para las estructuras de nodoOperando, nodoOperadores,...
#include "cuadruplos.h"
//Libreria para los codigos de operaciones
#include "codigosOperaciones.h"

//Definiciones de operadores
#define TIPO_ENTERO			0
#define TIPO_DECIMAL 		1 
#define TIPO_TEXTO 			2
#define TIPO_BOOLEANO 		3

#define OP_ERROR 			-1

void inicializarSemantica(int cuboSemantico[4][4][14]);
void inicializarAvail(pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean,int *memoriaEnteroTemp, int *memoriaDecimalTemp, int *memoriaTextoTemp, int *memoriaBooleanoTemp);
