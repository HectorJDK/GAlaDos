%{
	//Hector Jesus De La Garza Ponce
	//Oziel Alonso Garza Lopez
	extern char * yytext;
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>  /* strcpy */
	#include "uthash.h"
	#include "tablasVarProc.h"
	#include "codigosOperaciones.h"
	#include "pilas.h"
	#include "utilerias.h"
	#include "cuadruplos.h"
	#define YYERROR_VERBOSE 1
	
//----------------------------------------------------------------------------------------


void yyerror( const char *str )
{
	fprintf( stderr, "error: %s\n", str );
}

//Contadores de temporales para las funciones
int totalTempEntero = 0;
int totalTempDecimal = 0;
int totalTempTexto = 0;
int totalTempBooleano = 0;

//Globales miscelaneas de Control
int tamanioIdentificadores = 25;

//Varialbes para el manejo de las secciones
int seccVariablesGlobales = 0;
int seccVariablesLocales = 0;
int seccFuncionesImplementacion = 0;
int seccObjeto = 0;
int seccMain = 0;

//Variables para la creacion de variables en la tabla
int direccionVariable;
char nombreObjeto[25];
char nombreVariable[25];
unsigned short tipoVariable;
char nombreProcedimiento[25];
int direccionVariableConstante;

//Pilas operaciones
pila *operandos;
pila *operadores;

//Pilas Avail
pila *availEntero;
pila *availDecimal;
pila *availTexto;
pila *availBoolean;

//Pila saltos 
pila *pilaSaltos;

//Contador de cuadruplos
int contadorIndice = 0;

//Variables para control
nodoOperando *operando;
nodoOperador *operador;
nodoOperador *salto;
directorio *variable;

//Variables para control de memoria
int cantidadVariablesConstante = 1000;
int cantidadVariablesTemp = 1000;
int cantidadVariablesLocal = 1000;
int cantidadVariablesGlobal = 1000;

//Direcciones base para memoria
int baseMemoriaConstante = 13000;
int baseMemoriaTemp = 9000;
int baseMemoriaLocal = 5000;
int baseMemoriaGlobal = 1000;


//Usado para calculo de direcciones
int cursorEntero = 1;
int cursorDecimal = 2;
int cursorTexto = 3;
int cursorBooleano = 4;

//Division de la memoria
//Por el momento solo son 1000 direcciones por cada tipo
//****************************
//Constantes
//De la 13,000 hasta la 16,999
int memoriaEnteroConstante;
int memoriaDecimalConstante;
int memoriaTextoConstante;
int memoriaBooleanoConstante;

//Temporales
//De la 9,000 hasta la 12,999
int memoriaEnteroTemp;
int memoriaDecimalTemp;
int memoriaTextoTemp;
int memoriaBooleanoTemp;

//Locales
//De la 5,000 hasta la 8,999
int memoriaEnteroLocal;
int memoriaDecimalLocal;
int memoriaTextoLocal;
int memoriaBooleanoLocal;
//****************************

//Locales
//De la 1,000 hasta la 4,999
int memoriaEnteroGlobal;
int memoriaDecimalGlobal;
int memoriaTextoGlobal;
int memoriaBooleanoGlobal;
//****************************

//cuboSemantico
static int cuboSemantico[4][4][14];

//Lista de cuadruplos
cuadruplos *listaCuadruplos = NULL;

//Declaracion e inicializacion de la estructura objetos
directorioObjetos *objetos = NULL;

//Declaracion para la tabla de constates
directorio *constantes = NULL;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void  generarMultiplicacionDivision(){
	listaCuadruplos = generarCuadruploSequencial(1 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarSumaResta(){
	listaCuadruplos = generarCuadruploSequencial(2 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarRelacional(){
	listaCuadruplos = generarCuadruploSequencial(3, listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarAndOr(){
	listaCuadruplos = generarCuadruploSequencial(4, listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarAsignacion(){
	listaCuadruplos = generarCuadruploSequencial(5 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarLectura(){
	listaCuadruplos = generarCuadruploSequencial(6 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarEscritura(){
	listaCuadruplos = generarCuadruploSequencial(7 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void generarAccion1Ciclo(){
		listaCuadruplos = generarCuadruploAccion1(listaCuadruplos, operandos, pilaSaltos, &contadorIndice);
}

void generarAccion2Ciclo(){
		listaCuadruplos = generarCuadruploAccion2Ciclo(listaCuadruplos, pilaSaltos, &contadorIndice);
}

void generarAccion1If(){
	listaCuadruplos = generarCuadruploAccion1(listaCuadruplos, operandos, pilaSaltos, &contadorIndice);
}

void generarAccion2If(){
	listaCuadruplos = generarCuadruploAccion2If(listaCuadruplos,  operandos, pilaSaltos, &contadorIndice);
}

void generarAccion3If(){
	listaCuadruplos = generarCuadruploAccion3If(listaCuadruplos, operandos, pilaSaltos, &contadorIndice);
}

void generarGoto(){
	listaCuadruplos = generarCuadruploGoto(listaCuadruplos, &contadorIndice);
}

void rellenarGoto(){
	listaCuadruplos = generarCuadruploAccion3If(listaCuadruplos, operandos, pilaSaltos, &contadorIndice);
}

void asignarMemoriaVariable(){
	//Checamos en que seccion nos encontramos al momento de crear una variable
	if (seccVariablesGlobales == 1) {
			//Estamos en las variables Globales
			//Determinar que tipo de variable tomaremos el dato
		switch(tipoVariable){
			case 0:
				if (memoriaEnteroGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorEntero)) {
					direccionVariable = memoriaEnteroGlobal;
					memoriaEnteroGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-entero\n");
					exit(1);
				}	
			break;

			case 1:
				if (memoriaDecimalGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorDecimal)) {
					direccionVariable = memoriaDecimalGlobal;
					memoriaDecimalGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-decimal\n");
					exit(1);
				}
			break;

			case 2:
				if (memoriaTextoGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorTexto)) {
					direccionVariable = memoriaTextoGlobal;
					memoriaTextoGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-Texto\n");
					exit(1);
				}
			break;

			case 3:
				if (memoriaBooleanoGlobal < (baseMemoriaGlobal + cantidadVariablesGlobal * cursorBooleano)) {
					direccionVariable = memoriaBooleanoGlobal;
					memoriaBooleanoGlobal++;
				} else{
					printf("Error: memoria insuficiente de tipo global-Booleano\n");
					exit(1);
				}
			break;
		}

	} else if (seccVariablesLocales == 1) {
		switch(tipoVariable){
			case 0:
				if (memoriaEnteroLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorEntero)) {
					direccionVariable = memoriaEnteroLocal;
					memoriaEnteroLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-entero\n");
					exit(1);
				}
			break;

			case 1:
				if (memoriaDecimalLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorDecimal)) {
					direccionVariable = memoriaDecimalLocal;
					memoriaDecimalLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-decimal\n");
					exit(1);
				}
			break;

			case 2:
				if (memoriaTextoLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorTexto)) {
					direccionVariable = memoriaTextoLocal;
					memoriaTextoLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-Texto\n");
					exit(1);
				}
			break;

			case 3:
				if (memoriaBooleanoLocal < (baseMemoriaLocal + cantidadVariablesLocal * cursorBooleano)) {
					direccionVariable = memoriaBooleanoLocal;
					memoriaBooleanoLocal++;
				} else{
					printf("Error: memoria insuficiente de tipo Local-Booleano\n");
					exit(1);
				}
			break;
		}
	}
}

void asignarMemoriaVariableConstante(int tipoConstate){
	//Checamos en que seccion nos encontramos al momento de crear una variable
			//Estamos en las variables Globales
			//Determinar que tipo de variable tomaremos el dato
	switch(tipoConstate){
		case 0:
		if (memoriaEnteroConstante < (baseMemoriaConstante + cantidadVariablesConstante * cursorEntero)) {
			direccionVariableConstante = memoriaEnteroConstante;
			memoriaEnteroConstante++;
		} else{
			printf("Error: memoria insuficiente de tipo Constante-entero\n");
			exit(1);
		}	
		break;

		case 1:
			if (memoriaDecimalConstante < (baseMemoriaConstante + cantidadVariablesConstante * cursorDecimal)) {
				direccionVariableConstante = memoriaDecimalConstante;
				memoriaDecimalConstante++;
			} else{
				printf("Error: memoria insuficiente de tipo Constante-decimal\n");
				exit(1);
			}
			break;

		case 2:
			if (memoriaTextoConstante < (baseMemoriaConstante + cantidadVariablesConstante * cursorTexto)) {
				direccionVariableConstante = memoriaTextoConstante;
				memoriaTextoConstante++;
			} else{
				printf("Error: memoria insuficiente de tipo Constante-Texto\n");
				exit(1);
			}
			break;

		case 3:
			if (memoriaBooleanoConstante < (baseMemoriaConstante + cantidadVariablesConstante * cursorBooleano)) {
				direccionVariableConstante = memoriaBooleanoConstante;
				memoriaBooleanoConstante++;
			} else{
				printf("Error: memoria insuficiente de tipo Constante-Booleano\n");
				exit(1);
			}
			break;
	}
}

void calcularMemoriaVirtual(){
	//Memoria Temporal
	memoriaEnteroTemp = baseMemoriaTemp + (cantidadVariablesTemp * 0);
	memoriaDecimalTemp = baseMemoriaTemp + (cantidadVariablesTemp * 1);
	memoriaTextoTemp = baseMemoriaTemp + (cantidadVariablesTemp * 2);
	memoriaBooleanoTemp = baseMemoriaTemp + (cantidadVariablesTemp * 3);

	//Memoria Local
	memoriaEnteroLocal = baseMemoriaLocal + (cantidadVariablesLocal * 0);
	memoriaDecimalLocal = baseMemoriaLocal + (cantidadVariablesLocal * 1);
	memoriaTextoLocal =	baseMemoriaLocal + (cantidadVariablesLocal * 2);
	memoriaBooleanoLocal = baseMemoriaLocal + (cantidadVariablesLocal * 3);

	//Memoria Global
	memoriaEnteroGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 0);
	memoriaDecimalGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 1);
	memoriaTextoGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 2);
	memoriaBooleanoGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 3);

	//Memoria Constante
	memoriaEnteroConstante = baseMemoriaConstante + (cantidadVariablesConstante * 0);
	memoriaDecimalConstante = baseMemoriaConstante + (cantidadVariablesConstante * 1);
	memoriaTextoConstante = baseMemoriaConstante + (cantidadVariablesConstante * 2);
	memoriaBooleanoConstante = baseMemoriaConstante + (cantidadVariablesConstante * 3);
}

void agregarTablaConstantes(char *nombre, int tipo){
	directorio *temp;

	//Buscar si anteriormente se ha insertado la constante en la tabla
	temp = buscarConstante(constantes, nombre);

	if (temp == NULL) {
		asignarMemoriaVariableConstante(tipo);
		constantes = agregarConstante(constantes, nombre, tipo, direccionVariableConstante);
	}
}

void inicializarCompilador(){
	//Accion numero 1
	//Inicializacion de estructuras

	//Calculamos la memoria a usar
	calcularMemoriaVirtual();

	//Creacion de las pilas en memoria
	operandos = malloc(sizeof(pila));
	operandos->tamanio = 0;
	operandos->primero = NULL;

	operadores = malloc(sizeof(pila));
	operadores->tamanio = 0;
	operadores->primero = NULL;

	//Creacion de las pilas de Avail en Memoria
	availEntero = malloc(sizeof(pila));
	availEntero->tamanio = 0;
	availEntero->primero = NULL;

	availDecimal = malloc(sizeof(pila));
	availDecimal->tamanio = 0;
	availDecimal->primero = NULL;

	availTexto = malloc(sizeof(pila));
	availTexto->tamanio = 0;
	availTexto->primero = NULL;

	availBoolean = malloc(sizeof(pila));
	availBoolean->tamanio = 0;
	availBoolean->primero = NULL;

	//Inicializacion de pila de Saltos
	pilaSaltos = malloc(sizeof(pila));
	pilaSaltos->tamanio = 0;
	pilaSaltos->primero = NULL;

	//Inicializacion del Avial
	inicializarAvail(availEntero, availDecimal, availTexto, availBoolean, &memoriaEnteroTemp, &memoriaDecimalTemp, &memoriaTextoTemp, &memoriaBooleanoTemp);

	//Inicializacion del CuboSemantico
	inicializarSemantica(cuboSemantico);
}

void pushPilaOperadores(int valor){
	//Creamos el nodo operandor que se le hara push en la pila operadores
	operador = (nodoOperador*)malloc(sizeof(nodoOperador));
	operador->operador = valor;
		
	//Metemos la multiplicacion en la pila de operadores
	push(operadores, operador);
}

//----------------------------------------------------------------------------


//----------------------------------MAIN--------------------------------------

int main()
{

	yyparse();
	//imprimirObjetos(objetos);
	//imprimeCuadruplos(listaCuadruplos, 0);
	generarObj(listaCuadruplos);
	generarDatos(objetos, constantes);
	return 0;
}


%}

%union
{
	char* sval;
	unsigned short ival;
};

%token DOSPUNTOS
%token COMA
%token ES
%token CREAROBJETO
%token VARIABLES_GLOBALES
%token VARIABLES_LOCALES
%token DECLARA_OBJETOS
%token DECLARA_FUNCIONES
%token IMPLEMENTA_FUNCIONES
%token ATRIBUTOS_GLOBALES
%token <ival> BOOLEANO
%token <ival> ENTERO
%token <ival> DECIMAL
%token <ival> TEXTO
%token NADA
%token CLASE
%token <ival> MATRIZENTERA
%token <ival> MATRIZDECIMAL
%token PRIVADA
%token PUBLICA
%token REGRESA
%token HIJODE
%token EJECUTARPROGRAMA
%token LEERDELTECLADO
%token DESPLIEGA
%token SI
%token SINO
%token ENTONCES
%token MIENTRAS
%token FLECHA
%token CONCATENA
%token IGUAL
%token MAS
%token MENOS
%token POR
%token ENTRE
%token PUNTOYCOMA
%token APARENTESIS
%token CPARENTESIS
%token ALLAVE
%token CLLAVE
%token ACORCHETE
%token CCORCHETE
%token AMPERSAND
%token BARRA
%token COMPARA
%token NEGACION
%token MAYORQUE
%token MENORQUE
%token MAYORIGUAL
%token MENORIGUAL
%token <sval> CTEENTERA
%token <sval> CTETEXTO
%token <sval> CTEBOOLEANO
%token <sval> CTEDECIMAL
%token <sval> IDENTIFICADOR
%start programa
%%

programa:
	{
		//Inicializamos las diferentes estructuras de control para el compilador
		inicializarCompilador();

		//Metemos el contador en la pila de saltos
		salto = (nodoOperador*)malloc(sizeof(nodoOperador));
		salto->operador = contadorIndice;
		push(pilaSaltos, salto);
		
		// cuadruplo 0 sera un goto a ejecutarPrograma
		generarGoto();
	}
	declara_objetos 
	{
		//Accion numero 2
		//Agregar main a tabla de objetos, siempre habra que haber un main	
		objetos = agregarObjeto(objetos, ":main:");

		//Prendemos la bandera de MAIN
		seccMain = 1;

		//Apagamos la bandera de Objeto
		seccObjeto = 0;
	}
		variables_globales declara_funciones implementa_funciones EJECUTARPROGRAMA
	{
		//Rellenamos el goto para que apuunte a ejecutar programa
		rellenarGoto();

		//LLenamos los datos a la tabla correspondiente
		strncpy(nombreProcedimiento, "ejecutarPrograma", tamanioIdentificadores);
		objetos = agregarFuncion(objetos, ":main:" ,nombreProcedimiento);

	} 
	ALLAVE variables_locales bloque CLLAVE
	{	
		//Desplegar mensaje de terminacion de compilacion
		printf("programa correctamente escrito\n");
	}
	;

variables_globales:
	VARIABLES_GLOBALES
	{
		//Prendemos la bandera de variablesGLobales
		seccVariablesGlobales=1;
	} 
	bloque_variables
	{
		//Al salir del bloque apagamos la bandera de variables globales
		seccVariablesGlobales=0;
	};

bloque_variables:
	ACORCHETE bloque_variables_rep CCORCHETE
	;

bloque_variables_rep:
	/* empty */
	| declara_variables 
	{	
		//Verificamos en que parte estamos
		if(seccMain == 1){
			//Estamos en el main
			//Checar la bandera de variables
			if(seccVariablesGlobales == 1){
				//Agregar a tabla de variables globales					
				objetos = agregarVariablesGlobales(objetos, ":main:" , nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;

			} else if(seccVariablesLocales == 1){	
				//Agregar a tabla de variables locales de la funcion
				objetos = agregarVariablesLocales(objetos, ":main:", nombreProcedimiento, nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;
			}
		} else if (seccObjeto == 1){
			//Estamos en un objeto
			if(seccVariablesGlobales == 1){
				//Agregar a tabla de variables globales					
				objetos = agregarVariablesGlobales(objetos, nombreObjeto, nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;

			} else if(seccVariablesLocales == 1){	
				//Agregar a tabla de variables locales de la funcion
				objetos = agregarVariablesLocales(objetos, nombreObjeto, nombreProcedimiento, nombreVariable, tipoVariable, direccionVariable);
				tipoVariable = -1;
			}
		}								
	} 
	bloque_variables_rep
	;

declara_variables:
	ENTERO IDENTIFICADOR PUNTOYCOMA
	{						
		tipoVariable = $1;
		strncpy(nombreVariable, $2, tamanioIdentificadores);
		asignarMemoriaVariable();
	}
	|
	DECIMAL IDENTIFICADOR PUNTOYCOMA
	{		
		tipoVariable = $1;
		strncpy(nombreVariable, $2, tamanioIdentificadores);
		asignarMemoriaVariable();
	}
	|
	TEXTO IDENTIFICADOR PUNTOYCOMA
	{		
		tipoVariable = $1;
		strncpy(nombreVariable, $2, tamanioIdentificadores);
		asignarMemoriaVariable();
	}
	|
	BOOLEANO IDENTIFICADOR PUNTOYCOMA
	{		
		tipoVariable = $1;
		strncpy(nombreVariable, $2, tamanioIdentificadores);
		asignarMemoriaVariable();
	}
	|
	MATRIZDECIMAL IDENTIFICADOR dimensiones PUNTOYCOMA
	{		
		//Pendiente
	}
	|
	MATRIZENTERA IDENTIFICADOR dimensiones PUNTOYCOMA
	{		
		//Pendiente
	}
	|
	CREAROBJETO IDENTIFICADOR ES IDENTIFICADOR PUNTOYCOMA
	{		
		//Pendiente
	}
	;

asignacion_matriz:
	ALLAVE asignacion_matriz_arreglo CLLAVE
	;

asignacion_matriz_arreglo:
	asignacion_matriz_valor PUNTOYCOMA asignacion_matriz_opcional
	;

asignacion_matriz_opcional:
	/*Empty*/
	| asignacion_matriz_arreglo
	;

asignacion_matriz_valor:
	CTEENTERA asignacion_matriz_valor1 
	| CTEDECIMAL asignacion_matriz_valor1
	;

asignacion_matriz_valor1:
	/*Empty*/
	| COMA asignacion_matriz_valor
	;

dimensiones:
	ACORCHETE serexpresion CCORCHETE dimensiones_rep
	;

dimensiones_rep:
	/*empty*/
	| ACORCHETE serexpresion CCORCHETE
	;

serexpresion: 
	expresion expresion_and_or
	;

expresion_and_or:
	/*empty*/
	| AMPERSAND 
	{
		//Creamos el nodo operandor que se le hara push en la pila operadores
		pushPilaOperadores(OP_AND);
	}
	serexpresion 
	{	
		//Generar cuadruplo logico
		generarAndOr();
	}
	| BARRA 
	{
		pushPilaOperadores(OP_OR);
	}
	serexpresion 
	{
		//Generar cuadruplo logico
		generarAndOr();
	}
	;

expresion:
	exp expresion_condicional
	;

expresion_condicional:
	/*empty*/
	| op_booleanos exp
	{
		//Aqui va la generacion del cuadruplo de checar
		generarRelacional();
	}
	;

op_booleanos:
	COMPARA 
	{
		pushPilaOperadores(OP_IGUAL);
	}
	| NEGACION 
	{
		pushPilaOperadores(OP_DIFERENTE);
	}
	| MAYORQUE 
	{
		pushPilaOperadores(OP_MAYORQUE);
	}
	| MENORQUE 
	{
		pushPilaOperadores(OP_MENORQUE);
	}
	| MAYORIGUAL 
	{
		pushPilaOperadores(OP_MAYORIGUAL);
	}
	| MENORIGUAL
	{
		pushPilaOperadores(OP_MENORIGUAL);
	} 
	;

exp:
	termino
	{

		generarSumaResta();	
	} 
	exp_suma_resta
	;

exp_suma_resta:
	/*Empty*/
	| MAS 
	{
		pushPilaOperadores(OP_SUMA);
	}
	exp 
	| MENOS 
	{
		pushPilaOperadores(OP_RESTA);
	}
	exp
	;

termino:
	factor
	{
		generarMultiplicacionDivision();
	} 
	termino_multi_divide
	;

termino_multi_divide:
	/*Empty*/
	| POR
	{
		pushPilaOperadores(OP_MULTIPLICACION);
	} 
	termino 
	| 
	ENTRE
	{
		pushPilaOperadores(OP_DIVISION);
	} 
	termino
	;

factor:
	APARENTESIS
	{
		pushPilaOperadores(OP_APARENTESIS);
	} 
	serexpresion CPARENTESIS
	{
		//Encontramos el cirre del parentesis lo sacamos de la pila
		pop(operadores);	
	} 
	| MAS factor_operando 
	| MENOS factor_operando 
	| factor_operando
	;

factor_operando:
	var_cte 	
	;

var_cte:
	CTEENTERA
	{
		//Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		agregarTablaConstantes(nombreVariable, 0);

		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	} 

	| CTEDECIMAL
	{
		//Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		agregarTablaConstantes(nombreVariable, 1);

		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	} 
	| CTETEXTO
	{
		//Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		agregarTablaConstantes(nombreVariable, 2);
		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	} 
	| CTEBOOLEANO
	{
		//Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);		
		agregarTablaConstantes(nombreVariable, 3);

		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	} 
	| identificadorOLlamadaAFuncion	
	;

identificadorOLlamadaAFuncion:
	IDENTIFICADOR 
	{
		//Obtenemos el nombre de la variable que desamos usar
		strncpy(nombreVariable, $1, tamanioIdentificadores);

		if(seccMain == 1){
			//Estamos en MAIN y la unica forma de hacer estatutos es dentro de funciones
			//Obtenemos los valores de las variables si no existen exit
			//variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			
			//La variable no se encontro
			if (variable == NULL) {
				//Si esta variable entonces la tomamos si no es asi marcaremos un error
				variable = buscarVariablesGlobales(objetos, ":main:", nombreVariable);
			}

			//crearemos un nodoOperando para agregarlo a la pila
			operando = (nodoOperando*)malloc(sizeof(nodoOperando));
			operando->temp = 0;
			operando->tipo = variable->tipo; 
			strcpy(operando->nombre, variable->nombre);
			operando->direccion = variable->direccion;

			push(operandos,operando);

		} else if (seccObjeto == 1) {
			//Estamos en la funcion de un objeto
			//Pendiente
		}
	}  
	opcionalFuncion
	;

opcionalFuncion:
	/*Empty*/
	| llama_funcion_opcional APARENTESIS serexpresion CPARENTESIS 
	;

declara_objetos:
	DECLARA_OBJETOS ACORCHETE declara_objetos_rep CCORCHETE;

declara_objetos_rep:
	/*Empty*/
	| objeto declara_objetos_rep
	;

objeto:
	CLASE IDENTIFICADOR objeto_herencia ALLAVE atributos_globales declara_funciones implementa_funciones CLLAVE;

objeto_herencia:
	/*Empty*/
	| HIJODE IDENTIFICADOR
	;

atributos_globales:
	ATRIBUTOS_GLOBALES bloque_variables
	;

declara_funciones:
	DECLARA_FUNCIONES ACORCHETE declara_funciones_rep CCORCHETE
	;

declara_funciones_rep:
	/*Empty*/
	| declaracion_prototipos declara_funciones_rep
	;

declaracion_prototipos:
	permiso IDENTIFICADOR 
	{
		//Checamos en que parte estamos
		if(seccMain == 1){
			//Estamos en MAIN
			strncpy(nombreProcedimiento, $2, tamanioIdentificadores);
			objetos = agregarFuncion(objetos, ":main:" ,nombreProcedimiento);
		} else if (seccObjeto == 1) {
			//Estams en objeto

		}
	}
	APARENTESIS parametros CPARENTESIS REGRESA declaracion_prototipos_regresa PUNTOYCOMA
	;

declaracion_prototipos_regresa:
	tipo 
	| NADA
	;

permiso:
	PRIVADA 
	| PUBLICA
	;

parametros:
	/*Empty*/
	| parametros_rep
	;

parametros_rep:
	IDENTIFICADOR 
	{
		//Actualizar el temporal con el nombre del parametro
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		
	}
	DOSPUNTOS tipo 
	{		
		//Agregar el parametro a la tabla de variables locales de la funcion	
		objetos = agregarVariablesLocales(objetos, ":main:", nombreProcedimiento, nombreVariable, tipoVariable,1);
	} 
	parametros_rep1
	;

parametros_rep1:
	/*Empty*/
	| COMA parametros_rep
	;

tipo:	
	ENTERO
	{

		tipoVariable=$1;
	}
	| DECIMAL 
	{
		
		tipoVariable=$1;
	}
	| BOOLEANO 
	{

		tipoVariable=$1;
	}
	| TEXTO 
	{

		tipoVariable=$1;
	}
	| MATRIZENTERA 
	{

		tipoVariable=$1;
	}
	| MATRIZDECIMAL
	{

		tipoVariable=$1;
	}
	;

implementa_funciones:
	IMPLEMENTA_FUNCIONES ACORCHETE implementa_funciones_rep CCORCHETE
	;

implementa_funciones_rep:
	/*Empty*/
	| funciones implementa_funciones_rep
	;

funciones:
	IDENTIFICADOR 
	{
		//Actualizar el temporal con el nombre de la funcion
		strncpy(nombreProcedimiento, $1, tamanioIdentificadores);
	} 
	APARENTESIS parametros CPARENTESIS ALLAVE variables_locales bloque CLLAVE
	;

variables_locales:
	VARIABLES_LOCALES 
	{
		//Prendemos la bandera de variablesGLobales
		seccVariablesLocales=1;	
	}
	bloque_variables
	{
		//Al salir del bloque apagamos la bandera de variables globales
		seccVariablesLocales=0;
	}
	;

bloque:
	/*Empty*/
	| estatuto bloque
	;

estatuto:
	decideEstatuto PUNTOYCOMA
	| escritura PUNTOYCOMA
	| regresa PUNTOYCOMA
	| lectura PUNTOYCOMA
	| condicional
	| ciclo
	;

decideEstatuto:
	IDENTIFICADOR 
	{
		//Obtenemos el nombre de la variable que desamos usar
		strncpy(nombreVariable, $1, tamanioIdentificadores);

		if(seccMain == 1){
			//Estamos en MAIN y la unica forma de hacer estatutos es dentro de funciones
			//Obtenemos los valores de las variables si no existen exit
			//variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			
			//La variable no se encontro
			if (variable == NULL) {
				//Si esta variable entonces la tomamos si no es asi marcaremos un error
				variable = buscarVariablesGlobales(objetos, ":main:", nombreVariable);
			}

			//crearemos un nodoOperando para agregarlo a la pila
			operando = (nodoOperando*)malloc(sizeof(nodoOperando));
			operando->temp = 0;
			operando->tipo = variable->tipo; 
			strcpy(operando->nombre, variable->nombre);
			operando->direccion = variable->direccion;

			push(operandos,operando);

		} else if (seccObjeto == 1) {
			//Estamos en la funcion de un objeto
			//Pendiente
		}
	}  
	estatutoOAsignacion
	;

estatutoOAsignacion:
	asignacion1 
	|
	llama_funcion_opcional APARENTESIS serexpresion CPARENTESIS
	;

llama_funcion_opcional:
	/*Empty*/
	| FLECHA IDENTIFICADOR
	;

asignacion1:
	dimensiones IGUAL serexpresion 
	| IGUAL
	{
		pushPilaOperadores(OP_ASIGNACION);
	} 
	asignacion2
	{
		//Funcion experimental solo funcionara con expresiones y id
		generarAsignacion();
	}
	| FLECHA IDENTIFICADOR asignacion3  IGUAL asignacion2;

asignacion2:
	asignacion_matriz 
	| serexpresion
	;

asignacion3:
	/*Empty*/
	| dimensiones
	;

lectura:
	LEERDELTECLADO
	{
		pushPilaOperadores(OP_LECTURA);
	}
 	APARENTESIS IDENTIFICADOR
	{
		//Obtenemos el nombre de la variable que desamos usar
		strncpy(nombreVariable, $4, tamanioIdentificadores);

		if(seccMain == 1){
			//Estamos en MAIN y la unica forma de hacer estatutos es dentro de funciones
			//Obtenemos los valores de las variables si no existen exit
			//variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			
			//La variable no se encontro
			if (variable == NULL) {
				//Si esta variable entonces la tomamos si no es asi marcaremos un error
				variable = buscarVariablesGlobales(objetos, ":main:", nombreVariable);
			}

			//crearemos un nodoOperando para agregarlo a la pila
			operando = (nodoOperando*)malloc(sizeof(nodoOperando));
			operando->temp = 0;
			operando->tipo = variable->tipo; 
			strcpy(operando->nombre, variable->nombre);
			operando->direccion = variable->direccion;

			push(operandos,operando);

		} else if (seccObjeto == 1) {
			//Estamos en la funcion de un objeto
			//Pendiente
		}
	}
	CPARENTESIS
	{

		generarLectura();
	}
	;
	
escritura:
	DESPLIEGA APARENTESIS 
	{
		pushPilaOperadores(OP_ESCRITURA);
	}
	escritura_valores CPARENTESIS 
	{
		generarEscritura();

		pushPilaOperadores(OP_ESCRITURA);
		
		//crearemos un nodoOperando para agregarlo a la pila DUMMY
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = -1;
		operando->tipo = -1; 
		strcpy(operando->nombre, "NuLl");
		operando->direccion = -1;
		push(operandos,operando);

		generarEscritura();
	}
	;

escritura_valores:
	valores escritura_concatena 
	| IDENTIFICADOR
	{
		//Obtenemos el nombre de la variable que desamos usar
		strncpy(nombreVariable, $1, tamanioIdentificadores);


		if(seccMain == 1){
			//Estamos en MAIN y la unica forma de hacer estatutos es dentro de funciones
			//Obtenemos los valores de las variables si no existen exit
			//variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			
			//La variable no se encontro
			if (variable == NULL) {
				//Si esta variable entonces la tomamos si no es asi marcaremos un error
				variable = buscarVariablesGlobales(objetos, ":main:", nombreVariable);
			}

			//crearemos un nodoOperando para agregarlo a la pila
			operando = (nodoOperando*)malloc(sizeof(nodoOperando));
			operando->temp = 0;
			operando->tipo = variable->tipo; 
			strcpy(operando->nombre, variable->nombre);
			operando->direccion = variable->direccion;

			push(operandos,operando);

		} else if (seccObjeto == 1) {
			//Estamos en la funcion de un objeto
			//Pendiente
		}	
	} escritura_valores1
	;

valores:
	CTEENTERA 
	{
	 	//Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		agregarTablaConstantes(nombreVariable, 0);

		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	}
	| CTEDECIMAL 
	{
	 //Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		agregarTablaConstantes(nombreVariable, 1);

		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	}
	| CTETEXTO
	{
	 	//Obtenemos el valor de la constante
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		agregarTablaConstantes(nombreVariable, 2);

		variable = buscarConstante(constantes, nombreVariable);

		//crearemos un nodoOperando para agregarlo a la pila
		operando = (nodoOperando*)malloc(sizeof(nodoOperando));
		operando->temp = 0;
		operando->tipo = variable->tipo; 
		strcpy(operando->nombre, variable->nombre);
		operando->direccion = variable->direccion;

		push(operandos,operando);
	 }
	 ;

escritura_valores1:
	/*Empty*/
	| CONCATENA
	{
		generarEscritura();

		pushPilaOperadores(OP_ESCRITURA);

	} escritura_valores 
	| dimensiones escritura_concatena
	;

escritura_concatena:
	/*Empty*/
	| CONCATENA 
	{
		generarEscritura();

		pushPilaOperadores(OP_ESCRITURA);
	}
	escritura_valores
	;


regresa:
	REGRESA serexpresion
	;


condicional:
	SI APARENTESIS serexpresion CPARENTESIS 
	{

	 	generarAccion1If();
	}
	ALLAVE bloque CLLAVE condicional_if
	{

		generarAccion3If();
	}
	;

condicional_if:
	/*Empty*/
	| SINO 
	{
		generarAccion2If();
	}
	ALLAVE bloque CLLAVE
	;

ciclo:
	MIENTRAS 
	{	
		//Metemos en la pila de saltos el contador actual
		salto = (nodoOperador*)malloc(sizeof(nodoOperador));
		salto->operador = contadorIndice;
		push(pilaSaltos, salto);
		
	}
	APARENTESIS serexpresion 
	{
		//Generamos el goto en falso para la expresion
		generarAccion1Ciclo();
	} 
	CPARENTESIS ALLAVE bloque CLLAVE 
	{	
		//Generamos el goto para regresar a evaluar la expresion
		generarAccion2Ciclo();
	}
	;