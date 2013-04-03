//Libreria para las estructuras de pila
#include "pilas.h"
//Libreria para las estructuras de nodoOperando, nodoOperadores,...
#include "cuadruplos.h"
//Libreria para los codigos de operaciones
#include "codigosOperaciones.h"

//Definiciones de operadores
#define ENTERO 			0
#define DECIMAL 		1 
#define TEXTO 			2
#define BOOLEANO 		3

#define ERROR 			-1

void inicializarSemantica();
void inicializarAvail();