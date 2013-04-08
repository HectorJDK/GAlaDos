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
	#include "cuadruplos.h"
	#include "pilas.h"
	#include "utilerias.h"
	#define YYERROR_VERBOSE 1
	
//----------------------------------------------------------------------------------------


void yyerror( const char *str )
{
	fprintf( stderr, "error: %s\n", str );
}

//Globales miscelaneas de Control
int tamanioIdentificadores = 25;

//Banderas
int error = 0;

//Varialbes para el manejo de las secciones
int seccVariablesGlobales = 0;
int seccVariablesLocales = 0;
int seccFuncionesImplementacion = 0;
int seccObjeto = 0;
int seccMain = 0;

//Variables para la creacion de variables en la tabla
char nombreVariable[25];
unsigned short tipoVariable;
char nombreProcedimiento[25];
char nombreObjeto[25];
int direccionVariable;

//Pilas Operandos
pila *operandos;
pila *operadores;

//Pilas Avail
pila *availEntero;
pila *availDecimal;
pila *availTexto;
pila *availBoolean;

//Contador de cuadruplos
int contadorIndice = 0;

//Variables para control
nodoOperando *operando;
nodoOperador *operador;
directorio *variable;

//Variables para control de memoria
int cantidadVariablesTemp = 1000;
int cantidadVariablesLocal = 1000;
int cantidadVariablesGlobal = 1000;

//Direcciones base para memoria
int baseMemoriaTemp = 10000;
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
//Temporales
//De la 10,000 hasta la 13,999
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


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void  generarMultiplicacionDivision(){
	listaCuadruplos = verificacionGeneracionCuadruplo(1 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarSumaResta(){
	listaCuadruplos = verificacionGeneracionCuadruplo(2 , listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarRelacional(){
	listaCuadruplos = verificacionGeneracionCuadruplo(3, listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
}

void  generarAndOr(){
	listaCuadruplos = verificacionGeneracionCuadruplo(4, listaCuadruplos, operandos, operadores, cuboSemantico, &contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
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
	
void calcularMemoriaVirtual(){
	memoriaEnteroTemp = baseMemoriaTemp + (cantidadVariablesTemp * 0);
	memoriaDecimalTemp = baseMemoriaTemp + (cantidadVariablesTemp * 1);
	memoriaTextoTemp = baseMemoriaTemp + (cantidadVariablesTemp * 2);
	memoriaBooleanoTemp = baseMemoriaTemp + (cantidadVariablesTemp * 3);
	memoriaEnteroLocal = baseMemoriaLocal + (cantidadVariablesLocal * 0);
	memoriaDecimalLocal = baseMemoriaLocal + (cantidadVariablesLocal * 1);
	memoriaTextoLocal =	baseMemoriaLocal + (cantidadVariablesLocal * 2);
	memoriaBooleanoLocal = baseMemoriaLocal + (cantidadVariablesLocal * 3);
	memoriaEnteroGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 0);
	memoriaDecimalGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 1);
	memoriaTextoGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 2);
	memoriaBooleanoGlobal = baseMemoriaGlobal + (cantidadVariablesGlobal * 3);
}


//----------------------------------------------------------------------------


//----------------------------------MAIN--------------------------------------

int main()
{

	yyparse();
	//Imprimir tabla de variables y procedimientos
	//imprimirObjetos(objetos); 
	//Imprimir cuadruplos
	//imprimeCuadruplos(listaCuadruplos, 0);
	//Imprimir cuadruplos version verbose
	//imprimeCuadruplos(listaCuadruplos, 1);								
	//Desplegar la tabla de objetos
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
%token CTEENTERA
%token CTETEXTO
%token CTEBOOLEANO
%token CTEDECIMAL
%token <sval> IDENTIFICADOR
%start programa
%%

programa:
	{
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

		//Inicializacion del Avial
		inicializarAvail(availEntero, availDecimal, availTexto, availBoolean, &memoriaEnteroTemp, &memoriaDecimalTemp, &memoriaTextoTemp, &memoriaBooleanoTemp);

		//Inicializacion del CuboSemantico
		inicializarSemantica(cuboSemantico);
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
		strncpy(nombreProcedimiento, "ejecutarProgama", tamanioIdentificadores);
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
	MATRIZDECIMAL IDENTIFICADOR dimensiones declara_variables_matriz
	{		
		//Pendiente
	}
	|
	MATRIZENTERA IDENTIFICADOR dimensiones declara_variables_matriz
	{		
		//Pendiente
	}
	|
	CREAROBJETO IDENTIFICADOR declara_variables_objeto
	{		
		//Pendiente
	}
	;

declara_variables_matriz:
	PUNTOYCOMA
	| IGUAL declara_variables_matriz1 PUNTOYCOMA
	;

declara_variables_matriz1:
	asignacion_matriz 
	| IDENTIFICADOR
	;

declara_variables_objeto:
	PUNTOYCOMA
	| ES IDENTIFICADOR PUNTOYCOMA
	;

asignacion_matriz:
	ALLAVE asignacion_matriz_rep CLLAVE
	;

asignacion_matriz_rep:
	/*Empty*/
	| asignacion_matriz_valor PUNTOYCOMA asignacion_matriz_rep;

asignacion_matriz_valor:
	CTEENTERA asignacion_matriz_valor1 
	| CTEDECIMAL asignacion_matriz_valor1
	;

asignacion_matriz_valor1:
	/*Empty*/
	| COMA asignacion_matriz_valor
	;

dimensiones:
	ACORCHETE exp CCORCHETE dimensiones_rep
	;

dimensiones_rep:
	/*empty*/
	| ACORCHETE exp CCORCHETE
	;

serexpresion: 
	expresion expresion_and_or
	;

expresion_and_or:
	/*empty*/
	| AMPERSAND serexpresion
	| BARRA serexpresion
	;

expresion:
	exp expresion_condicional
	;

expresion_condicional:
	/*empty*/
	| op_booleanos exp
	;

op_booleanos:
	COMPARA 
	| NEGACION 
	| MAYORQUE 
	| MENORQUE 
	| MAYORIGUAL 
	| MENORIGUAL 
	;

exp:
	termino
	{
		generarSumaResta();	
	} exp_suma_resta
	;

exp_suma_resta:
	/*Empty*/
	| MAS 
	{
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_SUMA;
		
		//Metemos la multiplicacion en la pila de operadores
		push(operadores, operador);
	}
	exp 
	| MENOS 
	{
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_RESTA;
		
		//Metemos la multiplicacion en la pila de operadores
		push(operadores, operador);
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
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_MULTIPLICACION;
		
		//Metemos la multiplicacion en la pila de operadores
		push(operadores, operador);
	} 
	termino 
	| 
	ENTRE
	{
		//Creamos el nodo operandor que se le hara push en la pila operadores
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_DIVISION;
		
		//Metemos la division en la pila de operadores
		push(operadores, operador);
	} 
	termino
	;

factor:
	APARENTESIS
	{
		//Creacion del nodo para meterlo en la pila
		operador = (nodoOperador*)malloc(sizeof(nodoOperador));
		operador->operador = OP_APARENTESIS;

		//Si encontramos un parentesis debemos meterlo como fondo falso
		push(operadores, operador);
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
	| llama_funcion
	;

var_cte:
	CTEENTERA 
	| CTEDECIMAL 
	| CTEBOOLEANO 
	| CTETEXTO 
	| IDENTIFICADOR
	{			
		//Obtenemos el nombre de la variable que desamos usar
		strncpy(nombreVariable, $1, tamanioIdentificadores);
		if(seccMain == 1){
			//Estamos en MAIN y la unica forma de hacer estatutos es dentro de funciones
			//Obtenemos los valores de las variables si no existen exit
			//variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
			variable = buscarVariablesLocales(objetos, ":main:", nombreProcedimiento,  nombreVariable);
		
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

parametros_rep1:
	| COMA parametros_rep
	;

declaracion_prototipos_regresa:
	tipo 
	| NADA
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
	asignacion PUNTOYCOMA
	| escritura PUNTOYCOMA
	| llama_funcion PUNTOYCOMA
	| regresa PUNTOYCOMA
	| condicional
	| ciclo
	;

asignacion:
	IDENTIFICADOR asignacion1
	;

asignacion1:
	dimensiones IGUAL serexpresion 
	| IGUAL asignacion2
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
	LEERDELTECLADO APARENTESIS lectura1 CPARENTESIS
	;
	
lectura1:
	ENTERO | DECIMAL | BOOLEANO | TEXTO
	;
	
escritura:
	DESPLIEGA APARENTESIS escritura_valores CPARENTESIS 
	;

escritura_valores:
	valores escritura_concatena 
	| IDENTIFICADOR escritura_valores1
	;

valores:
	 CTEENTERA 
	 | CTEDECIMAL 
	 | CTETEXTO
	 ;

escritura_valores1:
	/*Empty*/
	| CONCATENA escritura_valores 
	| dimensiones escritura_concatena
	;

escritura_concatena:
	/*Emty*/
	| CONCATENA escritura_valores
	;


llama_funcion:
	IDENTIFICADOR llama_funcion_opcional APARENTESIS serexpresion CPARENTESIS
	| lectura
	;

llama_funcion_opcional:
	/*Empty*/
	| FLECHA IDENTIFICADOR
	;

regresa:
	REGRESA serexpresion
	;


condicional:
	SI APARENTESIS serexpresion CPARENTESIS ALLAVE bloque CLLAVE condicional_ifelse
	;

condicional_ifelse:
	/*Empty*/
	| SINO condicional_else
	;

condicional_else:
	ENTONCES APARENTESIS serexpresion CPARENTESIS ALLAVE bloque CLLAVE condicional_ifelse 
	| ALLAVE bloque CLLAVE
	;

ciclo:
	MIENTRAS APARENTESIS serexpresion CPARENTESIS ALLAVE bloque CLLAVE
	;