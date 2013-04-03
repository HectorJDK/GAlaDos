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
	#define YYERROR_VERBOSE 1
	
//----------------------------------------------------------------------------------------


void yyerror( const char *str )
{
	fprintf( stderr, "error: %s\n", str );
}


//Variables globales para la semantica-------------------------------------------------------

//Banderas
int error = 0;
int ejecutar = 0;
int variablesGlobales=0; //En seccion de variables globales	
int funcionesD=0;		//En seccion de declaracion de funciones
int funcionesI=0;		//En seccion de implementacion de funciones

//Globales
int id=1;
char *nombreV=NULL;
char *tipoV=NULL;
char *datoV="dato";
char *nombreP=NULL;
char *nombreO=NULL;

//Contadores para direcciones de memoria
int contadorIndiceCuadruplos = 0;
int contadorBooleanos = 0;
int contadorEntero = 0;
int contadorDecimal = 0;
int contadorTexto = 0;

//Temporales para tablas de procedimientos y variables
char tempObjetos[25];
char tempFunciones[25];
unsigned short tempTipos;
char tempVariable[25];

//Declaracion e inicializacion de la estructura objetos
directorioObjetos *objetos = NULL;

//----------------------------------------------------------------------------

int main()
{
	//Realizar escaneo de gramatica
	yyparse();
	
	//Desplegar la tabla de objetos	
	imprimirObjetos(objetos);

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
	//Agregar main a tabla de objetos	
	objetos = agregarObjeto(objetos, "main");	
	}
	declara_objetos variables_globales declara_funciones implementa_funciones EJECUTARPROGRAMA 
	{
		//Actualizar la posicion a ejecutarPrograma
		ejecutar = 1;
	} ALLAVE variables_locales bloque CLLAVE
	{	
		//Desplegar mensaje de terminacion de compilacion
		printf("programa correctamente escrito\n");		
	}
	;

variables_globales:
	VARIABLES_GLOBALES
	{
		variablesGlobales=1;			
	} 
	bloque_variables
	{
		variablesGlobales=0;		
	};

bloque_variables:
	ACORCHETE bloque_variables_rep CCORCHETE
	;

bloque_variables_rep:
	/* empty */
	| declara_variables 
	{		
			//Checar la bandera de posicion
			if(variablesGlobales == 1){
				//Agregar a tabla de variables globales					
				 objetos = agregarVariablesGlobales(objetos, "main" ,nombreV, tempTipos, 15);
				 tempTipos=-1;
			} else 
			if(funcionesI == 1){	
				//Agregar a tabla de variables locales de la funcion
				objetos = agregarVariablesLocales(objetos, "main", tempFunciones, nombreV, tempTipos,1);	
 				tempTipos=-1;
			}								
	} bloque_variables_rep
	;

declara_variables:
	ENTERO IDENTIFICADOR declara_variables_atomica
	{				
		nombreV = $2;
		tempTipos=$1;		
	}
	|
	DECIMAL IDENTIFICADOR declara_variables_atomica
	{		
		nombreV = $2;
		tempTipos=$1;		
	}
	|
	TEXTO IDENTIFICADOR declara_variables_atomica
	{		
		nombreV = $2;
		tempTipos=$1;		
	}
	|
	BOOLEANO IDENTIFICADOR declara_variables_atomica
	{		
		nombreV = $2;
		tempTipos=$1;		
	}
	|
	MATRIZDECIMAL IDENTIFICADOR dimensiones declara_variables_matriz
	{		
		nombreV = $2;
		tempTipos=$1;		
	}
	|
	MATRIZENTERA IDENTIFICADOR dimensiones declara_variables_matriz
	{		
		nombreV = $2;
		tempTipos=$1;		
	}
	|
	CREAROBJETO IDENTIFICADOR declara_variables_objeto
	{		
		nombreV = $2;	
	}
	;	

declara_variables_atomica:
	PUNTOYCOMA
	|IGUAL serexpresion PUNTOYCOMA
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
	termino exp_suma_resta
	;

exp_suma_resta:
	/*Empty*/
	| MAS exp 
	| MENOS exp
	;

termino:
	factor termino_multi_divide
	;

termino_multi_divide:
	/*Empty*/
	| POR termino 
	| ENTRE termino
	;

factor:
	APARENTESIS serexpresion CPARENTESIS 
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
	DECLARA_FUNCIONES 
	{	
		//Cambiar la posicion a declaracion de funciones
		funcionesD = 1;
	} 
	ACORCHETE declara_funciones_rep CCORCHETE
	{
		//Termina la posicion de declaracion de funciones
		funcionesD=0;
	}
	;

declara_funciones_rep:
	/*Empty*/
	| declaracion_prototipos declara_funciones_rep
	;

declaracion_prototipos:
	permiso IDENTIFICADOR 
	{
		//Agregar la funcion al objeto main y guardar el nombre en temporal
		if(funcionesD == 1){				
			objetos = agregarFuncion(objetos, "main" ,$2);
			strncpy(tempFunciones, $2, strlen($2));						
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
		strncpy(tempVariable, $1, strlen($1));		
		
	}
	DOSPUNTOS tipo 
	{		
		//Agregar el parametro a la tabla de variables locales de la funcion	
		objetos = agregarVariablesLocales(objetos, "main", tempFunciones, tempVariable, tempTipos,1);	
	} 
	parametros_rep1
	;

tipo:	
	ENTERO
	{
		tempTipos=$1;		
	}
	| DECIMAL 
	{
		
		tempTipos=$1;
	}
	| BOOLEANO 
	{
		tempTipos=$1;
	}
	| TEXTO 
	{
		tempTipos=$1;
	}
	| MATRIZENTERA 
	{
		tempTipos=$1;
	}
	| MATRIZDECIMAL
	{
		tempTipos=$1;
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
	IMPLEMENTA_FUNCIONES
	{
		//Cambiar la posicion a implementacion de funciones
		funcionesI=1;
	} ACORCHETE implementa_funciones_rep CCORCHETE
	{
		//Termina la posicion de implementacion de funciones
		funcionesI = 0;
	}
	;

implementa_funciones_rep:
	/*Empty*/
	| funciones implementa_funciones_rep
	;

funciones:
	IDENTIFICADOR 
	{
		//Actualizar el temporal con el nombre de la funcion
		strncpy(tempFunciones, $1, strlen($1));
	} 
	APARENTESIS parametros CPARENTESIS ALLAVE variables_locales bloque CLLAVE
	;

variables_locales:
	VARIABLES_LOCALES bloque_variables
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