//Ejemplo basico para la estructura del cubo semantico
//Codigo de operaciones
/*
	Primeras dos entradas del cubo son los operadores
	1 = TIPO_ENTERO
	2 = Decimal
	3 = Texto
	4 = Booleano

	Ultima entrada del cubo definira la operacion
	---------------Operadores Aritmeticos
	1 = OP_SUMA
	2 = OP_Resta
	3 = OP_Division
	4 = OP_Multiplicacion
	---------------Operadores booleanos
	5 = OP_mayorque >
	6 = OP_menorque >
	7 = OP_mayorIgual >=
	8 = OP_menorIgual <=
	9 = igual ==
	10 = diferente ¬¬
	---------------Operadores logicos
	11 = and &
	12 = or |
	---------------Operador de asignacion
	13 = asignacion =
	---------------Operadores especiales
	14 = concatena <<

*/

#include "utilerias.h"
#include <stdio.h>

void inicializarSemantica(int cuboSemantico[4][4][14]){
	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion TIPO_ENTERO op1
	//Operaciones Op1: TIPO_ENTERO, Op2:TIPO_ENTERO
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_SUMA] = TIPO_ENTERO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_RESTA] = TIPO_ENTERO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_DIVISION] = TIPO_ENTERO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_MULTIPLICACION] = TIPO_ENTERO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_MAYORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_MENORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_MAYORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_MENORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_IGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_DIFERENTE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_ASIGNACION] = TIPO_ENTERO;
	cuboSemantico[TIPO_ENTERO][TIPO_ENTERO][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: TIPO_ENTERO, Op2:TIPO_DECIMAL
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_SUMA] = TIPO_DECIMAL;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_RESTA] = TIPO_DECIMAL;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_DIVISION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_MULTIPLICACION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_MAYORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_MENORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_MAYORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_MENORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_IGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_DIFERENTE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_ASIGNACION] = TIPO_ENTERO;
	cuboSemantico[TIPO_ENTERO][TIPO_DECIMAL][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: TIPO_ENTERO, Op2:TIPO_TEXTO
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_TEXTO][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: TIPO_ENTERO, Op2:TIPO_BOOLEANO
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_ENTERO][TIPO_BOOLEANO][OP_CONCATENA] = OP_ERROR;

	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion TIPO_DECIMAL op1
	
	//Operaciones Op1: Decimal, Op2:TIPO_ENTERO
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_SUMA] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_RESTA] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_DIVISION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_MULTIPLICACION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_MAYORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_MENORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_MAYORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_MENORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_IGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_DIFERENTE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_ASIGNACION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_ENTERO][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: Decimal, Op2:TIPO_DECIMAL
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_SUMA] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_RESTA] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_DIVISION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_MULTIPLICACION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_MAYORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_MENORQUE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_MAYORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_MENORIGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_IGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_DIFERENTE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_ASIGNACION] = TIPO_DECIMAL;
	cuboSemantico[TIPO_DECIMAL][TIPO_DECIMAL][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: Decimal, Op2:TIPO_TEXTO
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_TEXTO][OP_CONCATENA] = -1;

	//Operaciones Op1: Decimal, Op2:TIPO_BOOLEANO
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_DECIMAL][TIPO_BOOLEANO][OP_CONCATENA] = OP_ERROR;

	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion TIPO_TEXTO op1
	
	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_ENTERO
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_ENTERO][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_DECIMAL
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_DECIMAL][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_TEXTO
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_IGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_DIFERENTE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_ASIGNACION] = TIPO_TEXTO;
	cuboSemantico[TIPO_TEXTO][TIPO_TEXTO][OP_CONCATENA] = TIPO_TEXTO;

	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_BOOLEANO
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_TEXTO][TIPO_BOOLEANO][OP_CONCATENA] = OP_ERROR;

	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion TIPO_BOOLEANO op1
	
	//Operaciones Op1: TIPO_BOOLEANO, Op2:TIPO_ENTERO
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_ENTERO][OP_CONCATENA] = OP_ERROR;

	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_DECIMAL
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_DECIMAL][OP_CONCATENA] = OP_ERROR;

	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_TEXTO
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_IGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_DIFERENTE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_AND] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_OR] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_ASIGNACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_TEXTO][OP_CONCATENA] = OP_ERROR;

	//Operaciones Op1: TIPO_TEXTO, Op2:TIPO_BOOLEANO
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_SUMA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_RESTA] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_DIVISION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_MULTIPLICACION] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_MAYORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_MENORQUE] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_MAYORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_MENORIGUAL] = OP_ERROR;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_IGUAL] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_DIFERENTE] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_AND] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_OR] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_ASIGNACION] = TIPO_BOOLEANO;
	cuboSemantico[TIPO_BOOLEANO][TIPO_BOOLEANO][OP_CONCATENA] = OP_ERROR;
}


void inicializarAvail(pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean,int *memoriaEnteroTemp, int *memoriaDecimalTemp, int *memoriaTextoTemp, int *memoriaBooleanoTemp){
	//Inicializacion del ciclo (for)
	int repeticion= 0;

	//Inicializacion de los nodos con sus tipos de nodos
	nodoOperando *datoEntero;
	nodoOperando *datoDecimal;
	nodoOperando *datoTexto;
	nodoOperando *datoBooleano;

	//Creacion de los nodos con todos sus datos 
	for(repeticion = 999; repeticion >= 0; repeticion--) {

		//Creacion de los nodos enteros
		datoEntero = (nodoOperando*)malloc(sizeof(nodoOperando));
		datoEntero->temp = 1;
		datoEntero->tipo = 0;
		sprintf(datoEntero->nombre, "tempInt_%d", *memoriaEnteroTemp - repeticion);
		datoEntero->direccion = *memoriaEnteroTemp + repeticion;

		//Creacion de los nodos Decimal
		datoDecimal = (nodoOperando*)malloc(sizeof(nodoOperando));
		datoDecimal->temp = 1;
		datoDecimal->tipo = 1;
		sprintf(datoDecimal->nombre, "tempDec_%d", *memoriaDecimalTemp - repeticion);
		datoDecimal->direccion = *memoriaDecimalTemp + repeticion;

		//Creacion de los nodos Texto
		datoTexto = (nodoOperando*)malloc(sizeof(nodoOperando));
		datoTexto->temp = 1;
		datoTexto->tipo = 2;
		sprintf(datoTexto->nombre, "tempText_%d", *memoriaTextoTemp - repeticion);
		datoTexto->direccion = *memoriaTextoTemp + repeticion;

		//Creacion de los nodos Booleano
		datoBooleano = (nodoOperando*)malloc(sizeof(nodoOperando));
		datoBooleano->temp = 1;
		datoBooleano->tipo = 3;
		sprintf(datoBooleano->nombre, "tempBool_%d", *memoriaBooleanoTemp - repeticion);
		datoBooleano->direccion = *memoriaBooleanoTemp + repeticion;

		//Metemos en las pilas
		push(availEntero, datoEntero);
		push(availDecimal, datoDecimal);
		push(availTexto, datoTexto);
		push(availBoolean, datoBooleano);
	}    
}