/*
*Hector Jesus De La Garza Ponce 	619971
*Oziel Alonzo Garza Lopez 			805074

*Libreria cuadruplos.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"
#include "codigosOperaciones.h"

/*
* Función: imprimeCuadruplo
* Parámetros: cuadruplos *listaCuadruplos, int mode
* Descripción: Funcion encargada de imprimir los cuadruplos que se hayan creado hasta el momento
				esta funcion permite desplegar de diferentes formas los cuadruplos para una lectura sencilla
* Salida: ninguna
*/
void imprimeCuadruplos(cuadruplos *listaCuadruplos, int mode) {
	//Variable pivote para cargar y desplegar los datos
	cuadruplos *temporal;

	//Modo para el despliege de los cuadruplo
	if (mode == 0){

		//Recorrido por los cuadruplos
		for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {

			char operacion[10];

			//Switch para renombramiento de operaciones
			switch (temporal->operador){
				case 0:
				strcpy(operacion, "+");
				break;

				case 1:
				strcpy(operacion, "-");
				break;

				case 2:
				strcpy(operacion, "/");
				break;

				case 3:
				strcpy(operacion, "*");
				break;

				case 4:
				strcpy(operacion, ">");
				break;

				case 5:
				strcpy(operacion, "<");
				break;

				case 6:
				strcpy(operacion, ">=");
				break;

				case 7:
				strcpy(operacion, "<=");
				break;

				case 8:
				strcpy(operacion, "==");
				break;

				case 9:
				strcpy(operacion, "¬¬");
				break;

				case 10:
				strcpy(operacion, "&");
				break;

				case 11:
				strcpy(operacion, "|");
				break;

				case 12:
				strcpy(operacion, "=");
				break;

				case 13:
				strcpy(operacion, "<<");
				break;

				case 14:
				strcpy(operacion, "(");
				break;

				case 15:
				strcpy(operacion, ")");
				break;

				case 16:
				strcpy(operacion, "gotoF");
				break;

				case 17:
				strcpy(operacion, "lectura");
				break;

				case 18:
				strcpy(operacion, "print");
				break;

				case 19:
				strcpy(operacion, "goto");
				break;

				case 20:
				strcpy(operacion, "ENDPROC");
				break;

				case 21:
				strcpy(operacion, "ERA");
				break;

				case 22:
				strcpy(operacion, "PARAM");
				break;

				case 23:
				strcpy(operacion, "GOSUB");
				break;

				case 25:
				strcpy(operacion, "ENDPROGRAM");
				break;

				case 26:
				strcpy(operacion, "VERIFICA");
				break;

				case 27:
				strcpy(operacion, "SUMAMAT");
				break;

				case 28:
				strcpy(operacion, "MULTIMAT");
				break;

				case 29:
				strcpy(operacion, "ORO");
				break;

				case 30:
				strcpy(operacion, "ACCESS");
				break;

				case 31:
				strcpy(operacion, "ENDACCESS");
				break;
			}
			printf("Cuadruplo: %d | %s %s %s %s \n", temporal->indice, operacion, temporal->operando1->nombre, temporal->operando2->nombre, temporal->resultado->nombre);
		}
	} else if(mode == 1){
		for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
			printf("---------------------------------------\n");
			printf("Indice : %d\n", temporal->indice);
			printf("Operador : %d\n", temporal->operador);
			printf("Nombre operando1 : %s\n", temporal->operando1->nombre);
			printf("Temp operando1 : %d\n", temporal->operando1->temp);
			printf("Tipo operando1 : %d\n", temporal->operando1->tipo);
			printf("Direccion operando1 : %d\n", temporal->operando1->direccion);
			printf("Nombre operando2 : %s\n", temporal->operando2->nombre);
			printf("Temp operando2 : %d\n", temporal->operando2->temp);
			printf("Tipo operando2 : %d\n", temporal->operando2->tipo);
			printf("Direccion operando2 : %d\n", temporal->operando2->direccion);
			printf("Nombre resultado : %s\n", temporal->resultado->nombre);
			printf("Temp resultado : %d\n", temporal->resultado->temp);
			printf("Tipo resultado : %d\n", temporal->resultado->tipo);
			printf("Direccion resultado : %d\n", temporal->resultado->direccion);

			printf("---------------------------------------\n");
		}
	} else if (mode == 2) {
		for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
			
			char operacion[10];

			//Switch para renombramiento de operaciones
			switch (temporal->operador){
				case 0:
				strcpy(operacion, "+");
				break;

				case 1:
				strcpy(operacion, "-");
				break;

				case 2:
				strcpy(operacion, "/");
				break;

				case 3:
				strcpy(operacion, "*");
				break;

				case 4:
				strcpy(operacion, ">");
				break;

				case 5:
				strcpy(operacion, "<");
				break;

				case 6:
				strcpy(operacion, ">=");
				break;

				case 7:
				strcpy(operacion, "<=");
				break;

				case 8:
				strcpy(operacion, "==");
				break;

				case 9:
				strcpy(operacion, "¬¬");
				break;

				case 10:
				strcpy(operacion, "&");
				break;

				case 11:
				strcpy(operacion, "|");
				break;

				case 12:
				strcpy(operacion, "=");
				break;

				case 13:
				strcpy(operacion, "<<");
				break;

				case 14:
				strcpy(operacion, "(");
				break;

				case 15:
				strcpy(operacion, ")");
				break;

				case 16:
				strcpy(operacion, "gotoF");
				break;

				case 17:
				strcpy(operacion, "lectura");
				break;

				case 18:
				strcpy(operacion, "print");
				break;

				case 19:
				strcpy(operacion, "goto");
				break;

				case 20:
				strcpy(operacion, "ENDPROC");
				break;

				case 21:
				strcpy(operacion, "ERA");
				break;

				case 22:
				strcpy(operacion, "PARAM");
				break;

				case 23:
				strcpy(operacion, "GOSUB");
				break;

				case 25:
				strcpy(operacion, "ENDPROGRAM");
				break;

				case 26:
				strcpy(operacion, "VERIFICA");
				break;

				case 27:
				strcpy(operacion, "SUMAMAT");
				break;

				case 28:
				strcpy(operacion, "MULTIMAT");
				break;

				case 29:
				strcpy(operacion, "ORO");
				break;

				case 30:
				strcpy(operacion, "ACCESS");
				break;

				case 31:
				strcpy(operacion, "ENDACCESS");
				break;
			}
			printf("Cuadruplo: %d | %s %i %i %i \n", temporal->indice, operacion, temporal->operando1->direccion, temporal->operando2->direccion, temporal->resultado->direccion);
		}
	} 
}

/*
* Función: ReciclarVariable
* Parámetros: nodo *variable, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean
* Descripción: Funcion encargada de regresar al avail correspondiente la variable temporal, al momento de meterla en el avail 
			   la marca como reciclada para que solo se tome una vez en el conteo de variables
* Salida: ninguna
*/
void reciclarVariable(nodo *variable, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean){
	//Variable auxiliar para reinsercion en la pila
	nodoOperando *variableReciclada;

	//Reinsercion del nodo en la memoria porque con el pop se habia liberado de memoria
	variableReciclada = (nodoOperando*)malloc(sizeof(nodoOperando));
	variableReciclada->temp = 1;
	variableReciclada->reciclada = 1;
	variableReciclada->tipo = ((nodoOperando*)variable->dato)->tipo;
	variableReciclada->direccion = ((nodoOperando*)variable->dato)->direccion;
	strcpy(variableReciclada->nombre, ((nodoOperando*)variable->dato)->nombre);

	//Seleccion de la pila adecuada para su reinsercion
	switch(variableReciclada->tipo){

		//Variable Entero
		case 0:
		push(availEntero, variableReciclada);
		break;
		//Variable Decimal
		case 1:
		push(availDecimal, variableReciclada);
		break;
		//Variable Texto
		case 2:
		push(availTexto, variableReciclada);
		break;
		//Variable Boolean
		case 3:
		push(availBoolean, variableReciclada);
		break;
	}	
}

/*
* Función: generaCuadruplo
* Parámetros: cuadruplos *listaCuadruplos, nodo *operando1, nodo *operando2, int operador, nodo *resultado, int indice
* Descripción: Funcion encargada de crear un cruadruplo y guardarlo en la lista de cuadruplos que se le mande
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *operando1, nodo *operando2, int operador, nodo *resultado, int indice){
	//Variable auxiliar que servira como needle para la busqueda e insercion en el hash
	cuadruplos *existe;

	//Variables auxiliares para poblar la estructura
	nodoOperando *tempOperando1;
	nodoOperando *tempOperando2;
	nodoOperando *tempResultado;
	
	//Obtenemos una nueva direccion reservada para nuestro resultado, asi obtenemos independencia
	tempOperando1 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempOperando2 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempResultado = (nodoOperando*)malloc(sizeof(nodoOperando));

	//Checamos si se ha agregado el cuadruplo anteriromente
	HASH_FIND_INT(listaCuadruplos, &indice, existe);
	if (existe==NULL) {
		//Si no se ha agregado el cuadruplo se crea y se llena sus datos
		existe = (cuadruplos*)malloc(sizeof(cuadruplos));

		if(operando1 == NULL){
			//Datos NULL
			tempOperando1->temp = -1;
			tempOperando1->tipo = -1;
			strcpy(tempOperando1->nombre, "__");
			tempOperando1->direccion = -1;	
		} else {
			//Pasamos todos los datos de operando1
			tempOperando1->temp = ((nodoOperando*)operando1->dato)->temp;
			tempOperando1->tipo = ((nodoOperando*)operando1->dato)->tipo;
			strcpy(tempOperando1->nombre, ((nodoOperando*)operando1->dato)->nombre);
			tempOperando1->direccion = ((nodoOperando*)operando1->dato)->direccion;	
		}

		if(operando2 == NULL){
			//Datos NULL
			tempOperando2->temp = -1;
			tempOperando2->tipo = -1;
			strcpy(tempOperando2->nombre, "__");
			tempOperando2->direccion = -1;
		} else {
			//Pasamos todos los datos de operando2
			tempOperando2->temp = ((nodoOperando*)operando2->dato)->temp;
			tempOperando2->tipo = ((nodoOperando*)operando2->dato)->tipo;
			strcpy(tempOperando2->nombre, ((nodoOperando*)operando2->dato)->nombre);
			tempOperando2->direccion = ((nodoOperando*)operando2->dato)->direccion;	
		}

		if (resultado == NULL) {
			//Datos NULL
			tempResultado->temp = -1;
			tempResultado->tipo = -1;
			strcpy(tempResultado->nombre, "__");
			tempResultado->direccion = -1;
		} else {
			//Genera el nodo resultado y lo asigna como temporal
			tempResultado->temp = ((nodoOperando*)resultado->dato)->temp;
			tempResultado->tipo = ((nodoOperando*)resultado->dato)->tipo;
			strcpy(tempResultado->nombre, ((nodoOperando*)resultado->dato)->nombre);
			tempResultado->direccion = ((nodoOperando*)resultado->dato)->direccion;	
		}
		
		//Pasar todos los datos al recien creado cuadruplo
		existe->indice = indice;
		existe->operando1 = tempOperando1;
		existe->operando2 = tempOperando2;
		existe->operador = operador;
		existe->resultado = tempResultado;
	
		//Agregamos el nuevo cuaruplo a la lista de hash y regresamos el nuevo apuntador
		HASH_ADD_INT(listaCuadruplos, indice, existe);
		return listaCuadruplos;
	} else {	
		printf("Error en la generacion y adicion de indices en el cuadruplo \n");
		return NULL;
	} 
}

/*
* Función: generarCuadruploExpresion
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[5][5][14], 
			  int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean
* Descripción: Funcion encargada de generar el cuadruplo de cualquier expresion aritmetica 
		       del compilador y verificar su valides en el cuboSemantico
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploExpresion(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[5][5][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean){
	//Variables para facilitar el manjeo de datos
	int operando1Tipo;
	int operando2Tipo;
	int operando1Temp;
	int operando2Temp;
	int operadorInt;
	
	//Apuntadores para el manejo de las pilas
	nodo *operador;
	nodo *operando1;
	nodo *operando2;

	//Apuntadores para el manejo del avail
	nodo *resultadoAvail;
	cuadruplos *accederCuadruplo;

	//Sacamos los datos de las pilas
	operador = pop(operadores);
	operando2 = pop(operandos);
	operando1 = pop(operandos);

	//Inicializacion de enteras
	operando1Tipo = ((nodoOperando*)(operando1->dato))->tipo;
	operando1Temp = ((nodoOperando*)(operando1->dato))->temp;
	operando2Tipo = ((nodoOperando*)(operando2->dato))->tipo;
	operando2Temp = ((nodoOperando*)(operando2->dato))->temp;
	operadorInt = *(int*)(operador->dato);

	//Checamos que el cuadruplo sea posible de realizar
	if (cuboSemantico[operando1Tipo][operando2Tipo][operadorInt] != OP_ERROR) {
		//Verificamos que se tenga un avail disponible para guardar el resultado
		switch(cuboSemantico[operando1Tipo][operando2Tipo][operadorInt]){
			case 0:
				resultadoAvail = pop(availEntero);
				break;

			case 1:
				resultadoAvail = pop(availDecimal);
				break;

			case 2:
				resultadoAvail = pop(availTexto);
				break;

			case 3:
				resultadoAvail = pop(availBoolean);
				break;
		}

		//Checamos si hay avail disponible para la variable, si no hay error en memoria
		if (resultadoAvail == NULL) {
			printf("Error no hay memoria disponible\n");
			exit(1);
		}

		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operadorInt, resultadoAvail, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {
			//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en
			HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

			//Lo guardamos en operandos
			push(operandos, accederCuadruplo->resultado);

			//Si alguno de los operandos correspondia a un temporal ENTONCES lo regresamos al avail correspondiente

			//Verificamos si el operando1 es temporal y si es un temporal de acceso se le regresa su estatus
			if (operando1Temp == 1) {
				if(((nodoOperando*)(operando1->dato))->direccion > 100000){
					((nodoOperando*)(operando1->dato))->direccion = ((nodoOperando*)(operando1->dato))->direccion - 100000;
				}

				//Reciclar la variable temporal
				reciclarVariable(operando1, availEntero, availDecimal, availTexto, availBoolean);
			}

			//Verificamos si el operando2 es temporal y si es un temporal de acceso se le regresa su estatus
			if (operando2Temp == 1) {
				if(((nodoOperando*)(operando2->dato))->direccion > 100000){
					((nodoOperando*)(operando2->dato))->direccion = ((nodoOperando*)(operando2->dato))->direccion - 100000;
				}				

				//Reciclar la variable temporal
				reciclarVariable(operando2, availEntero, availDecimal, availTexto, availBoolean);
			}

			//Aumentamos el contador en 1
			*contadorIndice = *contadorIndice+1;

			return listaCuadruplos;
		} else {
			printf("Error al crear el cuadruplo\n");
			exit(1);
		}

	} else {
		//Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
		printf("Operacion Invalida no se puede realizar una %i con un %i y un %i\n", operadorInt, operando1Tipo, operando2Tipo);
		exit(1);
	}
}

/*
* Función: generarCuadruploAsignacion
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[5][5][14], 
			  int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean
* Descripción: Funcion encargada de generar el cuadruplo de la asignacion, ademas de reciclar la variable temporal para su uso posterior
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploAsignacion(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[5][5][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean){
	//Variables auxiliares Enteras
	int operando1Tipo;
	int resultadoTipo;
	int operando1Temp;
	int operadorInt;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *operando1;
	nodo *resultado;

	//Sacamos los operandos de pila operandos
	//El operando dos llevara NULL
	operando1 = pop(operandos);
	resultado = pop(operandos);

	//Sacamos de la pila (momentariamente) para validar
	operador = pop(operadores);
		
	//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
	operadorInt = *(int*)(operador->dato);

	//Sacando los tipos para ver su compatibilidad en el cubo semantico
	operando1Tipo = ((nodoOperando*)(operando1->dato))->tipo;
	resultadoTipo = ((nodoOperando*)(resultado->dato))->tipo;

	//Checamos en el cubo semantico para ver su compatibilidad
	if (cuboSemantico[operando1Tipo][resultadoTipo][operadorInt] != OP_ERROR){

		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, NULL, operadorInt, resultado, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {

			//Obtenemos si el operando1 es un temporal
			operando1Temp = ((nodoOperando*)(operando1->dato))->temp;

			//Checamos que el operando1 sea temp
			if (operando1Temp == 1) {
				if(((nodoOperando*)(operando1->dato))->direccion > 100000){
					((nodoOperando*)(operando1->dato))->direccion = ((nodoOperando*)(operando1->dato))->direccion - 100000;
				}
				
				//Reciclamos la variable
				reciclarVariable(operando1, availEntero, availDecimal, availTexto, availBoolean);
			} 

			//Aumentamos en 1 el contador de cuadruplos
			*contadorIndice = *contadorIndice+1;

			return listaCuadruplos;
		} else {
			//No se pudo crear el cuadruplo exitosamente
			printf("Error al crear el cuadruplo\n");
			exit(1);
		}
	} else {
		//Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
		printf("Asignacion Invalida\n");
		exit(1);
	}
}

/*
* Función: generarCuadruploLectura
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de lectura
* Consideraciones: Falta ver si es necesario reciclar la variable
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploLectura(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int *contadorIndice){
	//Variables auxiliares Enteras
	int operadorInt;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *resultado;

	//Sacamos el operador de la pila de operandos
	resultado = pop(operandos);

	//Sacamos de la pila (momentariamente) para validar
	operador = pop(operadores);
		
	//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
	operadorInt = *(int*)(operador->dato);
	
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, operadorInt, resultado, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos != NULL) {
		//aumentamos en 1 el contador de cuadruplos
		*contadorIndice = *contadorIndice+1;

		return listaCuadruplos;
	} else {
		printf("Error al crear el cuadruplo\n");
		exit(1);
	}
}

/*
* Función: generarCuadruploEscritura
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de la asignacion
* Consideraciones: Falta ver si es necesario reciclar la variable
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploEscritura(cuadruplos *listaCuadruplos,  pila *operandos, pila *operadores,  int *contadorIndice){
	//Variables auxiliares Enteras
	int operadorInt;
	int resultadoTipo;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *resultado;
	
	//Sacamos los operandos de pila operandos
	resultado = pop(operandos);

	//Sacamos el valor de la pila de operadores
	operador = pop(operadores);
		
	//Obtenemos el valor dentro del nodo que sacamos
	operadorInt = *(int*)(operador->dato);
	resultadoTipo = ((nodoOperando*)(resultado->dato))->tipo;
	
	//Checamos que el resultado de la escritura sea diferente a booleano
	if (resultadoTipo != 3) {	
		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, operadorInt, resultado, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {
		//aumentamos en 1 el contador de cuadruplo
			*contadorIndice = *contadorIndice+1;
			return listaCuadruplos;
		} else {
			printf("Error al crear el cuadruplo\n");
			exit(1);
		}
	} else {
		printf("No es posible imprimir un booleano\n");
		exit(1);
	}
}

/*
* Función: generarCuadruploAccion1
* Parámetros: cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de gotoF, verifica que el cuadruplo se haya creado 
			   y mete el indeCuadruplo en la pila de saltos
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploAccion1(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;

	//Variables auxiliares Apuntadores
	nodo *operando1;
	nodoOperador *salto;

	//Sacamos el operando1 de la pila de operandos
	operando1 = pop(operandos);

	//Almacenar el tipo del operando para verificar que sea booleano
	operandoTipo = ((nodoOperando*)(operando1->dato))->tipo;
	
	if (operandoTipo == 3) {	
		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		//Para obtener la forma de (codigoOperacion, variableEvaluar, __ , resultado)
		listaCuadruplos = generarCuadruploGotoFalso(listaCuadruplos, operando1, contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {
			//Meter en la pila de saltos
			salto = (nodoOperador*)malloc(sizeof(nodoOperador));
			salto->operador = *contadorIndice - 1;
			push(pilaSaltos, salto);

			return listaCuadruplos;
		} else {
			printf("Error al crear el cuadruplo\n");
			exit(1);
		}
	} else {
		printf("No es posible hacer la evaluacion de un operando no booleano\n");
		exit(1);
	}
}

/*
* Función: generarCuadruploAccion2Ciclo
* Parámetros: cuadruplos *listaCuadruplos, pila *pilaSaltos, int *contadorIndice
* Descripción: Funcion encargada de generar el Goto del ciclo y rellenarlo con el valor que se tenia en la pila
			   ademas rellenar el gotoF que se tenia anteriormente en la pila de saltos
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploAccion2Ciclo(cuadruplos *listaCuadruplos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;
	int direccionFalso;
	int direccionRetorno;

	//Variables auxiliares Apuntadores
	nodo *falso;
	nodo *retorno;
	cuadruplos *accederCuadruplo;

	//Obtenemos los valores de la pila de saltos
	falso = pop(pilaSaltos);
	retorno = pop(pilaSaltos);

	//Guardamos la direccion del cuadruplo actual para usarla al modificar datos
	direccionRetorno = *contadorIndice;

	//Guardamos la direccion del cuadruplo del GOTOF para usarla y modificar datos
	direccionFalso = *(int*)(falso->dato);

	//Generamos el cuadruplo del GOTO y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generarCuadruploGoto(listaCuadruplos, contadorIndice);

	if (listaCuadruplos != NULL) {
		//Buscamos el cuadruplo del GOTO que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, &direccionRetorno, accederCuadruplo);

		//Rellenamos los datos del Goto para que apunte de nuevo a la evaluacion
		if(accederCuadruplo != NULL){
			accederCuadruplo->resultado->direccion = *(int*)(retorno->dato);
			sprintf(accederCuadruplo->resultado->nombre, "%d", *(int*)(retorno->dato));
		} else {
			printf("Error en la busqueda del cuadruplo del GOTO\n");
			exit(1);
		}	

		//Buscamos el cuadruplo del GOTOF para modificar sus datos
		HASH_FIND_INT(listaCuadruplos, &direccionFalso, accederCuadruplo);

		if (accederCuadruplo != NULL) {
			sprintf(accederCuadruplo->resultado->nombre, "%d", *contadorIndice);
			accederCuadruplo->resultado->direccion = *contadorIndice;
		} else {
			printf("Error fatal: No se encuentra el cuadruplo %i\n", direccionRetorno);
			exit(1);
		}

		//Al terminar los cambios en los datos se regresa la lista ya actualizada
		return listaCuadruplos;
	} else {
		printf("Error al crear el cuadruplo\n");
		exit(1);
	}
}

/*
* Función: generarCuadruploAccion2Ciclo
* Parámetros: cuadruplos *listaCuadruplos, pila *pilaSaltos, int *contadorIndice
* Descripción: Funcion encargada de generar el segundo cuadruplo GOTO para el else, 
			   ademas de rellenar el GOTOF del if anterior y meterlo en la pila
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploAccion2If(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;	
	int direccionFalso;

	//Variables auxiliares Apuntadores
	nodo *falso;
	nodoOperador *salto;
	cuadruplos *accederCuadruplo;

	//Generamos el cuadruplo GOTO y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generarCuadruploGoto(listaCuadruplos, contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos != NULL) {

		//Obtenemos los datos del GOTOF anteror
		falso = pop(pilaSaltos);
		direccionFalso = *(int*)(falso->dato);

		//Buscamos el cuadruplo del GOTOF para rellenar sus datos
		HASH_FIND_INT(listaCuadruplos, &direccionFalso, accederCuadruplo);

		if (accederCuadruplo != NULL) {
			//Modificamos el cuadruplo
			sprintf(accederCuadruplo->resultado->nombre, "%d", *contadorIndice);
			accederCuadruplo->resultado->direccion = *contadorIndice;
			
			//Metemos el contador actual en la pila de cuadruplos anterior
			salto = (nodoOperador*)malloc(sizeof(nodoOperador));
			salto->operador = *contadorIndice - 1;

			//Lo metemos ne la pila de saltos
			push(pilaSaltos, salto);

			return listaCuadruplos;
		} else {
			printf("Error fatal: No se encuentra el cuadruplo %i\n", direccionFalso);
			exit(1);
		}
	} else {
		printf("Error al crear el cuadruplo\n");
		exit(1);
	}	
}

/*
* Función: generarCuadruploAccion3If
* Parámetros: cuadruplos *listaCuadruplos, pila *pilaSaltos, int *contadorIndice
* Descripción: Funcion encargada de rellenar el GOTO en el caso de ser if else o rellenar el GOTOF del if
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploAccion3If(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;	
	int direccionRetorno;

	//Variables auxiliares Apuntadores
	nodo *retorno;
	cuadruplos *accederCuadruplo;

	//Sacamos de la pila de saltos 
	retorno = pop(pilaSaltos);
	direccionRetorno = *(int*)(retorno->dato);

	//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
	HASH_FIND_INT(listaCuadruplos, &direccionRetorno, accederCuadruplo);

	if (accederCuadruplo != NULL) {

		//Modificamos el cuadruplo anterior
		sprintf(accederCuadruplo->resultado->nombre, "%d", *contadorIndice);
		accederCuadruplo->resultado->direccion = *contadorIndice ;			
		
		return listaCuadruplos;
	} else {
		printf("Error fatal: No se encuentra el cuadruplo %i\n", direccionRetorno);
		exit(1);
	}
}

/*
* Función: generarCuadruploGoto
* Parámetros: cuadruplos *listaCuadruplos, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de GOTO y aumentar en 1 el contadorIndice
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploGoto(cuadruplos *listaCuadruplos, int *contadorIndice){
	//Todos los datos iran en NULL puesto solo se necesitara cambiar el resultado despues
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_GOTO, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploGotoFalso
* Parámetros: cuadruplos *listaCuadruplos, nodo *operando1, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de GOTOF y aumentar en 1 el contadorIndice
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploGotoFalso(cuadruplos *listaCuadruplos, nodo *operando1, int *contadorIndice){
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, NULL, OP_GOTOFALSO, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploEra
* Parámetros: cuadruplos *listaCuadruplos, nodo *operando1, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de ERA
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploEra(cuadruplos *listaCuadruplos, char *nombreFuncion, char *nombreObjeto,int *contadorIndice){
	//Variables auxiliares Apuntadores
	cuadruplos *accederCuadruplo;

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ERA, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Buscamos el cuadruplo que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Rellenamos los datos del Goto para que apunte de nuevo a la evaluacion
		if(accederCuadruplo != NULL){
			sprintf(accederCuadruplo->operando1->nombre, "%s", nombreFuncion);
			sprintf(accederCuadruplo->resultado->nombre, "%s", nombreObjeto);
		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}

		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploOro
* Parámetros: cuadruplos *listaCuadruplos, char *nombreVariable, char *nombreClase, char *nombreProcedimiento, 
			  char *nombreObjetoActual, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo para la creacion de los datos de los objetos en la maquina virtual
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploOro(cuadruplos *listaCuadruplos, char *nombreVariable, char *nombreClase, char *nombreProcedimiento, char *nombreObjetoActual, int *contadorIndice){
	//Variables auxiliares Apuntadores
	cuadruplos *accederCuadruplo;

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ORO, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Buscamos el cuadruplo que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Rellenamos los datos del Goto para que apunte de nuevo a la evaluacion
		if(accederCuadruplo != NULL){

			//Modificacion de los datos de
			sprintf(accederCuadruplo->operando1->nombre, "%s", nombreVariable);
			sprintf(accederCuadruplo->operando2->nombre, "%s", nombreClase);
			sprintf(accederCuadruplo->resultado->nombre, "%s%s", nombreProcedimiento, nombreObjetoActual);
		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}

		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploAccess
* Parámetros: cuadruplos *listaCuadruplos, char *nombreVariable, char *nombreClase, char *nombreProcedimiento, 
			  char *nombreObjetoActual, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo para el acceso a los datos de los objetos en la maquina virtual
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploAccess(cuadruplos *listaCuadruplos, char *nombreVariable, char *nombreClase, char *nombreProcedimiento, char *nombreObjetoActual, int *contadorIndice){
	//Variables auxiliares Apuntadores
	cuadruplos *accederCuadruplo;

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ACCESS, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Buscamos el cuadruplo que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Checamos que el cuadruplo exista
		if(accederCuadruplo != NULL){

			//Modificacion de los datos del cuadruplo
			sprintf(accederCuadruplo->operando1->nombre, "%s", nombreVariable);
			sprintf(accederCuadruplo->operando2->nombre, "%s", nombreClase);
			sprintf(accederCuadruplo->resultado->nombre, "%s%s", nombreProcedimiento, nombreObjetoActual);
		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}

		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploEndAccess
* Parámetros: cuadruplos *listaCuadruplos, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo para el terminar acceso a los datos de los objetos en la maquina virtual
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploEndAccess(cuadruplos *listaCuadruplos, int *contadorIndice){
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ENDACCESS, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploEndProc
* Parámetros: cuadruplos *listaCuadruplos, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de ENDPROC y aumentar en 1 el contador de indices
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploEndProc(cuadruplos *listaCuadruplos, int *contadorIndice){
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ENDPROC, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploEndProc
* Parámetros: cuadruplos *listaCuadruplos, int *cantidadParametros, pila *operandos, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de param
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploParam(cuadruplos *listaCuadruplos, int *cantidadParametros, pila *operandos, int *contadorIndice){
	//Variables auxiliares Apuntadores
	nodo *operando;
	cuadruplos *accederCuadruplo;

	//Sacamos el operando de la pila
	operando = pop(operandos);

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando, NULL, OP_PARAM, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Buscamos el cuadruplo que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Rellenamos los datos de las direcciones y nombres para visualizar los datos
		if(accederCuadruplo != NULL){
			accederCuadruplo->resultado->direccion = *(int*)(cantidadParametros);
			sprintf(accederCuadruplo->resultado->nombre, "param%d", *(int*)(cantidadParametros));
		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}	
		
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploGosub
* Parámetros: cuadruplos *listaCuadruplos, int direccionFuncion, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo Gosub para una funcion apuntando al cuadruplo donde empieza esta
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploGosub(cuadruplos *listaCuadruplos, int direccionFuncion, int *contadorIndice){
	//Variables auxiliares Apuntadores
	cuadruplos *accederCuadruplo;

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_GOSUB, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Buscamos el cuadruplo que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Modificamos los datos del operando 1 para que apunten a la direccion deseada
		if(accederCuadruplo != NULL){
			accederCuadruplo->operando1->direccion =  direccionFuncion;
			sprintf(accederCuadruplo->operando1->nombre, "%d", direccionFuncion);
		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}	
		
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploReturn
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, int tipo, long direccion, char *nombre, int *contadorIndice
* Descripción: Funcion encargada de generar los cuadruplos correspondientes para la accion de regresar en una funcion
				generara un cuadruplo de asignacion donde guardara en una variable temporal el dato y el cuadruplo ENDPROC
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploReturn(cuadruplos *listaCuadruplos, pila *operandos, int tipo, long direccion, char *nombre, int *contadorIndice){
	//Variables auxiliares Apuntadores
	cuadruplos *accederCuadruplo;

	//Variables auxiliares Apuntadores
	nodo *operando;
	int operandoInt;

	//Sacamos el operando de la expresion de operandos
	operando = pop(operandos);	
	operandoInt = ((nodoOperando*)(operando->dato))->tipo;;

	//Checamos que se pueda hacer la asignacion
	//Esto quiere decir que el valor que regresemos sea igual al que definimos
	if (operandoInt == tipo){
		//Generamos el cuadruplo de asignacion por el momento solo con el dato del operando que usaremos
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando, NULL, OP_ASIGNACION, NULL, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
		} else {
			//Buscamos el cuadruplo que acabamos de crear para darle los valores correspondientes
			HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

			//Modificamos los datos del cuadruplo
			if(accederCuadruplo != NULL){
				accederCuadruplo->resultado->tipo = tipo;
				accederCuadruplo->resultado->direccion =  direccion;
				strcpy(accederCuadruplo->resultado->nombre, nombre);
			} else {
				printf("Error en el acceso al cuadruplo\n");
				exit(1);
			}	

			//Tuvo exito la creacion del cuadruplo
			*contadorIndice = *contadorIndice+1;

			//Regresamos la lista
			return listaCuadruplos;	
		}
	} else {
		printf("Error en el retorno, no es posible regresar una variable tipo %i, cuando se definio una %i \n", operandoInt, tipo);
		exit(1);
	}
}

/*
* Función: generarCuadruploTemporalFuncion
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, int tipo, long direccion, char *nombre,
			  pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo temporal para las llamadas a funciones en expresiones
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploTemporalFuncion(cuadruplos *listaCuadruplos, pila *operandos, int tipo, long direccion, char *nombre, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean, int *contadorIndice){
	//Apuntadores para el manejo del avail
	nodo *resultadoAvail;
	cuadruplos *accederCuadruplo;

	//Instruccion para obtener el Temporal Adecuado	
	switch(tipo){
		case 0:
			resultadoAvail = pop(availEntero);
			break;

		case 1:
			resultadoAvail = pop(availDecimal);
			break;

		case 2:
			resultadoAvail = pop(availTexto);
			break;

		case 3:
			resultadoAvail = pop(availBoolean);
			break;
	}

	//Checamos si hay avail disponible para la variable, si no hay error en memoria
	if (resultadoAvail == NULL) {
		printf("Error no hay memoria disponible\n");
		exit(1);
	}

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ASIGNACION, resultadoAvail, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Buscamos el cuadruplo que acabamos de crear
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Modificamos los datos del cuadruplo recien creado
		if(accederCuadruplo != NULL){
			accederCuadruplo->operando1->tipo =  tipo;
			accederCuadruplo->operando1->direccion =  direccion;
			strcpy(accederCuadruplo->operando1->nombre, nombre);
		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}	
		
		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Metemos en la pila de operandos el temporal recien creado que sera usado para la expresion
		push(operandos, ((nodoOperando*)(resultadoAvail->dato)));

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generarCuadruploEndProgram
* Parámetros: cuadruplos *listaCuadruplos, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo de fin de programa
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploEndProgram(cuadruplos *listaCuadruplos, int *contadorIndice){
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, NULL, NULL, OP_ENDPROGRAM, NULL, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos == NULL) {
			//Si hubo un error desplegarlo por pantalla
			printf("Error en la creacion del cuadruplo\n");
			exit(1);
	} else {
		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generaCuadruploVerifica
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos,  int lsuperior, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo verifica desde la posicion 0 hasta el limite superior
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generaCuadruploVerifica(cuadruplos *listaCuadruplos, pila *operandos,  int lsuperior, int *contadorIndice){
	//Apuntadores para el manejo del avail
	nodo *operando;
	cuadruplos *accederCuadruplo;

	//Sacamos el operando de su pila
	operando = pop(operandos);

	//Si el operando tiene tipo difernete a entero marcar error
	if(((nodoOperando*)operando->dato)->tipo != 0){
		printf("Error: el indice debe ser entero");
		exit(1);
	} else {

		//Generar el cuadruplo de verificar y agregarlo a la lista
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando, NULL, OP_VERIFICA, NULL , *contadorIndice);

		//Buscamos el cuadruplo que acabamos de crear para darle los valores correspondientes
		HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

		//Checamos que se haya creado y modificamos los datos pertinentes
		if(accederCuadruplo != NULL){
			
			accederCuadruplo->operando2->direccion = 0;
			accederCuadruplo->resultado->direccion = lsuperior;

			sprintf(accederCuadruplo->resultado->nombre, "%d", lsuperior);
			sprintf(accederCuadruplo->operando2->nombre, "%d", 0);

		} else {
			printf("Error en el acceso al cuadruplo\n");
			exit(1);
		}	

		//Metemos el operando a la pila para usarlo en los despalzamientos del arreglo o matriz
		push(operandos, ((nodoOperando*)(operando->dato)));

		//Tuvo exito la creacion del cuadruplo
		*contadorIndice = *contadorIndice+1;

		//Regresamos la lista
		return listaCuadruplos;	
	}
}

/*
* Función: generaCuadruploSUMAarreglo
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, int direccionBase, pila *availEntero, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo SUMAMAT, el cual hacer un desplazamiento al sumar una variable con una direccion
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generaCuadruploSUMAarreglo(cuadruplos *listaCuadruplos, pila *operandos, int direccionBase, pila *availEntero, int *contadorIndice){

	//Apuntadores para el manejo del avail
	nodo *operando;
	cuadruplos *accederCuadruplo;
	nodo *resultadoAvail;

	//Obtenemos los datos de operandos y del avail de temporales
	resultadoAvail =  pop(availEntero);
	operando = pop(operandos);

	//Checamos si hay avail disponible para la variable, si no hay error en memoria	
	if (resultadoAvail == NULL) {
		printf("Error no hay memoria disponible\n");
		exit(1);
	}

	//Generamos el cuadruplo de SUMAMAT y lo agregamos a la lista de cuadruplos
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando, NULL, OP_SUMAMAT, resultadoAvail , *contadorIndice);

	//Buscamos el cuadruplo que acabamos de crear para darle los valores correspondientes
	HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

	//Verificamos que el cuadruplo se haya creado correctamente
	if(accederCuadruplo != NULL){
		
		//Modificamos los datos necesarios
		accederCuadruplo->operando2->direccion = direccionBase;

		sprintf(accederCuadruplo->operando2->nombre, "%d", direccionBase);		

	} else {
		printf("Error en el acceso al cuadruplo\n");
		exit(1);
	}

	//Como el resultado tendra que marcarse como especial se le agrega una direccion falsa y se agrega a la pila de operandos
	((nodoOperando*)resultadoAvail->dato)->direccion = ((nodoOperando*)resultadoAvail->dato)->direccion + 100000;
	push(operandos, ((nodoOperando*)resultadoAvail->dato));

	//Tuvo exito la creacion del cuadruplo
	*contadorIndice = *contadorIndice+1;

	//Regresamos la lista
	return listaCuadruplos;	
}

/*
* Función: generarCuadruploMULTIarreglo
* Parámetros: cuadruplos *listaCuadruplos, pila *operandos, int direccionBase, pila *availEntero, int *contadorIndice
* Descripción: Funcion encargada de generar el cuadruplo MULTIMAT, el cual hace un desplazamiento al multiplcar una variable con una direccion
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploMULTIarreglo(cuadruplos *listaCuadruplos, pila *operandos, int m1, pila *availEntero, int *contadorIndice){

	//Apuntadores para el manejo del avail
	nodo *operando;
	cuadruplos *accederCuadruplo;
	nodo *resultadoAvail;

	//Obtenemos los datos de operandos y del avail de temporales
	resultadoAvail =  pop(availEntero);
	operando = pop(operandos);

	//Checamos si hay avail disponible para la variable, si no hay error en memoria	
	if (resultadoAvail == NULL) {
		printf("Error no hay memoria disponible\n");
		exit(1);
	}
	//Generamos el cuadruplo de SUMAMAT y lo agregamos a la lista de cuadruplos
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando, NULL, OP_MULTIMAT, resultadoAvail, *contadorIndice);

	//Buscamos el cuadruplo que acabamos de crear para darle los valores correspondientes
	HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

	//Verificamos que el cuadruplo se haya creado correctamente
	if(accederCuadruplo != NULL){
		
		//Modificamos los datos necesarios
		accederCuadruplo->operando2->direccion = m1;

		sprintf(accederCuadruplo->operando2->nombre, "%d", m1);

	} else {
		printf("Error en el acceso al cuadruplo\n");
		exit(1);
	}	

	//Meter el resultado a la pila de operandos
	push(operandos, ((nodoOperando*)resultadoAvail->dato));

	//Tuvo exito la creacion del cuadruplo
	*contadorIndice = *contadorIndice+1;

	//Regresamos la lista
	return listaCuadruplos;		
}

/*
* Función: generarCuadruploSequencial
* Parámetros: nt prioridad, cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[5][5][14], 
			  int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean
* Descripción: Funcion encargada de seleccionar que funcion se debera usar para generar cuadruplos secuenciales
			    Util para control y para no confundir que parametros se deben usar
* Salida: la lista de cuadruplos con el nuevo cuadruplo insertado en esta
*/
cuadruplos* generarCuadruploSequencial(int prioridad, cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[5][5][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean){
	//Variables auxiliares Enteras
	int operadorInt;

	//Variables auxiliares Apuntadores
	nodo *operador;

	//Variables para la reinsercion
	nodoOperador *reinsertarOperador;

	//Checamos que la pila de operadores no este vacia
	if (pilaVacia(operadores) == 1) {
		//Si no esta vacia ...
		//Sacamos de la pila (momentariamente) para validar
		operador = pop(operadores);

		//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
		operadorInt = *(int*)(operador->dato);

		//Metemos otra vez en la pila el operador con el fin de usarlo en alguna de las operaciones
		reinsertarOperador = (nodoOperador*)malloc(sizeof(nodoOperador));
		reinsertarOperador->operador = operadorInt;
		push(operadores, reinsertarOperador);

		switch(prioridad){
			//Prioridad: Multiplicacion o Division
			case 1:
			if (operadorInt == OP_MULTIPLICACION || operadorInt == OP_DIVISION)
				listaCuadruplos = generarCuadruploExpresion(listaCuadruplos, operandos, operadores, cuboSemantico, contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
			break;

			//Prioridad: Suma o Resta
			case 2:
			if (operadorInt == OP_SUMA || operadorInt == OP_RESTA)
				listaCuadruplos = generarCuadruploExpresion(listaCuadruplos, operandos, operadores, cuboSemantico, contadorIndice, availEntero, availDecimal, availTexto, availBoolean);

			break;

			//Prioridad: Operadores Relacionales
			case 3:
			if (operadorInt == OP_MAYORQUE || operadorInt == OP_MENORQUE || operadorInt == OP_MAYORIGUAL || operadorInt == OP_MENORIGUAL || operadorInt == OP_IGUAL || operadorInt == OP_DIFERENTE)
				listaCuadruplos = generarCuadruploExpresion(listaCuadruplos, operandos, operadores, cuboSemantico, contadorIndice, availEntero, availDecimal, availTexto, availBoolean);

			break;

			//Prioridad: And Or
			case 4:
			if (operadorInt == OP_AND || operadorInt == OP_OR)
				listaCuadruplos = generarCuadruploExpresion(listaCuadruplos, operandos, operadores, cuboSemantico, contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
			break;

			//Prioridad: Asignacion
			case 5:
			if (operadorInt == OP_ASIGNACION)
				listaCuadruplos = generarCuadruploAsignacion(listaCuadruplos, operandos, operadores, cuboSemantico, contadorIndice, availEntero, availDecimal, availTexto, availBoolean);

			break;

			//Prioridad Lectura
			case 6:
			if (operadorInt == OP_LECTURA)
				listaCuadruplos = generarCuadruploLectura(listaCuadruplos, operandos, operadores, contadorIndice);
			break;

			//Prioridad Escritura
			case 7:
			if (operadorInt == OP_ESCRITURA)
				listaCuadruplos = generarCuadruploEscritura(listaCuadruplos, operandos, operadores, contadorIndice);
			break;
		}

		//Regesamos la lista de cuadruplos con o sin ningun cambio
		return listaCuadruplos;	

	} else {
		//Si la pila esta vacia no necesitamos realizar ninguna operacion
		//Regresamos la lista de cuadruplos
		return listaCuadruplos;
	}
}

/*
* Función: generarObj
* Parámetros: cuadruplos *listaCuadruplos
* Descripción: Funcion encargada de crear el archivo obj de traduccion del lenguaje
* Salida: Generara un archivo de texto en donde se tendra los cuadruplos necesarios para que los interprete la maquina virtual
*/
void generarObj(cuadruplos *listaCuadruplos) {
	
	//Crear el archivo y guardarlo en carpeta raiz
	FILE *fp;
	fp = fopen("GAlaDos-MaqVirtual/obj/codigoObjeto.txt", "w");
	
	//Variable pivote
	cuadruplos *temporal;

	//Barrido de los cuadruplos imprimiendolos directamente en el archivo
	for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
		char operacion[10];					
		if(temporal->operador == 21){
			fprintf(fp,  "%i, %s, %i, %s\n", temporal->operador, temporal->operando1->nombre, temporal->operando2->direccion, temporal->resultado->nombre);
		} else if (temporal->operador == 29) {
			fprintf(fp,  "%i, %s, %s, %s\n", temporal->operador, temporal->operando1->nombre, temporal->operando2->nombre, temporal->resultado->nombre);
		} else if (temporal->operador == 30) {
			fprintf(fp,  "%i, %s, %s, %s\n", temporal->operador, temporal->operando1->nombre, temporal->operando2->nombre, temporal->resultado->nombre);
		} else {
			fprintf(fp,  "%i, %i, %i, %i\n", temporal->operador, temporal->operando1->direccion, temporal->operando2->direccion, temporal->resultado->direccion);		
		}
	}
}