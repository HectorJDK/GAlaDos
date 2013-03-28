//Ejemplo basico para la estructura del cubo semantico
//Codigo de operaciones
/*
	Primeras dos entradas del cubo son los operadores
	1 = Entero
	2 = Decimal
	3 = Texto
	4 = Booleano

	Ultima entrada del cubo definira la operacion
	---------------Operadores Aritmeticos
	1 = Suma
	2 = Resta
	3 = Division
	4 = Multiplicacion
	---------------Operadores booleanos
	5 = mayorque >
	6 = menorque >
	7 = mayorIgual >=
	8 = menorIgual <=
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

#include "cuboSemantico.h"


void inicializarSemantica(int cuboSemantico[4][4][14]){
	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion Entero op1
	//Operaciones Op1: Entero, Op2:Entero
	cuboSemantico[ENTERO][ENTERO][SUMA] = ENTERO;
	cuboSemantico[ENTERO][ENTERO][RESTA] = ENTERO;
	cuboSemantico[ENTERO][ENTERO][DIVISION] = ENTERO;
	cuboSemantico[ENTERO][ENTERO][MULTIPLICACION] = ENTERO;
	cuboSemantico[ENTERO][ENTERO][MAYORQUE] = BOOLEANO;
	cuboSemantico[ENTERO][ENTERO][MENORQUE] = BOOLEANO;
	cuboSemantico[ENTERO][ENTERO][MAYORIGUAL] = BOOLEANO;
	cuboSemantico[ENTERO][ENTERO][MENORIGUAL] = BOOLEANO;
	cuboSemantico[ENTERO][ENTERO][IGUAL] = BOOLEANO;
	cuboSemantico[ENTERO][ENTERO][DIFERENTE] = BOOLEANO;
	cuboSemantico[ENTERO][ENTERO][AND] = ERROR;
	cuboSemantico[ENTERO][ENTERO][OR] = ERROR;
	cuboSemantico[ENTERO][ENTERO][ASIGNACION] = ENTERO;
	cuboSemantico[ENTERO][ENTERO][CONCATENA] = TEXTO;

	//Operaciones Op1: Entero, Op2:DECIMAL
	cuboSemantico[ENTERO][DECIMAL][SUMA] = DECIMAL;
	cuboSemantico[ENTERO][DECIMAL][RESTA] = DECIMAL;
	cuboSemantico[ENTERO][DECIMAL][DIVISION] = DECIMAL;
	cuboSemantico[ENTERO][DECIMAL][MULTIPLICACION] = DECIMAL;
	cuboSemantico[ENTERO][DECIMAL][MAYORQUE] = BOOLEANO;
	cuboSemantico[ENTERO][DECIMAL][MENORQUE] = BOOLEANO;
	cuboSemantico[ENTERO][DECIMAL][MAYORIGUAL] = BOOLEANO;
	cuboSemantico[ENTERO][DECIMAL][MENORIGUAL] = BOOLEANO;
	cuboSemantico[ENTERO][DECIMAL][IGUAL] = BOOLEANO;
	cuboSemantico[ENTERO][DECIMAL][DIFERENTE] = BOOLEANO;
	cuboSemantico[ENTERO][DECIMAL][AND] = ERROR;
	cuboSemantico[ENTERO][DECIMAL][OR] = ERROR;
	cuboSemantico[ENTERO][DECIMAL][ASIGNACION] = ENTERO;
	cuboSemantico[ENTERO][DECIMAL][CONCATENA] = TEXTO;

	//Operaciones Op1: Entero, Op2:TEXTO
	cuboSemantico[ENTERO][TEXTO][SUMA] = ERROR;
	cuboSemantico[ENTERO][TEXTO][RESTA] = ERROR;
	cuboSemantico[ENTERO][TEXTO][DIVISION] = ERROR;
	cuboSemantico[ENTERO][TEXTO][MULTIPLICACION] = ERROR;
	cuboSemantico[ENTERO][TEXTO][MAYORQUE] = ERROR;
	cuboSemantico[ENTERO][TEXTO][MENORQUE] = ERROR;
	cuboSemantico[ENTERO][TEXTO][MAYORIGUAL] = ERROR;
	cuboSemantico[ENTERO][TEXTO][MENORIGUAL] = ERROR;
	cuboSemantico[ENTERO][TEXTO][IGUAL] = ERROR;
	cuboSemantico[ENTERO][TEXTO][DIFERENTE] = ERROR;
	cuboSemantico[ENTERO][TEXTO][AND] = ERROR;
	cuboSemantico[ENTERO][TEXTO][OR] = ERROR;
	cuboSemantico[ENTERO][TEXTO][ASIGNACION] = ERROR;
	cuboSemantico[ENTERO][TEXTO][CONCATENA] = TEXTO;

	//Operaciones Op1: Entero, Op2:BOOLEANO
	cuboSemantico[ENTERO][BOOLEANO][SUMA] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][RESTA] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][DIVISION] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][MULTIPLICACION] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][MAYORQUE] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][MENORQUE] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][MAYORIGUAL] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][MENORIGUAL] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][IGUAL] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][DIFERENTE] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][AND] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][OR] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][ASIGNACION] = ERROR;
	cuboSemantico[ENTERO][BOOLEANO][CONCATENA] = ERROR;

	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion DECIMAL op1
	
	//Operaciones Op1: Decimal, Op2:Entero
	cuboSemantico[DECIMAL][ENTERO][SUMA] = DECIMAL;
	cuboSemantico[DECIMAL][ENTERO][RESTA] = DECIMAL;
	cuboSemantico[DECIMAL][ENTERO][DIVISION] = DECIMAL;
	cuboSemantico[DECIMAL][ENTERO][MULTIPLICACION] = DECIMAL;
	cuboSemantico[DECIMAL][ENTERO][MAYORQUE] = BOOLEANO;
	cuboSemantico[DECIMAL][ENTERO][MENORQUE] = BOOLEANO;
	cuboSemantico[DECIMAL][ENTERO][MAYORIGUAL] = BOOLEANO;
	cuboSemantico[DECIMAL][ENTERO][MENORIGUAL] = BOOLEANO;
	cuboSemantico[DECIMAL][ENTERO][IGUAL] = BOOLEANO;
	cuboSemantico[DECIMAL][ENTERO][DIFERENTE] = BOOLEANO;
	cuboSemantico[DECIMAL][ENTERO][AND] = ERROR;
	cuboSemantico[DECIMAL][ENTERO][OR] = ERROR;
	cuboSemantico[DECIMAL][ENTERO][ASIGNACION] = DECIMAL;
	cuboSemantico[DECIMAL][ENTERO][CONCATENA] = TEXTO;

	//Operaciones Op1: Decimal, Op2:DECIMAL
	cuboSemantico[DECIMAL][DECIMAL][SUMA] = DECIMAL;
	cuboSemantico[DECIMAL][DECIMAL][RESTA] = DECIMAL;
	cuboSemantico[DECIMAL][DECIMAL][DIVISION] = DECIMAL;
	cuboSemantico[DECIMAL][DECIMAL][MULTIPLICACION] = DECIMAL;
	cuboSemantico[DECIMAL][DECIMAL][MAYORQUE] = BOOLEANO;
	cuboSemantico[DECIMAL][DECIMAL][MENORQUE] = BOOLEANO;
	cuboSemantico[DECIMAL][DECIMAL][MAYORIGUAL] = BOOLEANO;
	cuboSemantico[DECIMAL][DECIMAL][MENORIGUAL] = BOOLEANO;
	cuboSemantico[DECIMAL][DECIMAL][IGUAL] = BOOLEANO;
	cuboSemantico[DECIMAL][DECIMAL][DIFERENTE] = BOOLEANO;
	cuboSemantico[DECIMAL][DECIMAL][AND] = ERROR;
	cuboSemantico[DECIMAL][DECIMAL][OR] = ERROR;
	cuboSemantico[DECIMAL][DECIMAL][ASIGNACION] = DECIMAL;
	cuboSemantico[DECIMAL][DECIMAL][CONCATENA] = TEXTO;

	//Operaciones Op1: Decimal, Op2:TEXTO
	cuboSemantico[DECIMAL][TEXTO][SUMA] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][RESTA] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][DIVISION] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][MULTIPLICACION] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][MAYORQUE] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][MENORQUE] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][MAYORIGUAL] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][MENORIGUAL] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][IGUAL] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][DIFERENTE] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][AND] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][OR] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][ASIGNACION] = ERROR;
	cuboSemantico[DECIMAL][TEXTO][CONCATENA] = -1;

	//Operaciones Op1: Decimal, Op2:BOOLEANO
	cuboSemantico[DECIMAL][BOOLEANO][SUMA] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][RESTA] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][DIVISION] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][MULTIPLICACION] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][MAYORQUE] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][MENORQUE] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][MAYORIGUAL] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][MENORIGUAL] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][IGUAL] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][DIFERENTE] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][AND] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][OR] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][ASIGNACION] = ERROR;
	cuboSemantico[DECIMAL][BOOLEANO][CONCATENA] = ERROR;

	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion TEXTO op1
	
	//Operaciones Op1: TEXTO, Op2:Entero
	cuboSemantico[TEXTO][ENTERO][SUMA] = ERROR;
	cuboSemantico[TEXTO][ENTERO][RESTA] = ERROR;
	cuboSemantico[TEXTO][ENTERO][DIVISION] = ERROR;
	cuboSemantico[TEXTO][ENTERO][MULTIPLICACION] = ERROR;
	cuboSemantico[TEXTO][ENTERO][MAYORQUE] = ERROR;
	cuboSemantico[TEXTO][ENTERO][MENORQUE] = ERROR;
	cuboSemantico[TEXTO][ENTERO][MAYORIGUAL] = ERROR;
	cuboSemantico[TEXTO][ENTERO][MENORIGUAL] = ERROR;
	cuboSemantico[TEXTO][ENTERO][IGUAL] = ERROR;
	cuboSemantico[TEXTO][ENTERO][DIFERENTE] = ERROR;
	cuboSemantico[TEXTO][ENTERO][AND] = ERROR;
	cuboSemantico[TEXTO][ENTERO][OR] = ERROR;
	cuboSemantico[TEXTO][ENTERO][ASIGNACION] = ERROR;
	cuboSemantico[TEXTO][ENTERO][CONCATENA] = TEXTO;

	//Operaciones Op1: TEXTO, Op2:DECIMAL
	cuboSemantico[TEXTO][DECIMAL][SUMA] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][RESTA] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][DIVISION] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][MULTIPLICACION] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][MAYORQUE] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][MENORQUE] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][MAYORIGUAL] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][MENORIGUAL] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][IGUAL] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][DIFERENTE] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][AND] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][OR] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][ASIGNACION] = ERROR;
	cuboSemantico[TEXTO][DECIMAL][CONCATENA] = TEXTO;

	//Operaciones Op1: TEXTO, Op2:TEXTO
	cuboSemantico[TEXTO][TEXTO][SUMA] = ERROR;
	cuboSemantico[TEXTO][TEXTO][RESTA] = ERROR;
	cuboSemantico[TEXTO][TEXTO][DIVISION] = ERROR;
	cuboSemantico[TEXTO][TEXTO][MULTIPLICACION] = ERROR;
	cuboSemantico[TEXTO][TEXTO][MAYORQUE] = ERROR;
	cuboSemantico[TEXTO][TEXTO][MENORQUE] = ERROR;
	cuboSemantico[TEXTO][TEXTO][MAYORIGUAL] = ERROR;
	cuboSemantico[TEXTO][TEXTO][MENORIGUAL] = ERROR;
	cuboSemantico[TEXTO][TEXTO][IGUAL] = BOOLEANO;
	cuboSemantico[TEXTO][TEXTO][DIFERENTE] = BOOLEANO;
	cuboSemantico[TEXTO][TEXTO][AND] = ERROR;
	cuboSemantico[TEXTO][TEXTO][OR] = ERROR;
	cuboSemantico[TEXTO][TEXTO][ASIGNACION] = ERROR;
	cuboSemantico[TEXTO][TEXTO][CONCATENA] = TEXTO;

	//Operaciones Op1: TEXTO, Op2:BOOLEANO
	cuboSemantico[TEXTO][BOOLEANO][SUMA] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][RESTA] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][DIVISION] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][MULTIPLICACION] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][MAYORQUE] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][MENORQUE] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][MAYORIGUAL] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][MENORIGUAL] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][IGUAL] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][DIFERENTE] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][AND] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][OR] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][ASIGNACION] = ERROR;
	cuboSemantico[TEXTO][BOOLEANO][CONCATENA] = ERROR;

	//************************************************************************************************************
	//************************************************************************************************************
	//************************************************************************************************************
	//Seccion BOOLEANO op1
	
	//Operaciones Op1: BOOLEANO, Op2:Entero
	cuboSemantico[BOOLEANO][ENTERO][SUMA] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][RESTA] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][DIVISION] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][MULTIPLICACION] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][MAYORQUE] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][MENORQUE] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][MAYORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][MENORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][IGUAL] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][DIFERENTE] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][AND] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][OR] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][ASIGNACION] = ERROR;
	cuboSemantico[BOOLEANO][ENTERO][CONCATENA] = ERROR;

	//Operaciones Op1: TEXTO, Op2:DECIMAL
	cuboSemantico[BOOLEANO][DECIMAL][SUMA] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][RESTA] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][DIVISION] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][MULTIPLICACION] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][MAYORQUE] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][MENORQUE] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][MAYORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][MENORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][IGUAL] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][DIFERENTE] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][AND] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][OR] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][ASIGNACION] = ERROR;
	cuboSemantico[BOOLEANO][DECIMAL][CONCATENA] = ERROR;

	//Operaciones Op1: TEXTO, Op2:TEXTO
	cuboSemantico[BOOLEANO][TEXTO][SUMA] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][RESTA] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][DIVISION] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][MULTIPLICACION] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][MAYORQUE] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][MENORQUE] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][MAYORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][MENORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][IGUAL] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][DIFERENTE] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][AND] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][OR] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][ASIGNACION] = ERROR;
	cuboSemantico[BOOLEANO][TEXTO][CONCATENA] = ERROR;

	//Operaciones Op1: TEXTO, Op2:BOOLEANO
	cuboSemantico[BOOLEANO][BOOLEANO][SUMA] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][RESTA] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][DIVISION] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][MULTIPLICACION] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][MAYORQUE] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][MENORQUE] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][MAYORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][MENORIGUAL] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][IGUAL] = BOOLEANO;
	cuboSemantico[BOOLEANO][BOOLEANO][DIFERENTE] = BOOLEANO;
	cuboSemantico[BOOLEANO][BOOLEANO][AND] = BOOLEANO;
	cuboSemantico[BOOLEANO][BOOLEANO][OR] = BOOLEANO;
	cuboSemantico[BOOLEANO][BOOLEANO][ASIGNACION] = ERROR;
	cuboSemantico[BOOLEANO][BOOLEANO][CONCATENA] = ERROR;
}