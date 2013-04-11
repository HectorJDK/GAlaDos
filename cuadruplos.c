#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"
#include "codigosOperaciones.h"
/*
* Clase que implementa una estructura de pila en C
*/

/*
*GenerarCuadruplo 
*Crea un cruadruplo y lo guarda en la lista de cuadruplos correspondiente, usa nodos en donde se tiene la informacion general
*/
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *operando1, nodo *operando2, nodo *operador, nodo *resultado, int indice){
	//Variable auxiliar que servira como needle para la busqueda e insercion en el hash
	cuadruplos *existe;
	cuadruplos *prueba;

	//Variables auxiliares para poblar la estructura
	nodoOperando *tempOperando1;
	nodoOperando *tempOperando2;
	nodoOperando *tempResultado;
	
	//Obtenemos una nueva direccion reservada para nuestro resultado, asi obtenemos independencia
	tempOperando1 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempOperando2 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempResultado = (nodoOperando*)malloc(sizeof(nodoOperando));
	

	//Checamos si se ha agregado el cuadruplo anteriromente
	HASH_FIND_INT(listaCuadruplos, &indice, existe);  /* id already in the hash? */
	if (existe==NULL) {
		//Si no se ha agregado el cuadruplo se crea y se llena sus datos
		existe = (cuadruplos*)malloc(sizeof(cuadruplos));

		if(operando1 == NULL){
			//Datos NULL
			tempOperando1->temp = -1;
			tempOperando1->tipo = -1;
			strcpy(tempOperando1->nombre, "NuLl");
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
			strcpy(tempOperando2->nombre, "NuLl");
			tempOperando2->direccion = -1;
		} else {
			//Pasamos todos los datos de operando2
			tempOperando2->temp = ((nodoOperando*)operando2->dato)->temp;
			tempOperando2->tipo = ((nodoOperando*)operando2->dato)->tipo;
			strcpy(tempOperando2->nombre, ((nodoOperando*)operando2->dato)->nombre);
			tempOperando2->direccion = ((nodoOperando*)operando2->dato)->direccion;	
		}

		if (resultado == NULL) {
			//Genera el nodo resultado y lo asigna como temporal
			tempResultado->temp = -1;
			tempResultado->tipo = -1;
			strcpy(tempResultado->nombre, "NuLl");
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
		existe->operador = *(int*)(operador->dato);
		existe->resultado = tempResultado;
	
		//Agregamos el nuevo cuaruplo a la lista de hash y regresamos el nuevo apuntador
		HASH_ADD_INT(listaCuadruplos, indice, existe);  /* id: name of key field */
		return listaCuadruplos;
	} else {	
		printf("Error en la generacion y adicion de indices en el cuadruplo \n");
		return NULL;
	} 
}

/*
*imprimeCuadruplos
*Imprime todos los datos en orden de la lista de cuadruplos que se da
*/	
void imprimeCuadruplos(cuadruplos *listaCuadruplos, int mode) {
	cuadruplos *temporal;

	if(mode == 1){
		for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
			printf("---------------------------------------\n");
			printf("Ya sabemos indice 				: %d\n", temporal->indice);

			printf("Ya sabemos operador 			: %d\n", temporal->operador);

			printf("Ya sabemos Nombre operando1 	: %s\n", temporal->operando1->nombre);
			printf("Ya sabemos temp operando1		: %d\n", temporal->operando1->temp);
			printf("Ya sabemos tipo operando1		: %d\n", temporal->operando1->tipo);
			printf("Ya sabemos direccion operando1	: %d\n", temporal->operando1->direccion);

			printf("Ya sabemos Nombre operando2 	: %s\n", temporal->operando2->nombre);
			printf("Ya sabemos temp operando2		: %d\n", temporal->operando2->temp);
			printf("Ya sabemos tipo operando2		: %d\n", temporal->operando2->tipo);
			printf("Ya sabemos direccion operando2	: %d\n", temporal->operando2->direccion);

			printf("Ya sabemos Nombre resultado 	: %s\n", temporal->resultado->nombre);
			printf("Ya sabemos temp resultado		: %d\n", temporal->resultado->temp);
			printf("Ya sabemos tipo resultado		: %d\n", temporal->resultado->tipo);
			printf("Ya sabemos direccion resultado	: %d\n", temporal->resultado->direccion);

			printf("---------------------------------------\n");
		}
	} else {
		for(temporal = listaCuadruplos; temporal != NULL; temporal=(cuadruplos*)(temporal->hh.next)) {
			char operacion[10];

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
			}
			printf("Cuadruplo: %d | %s %s %s %s \n", temporal->indice, operacion, temporal->operando1->nombre, temporal->operando2->nombre, temporal->resultado->nombre);
		}
	}
}

cuadruplos* generarCuadruploAsignacion(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[4][4][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean){
	//Variables auxiliares Enteras
	int operando1Tipo;
	int resultadoTipo;
	int operando1Temp;
	int operadorInt;


	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *operando1;
	nodo *operando2;
	nodo *resultado;
	cuadruplos *accederCuadruplo;
	
	//Apuntador para el avail que se usara en el cuadruplo
	nodoOperando *nuevoAvail;

	//Esta funcion generara un triplo con los datos necesarios
	//Tenemos todos los valores necesarios en las pilas
	//Sacamos los operandos de pila operandos
	operando1 = pop(operandos);
	resultado = pop(operandos);
	operando2 = NULL;

	//Sacamos de la pila (momentariamente) para validar
	operador = pop(operadores);
		
	//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
	operadorInt = *(int*)(operador->dato);

	//Sacando los tipos para ver su compatibilidad en el cubo semantico
	operando1Tipo = ((nodoOperando*)(operando1->dato))->tipo;
	resultadoTipo = ((nodoOperando*)(resultado->dato))->tipo;
	operando1Temp = ((nodoOperando*)(operando1->dato))->temp;

	if (cuboSemantico[operando1Tipo][resultadoTipo][operadorInt] != OP_ERROR){
		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultado, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {
			//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
			HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

			//Si alguno de los operandos correspondia a un temporal ENTONCES lo regresamos al avail correspondiente
			//checamos que el operando1 sea temp
			if (operando1Temp == 1) {
				//Reinsercion del nodo en la memoria porque con el pop se habia liberado de memoria
				nuevoAvail = (nodoOperando*)malloc(sizeof(nodoOperando));
				nuevoAvail->temp = ((nodoOperando*)operando1->dato)->temp;
				nuevoAvail->tipo = ((nodoOperando*)operando1->dato)->tipo;
				strcpy(nuevoAvail->nombre, ((nodoOperando*)operando1->dato)->nombre);
				nuevoAvail->direccion = ((nodoOperando*)operando1->dato)->direccion;

				switch(operando1Tipo){
					case 0:
						push(availEntero, nuevoAvail);
						break;

					case 1:
						push(availDecimal, nuevoAvail);
						break;

					case 2:
						push(availTexto, nuevoAvail);
						break;

					case 3:
						push(availBoolean, nuevoAvail);
						break;
				}
			} 

			//aumentamos en 1 el contador de cuadruplos
			//int aux = *contadorIndice+1;
			*contadorIndice = *contadorIndice+1;

			return listaCuadruplos;
		} else {
			printf("Error al crear el cuadruplo\n");
			exit(1);
		}
	} else {
		//Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
		printf("Asignacion Invalida\n");
		exit(1);
	}
}

cuadruplos* generarCuadruploLectura(cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int *contadorIndice){
	//Variables auxiliares Enteras
	int operadorInt;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *operando1;
	nodo *operando2;
	nodo *resultado;

	//Esta funcion generara un triplo con los datos necesarios
	//Tenemos todos los valores necesarios en las pilas
	//Sacamos los operandos de pila operandos
	resultado = pop(operandos);
	operando1 = NULL;
	operando2 = NULL;

	//Sacamos de la pila (momentariamente) para validar
	operador = pop(operadores);
		
	//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
	operadorInt = *(int*)(operador->dato);
	
	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultado, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos != NULL) {
		//aumentamos en 1 el contador de cuadruplos
		//int aux = *contadorIndice+1;
		*contadorIndice = *contadorIndice+1;
		return listaCuadruplos;
	} else {
		printf("Error al crear el cuadruplo\n");
		exit(1);
	}
	
}

cuadruplos* generarCuadruploEscritura(cuadruplos *listaCuadruplos,  pila *operandos, pila *operadores,  int *contadorIndice){
	//Variables auxiliares Enteras
	int operadorInt;
	int resultadoTipo;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *operando1;
	nodo *operando2;
	nodo *resultado;

	//Esta funcion generara un triplo con los datos necesarios
	//Tenemos todos los valores necesarios en las pilas
	//Sacamos los operandos de pila operandos
	resultado = pop(operandos);
	operando1 = NULL;
	operando2 = NULL;

	//Sacamos de la pila (momentariamente) para validar
	operador = pop(operadores);
		
	//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
	operadorInt = *(int*)(operador->dato);
	resultadoTipo = ((nodoOperando*)(resultado->dato))->tipo;
	
	if (resultadoTipo != 3) {	
		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultado, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {
		//aumentamos en 1 el contador de cuadruplos
		//int aux = *contadorIndice+1;
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


cuadruplos* generarCuadruploGotoFalsoCiclo(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;	

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodoOperador *operador1;
	nodo *operando1;
	nodo *operando2;
	nodo *resultado;
	nodoOperador *salto;

	//Esta funcion generara un triplo con los datos necesarios
	//Tenemos todos los valores necesarios en las pilas
	//Sacamos los operandos de pila operandos
	resultado = NULL;
	operando1 = pop(operandos);
	operando2 = NULL;

	operador1 = (nodoOperador*)malloc(sizeof(nodoOperador));
	operador1->operador = OP_GOTOFALSO;
	push(pilaSaltos, operador1);
	operador = pop(pilaSaltos);

	//Almacenar el tipo del operando para verificar que sea booleano
	operandoTipo = ((nodoOperando*)(operando1->dato))->tipo;
	
	if (operandoTipo == 3) {	
		//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
		listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultado, *contadorIndice);

		//Checamos si no hubo algun error en la generacion de los cuadruplos
		if (listaCuadruplos != NULL) {
			//Meter en la pila de saltos
			salto = (nodoOperador*)malloc(sizeof(nodoOperador));
			salto->operador = *contadorIndice;
			push(pilaSaltos, salto);

			//aumentamos en 1 el contador de cuadruplos
			//int aux = *contadorIndice+1;
			*contadorIndice = *contadorIndice+1;

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

cuadruplos* generarCuadruploGotoCiclo(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;	
	int direccionRetorno;

	cuadruplos *accederCuadruplo;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodoOperador *operador1;
	nodo *operando1;
	nodo *operando2;
	nodo *resultado;
	nodoOperando *resultado1;

	nodo *falso;
	nodo *retorno;

	operando1 = NULL;
	operando2 = NULL;

	falso = pop(pilaSaltos);
	retorno = pop(pilaSaltos);
	
	//Truco sucio para castear a nodo
	operador1 = (nodoOperador*)malloc(sizeof(nodoOperador));
	operador1->operador = OP_GOTO;
	push(pilaSaltos, operador1);
	operador = pop(pilaSaltos);

	//Truco sucio para castear a nodo
	resultado1 = (nodoOperando*)malloc(sizeof(nodoOperando));
	resultado1->direccion = *(int*)(retorno->dato);
	resultado1->tipo = -1;
	resultado1->temp = -1;	
	sprintf(resultado1->nombre, "%d", *(int*)(retorno->dato));
	
	push(pilaSaltos, resultado1);
	resultado = pop(pilaSaltos);

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultado, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos != NULL) {
		direccionRetorno = *(int*)(falso->dato);

		//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
		HASH_FIND_INT(listaCuadruplos, &direccionRetorno, accederCuadruplo);

		if (accederCuadruplo != NULL) {
			*contadorIndice = *contadorIndice+1;

			sprintf(accederCuadruplo->resultado->nombre, "%d", *contadorIndice);
			accederCuadruplo->resultado->direccion = *contadorIndice;

			return listaCuadruplos;
		} else {
			printf("Error fatal: No se encuentra el cuadruplo %i\n", direccionRetorno);
			exit(1);
		}
	} else {
		printf("Error al crear el cuadruplo\n");
		exit(1);
	}	
}

cuadruplos* generarCuadruploGotoFalsoElse(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;	
	int direccionRetorno;

	cuadruplos *accederCuadruplo;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodoOperador *operador1;
	nodo *operando1;
	nodo *operando2;
	nodo *resultado;
	nodoOperando *resultado1;
	nodoOperador *salto;

	nodo *falso;

	operando1 = NULL;
	operando2 = NULL;
	resultado = NULL;

	//Generacion del GOTO
	//Truco sucio para castear a nodo
	operador1 = (nodoOperador*)malloc(sizeof(nodoOperador));
	operador1->operador = OP_GOTO;

	push(pilaSaltos, operador1);
	operador = pop(pilaSaltos);

	//Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
	listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultado, *contadorIndice);

	//Checamos si no hubo algun error en la generacion de los cuadruplos
	if (listaCuadruplos != NULL) {

		falso = pop(pilaSaltos);
		direccionRetorno = *(int*)(falso->dato);

		//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
		HASH_FIND_INT(listaCuadruplos, &direccionRetorno, accederCuadruplo);

		if (accederCuadruplo != NULL) {
			*contadorIndice = *contadorIndice+1;

			//Modificamos el cuadruplo anterior
			sprintf(accederCuadruplo->resultado->nombre, "%d", *contadorIndice);
			accederCuadruplo->resultado->direccion = *contadorIndice;
			

			//Metemos el contador actual en la pila de cuadruplos anterior
			salto = (nodoOperador*)malloc(sizeof(nodoOperador));
			salto->operador = *contadorIndice - 1;

			//Lo metemos ne la pila de saltos
			push(pilaSaltos, salto);

			return listaCuadruplos;
		} else {
			printf("Error fatal: No se encuentra el cuadruplo %i\n", direccionRetorno);
			exit(1);
		}
	} else {
		printf("Error al crear el cuadruplo\n");
		exit(1);
	}	
}

cuadruplos* generarCuadruploGotoIf(cuadruplos *listaCuadruplos,  pila *operandos, pila *pilaSaltos, int *contadorIndice){
	//Variables auxiliares Enteras
	int operandoTipo;	
	int direccionRetorno;

	cuadruplos *accederCuadruplo;

	//Variables auxiliares Apuntadores
	nodo *retorno;

	//Sacamos de la pila de saltos 
	retorno = pop(pilaSaltos);
	direccionRetorno = *(int*)(retorno->dato);

	//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
	HASH_FIND_INT(listaCuadruplos, &direccionRetorno, accederCuadruplo);

	if (accederCuadruplo != NULL) {

		//Modificamos el cuadruplo anterior
		sprintf(accederCuadruplo->resultado->nombre, "%d", *contadorIndice);
		accederCuadruplo->resultado->direccion = *contadorIndice + 1;			
		
		return listaCuadruplos;
	} else {
		printf("Error fatal: No se encuentra el cuadruplo %i\n", direccionRetorno);
		exit(1);
	}
	
}



//Generacion de cuadruplos para 
cuadruplos* verificacionGeneracionCuadruplo (int prioridad, cuadruplos *listaCuadruplos, pila *operandos, pila *operadores, int cuboSemantico[4][4][14], int *contadorIndice, pila *availEntero, pila *availDecimal, pila *availTexto, pila *availBoolean){
	
	//Variables auxiliares Enteras
	int acceso;
	int operando1Tipo;
	int operando2Tipo;
	int operando1Temp;
	int operando2Temp;
	int operadorInt;

	//Variables auxiliares Apuntadores
	nodo *operador;
	nodo *operando1;
	nodo *operando2;
	cuadruplos *accederCuadruplo;

	//Variables para la reinsercion
	nodoOperador *reinsertarOperador;

	//Apuntador para el avail que se usara en el cuadruplo
	nodo *resultadoAvail;
	nodoOperando *nuevoAvail;

	//Salimos de FACTOR
	//Checamos que la pila de operadores no este vacia
	if (pilaVacia(operadores) == 1) {
		//Si no esta vacia ...
		//Sacamos de la pila (momentariamente) para validar
		operador = pop(operadores);
		
		//Obtenemos el valor dentro del nodo que sacamos (este sera entero)
		operadorInt = *(int*)(operador->dato);

		//Inicializamos acceso con 0 para no entrar
		acceso = 0;

		switch(prioridad){
			//Prioridad: Multiplicacion o Division
			case 1:
				if (operadorInt == OP_MULTIPLICACION || operadorInt == OP_DIVISION)
					acceso = 1;
				break;

			//Prioridad: Suma o Resta
			case 2:
				if (operadorInt == OP_SUMA || operadorInt == OP_RESTA)
					acceso = 1;
				break;

			//Prioridad: Operadores Relacionales
			case 3:
				if (operadorInt == OP_MAYORQUE || operadorInt == OP_MENORQUE || operadorInt == OP_MAYORIGUAL || operadorInt == OP_MENORIGUAL || operadorInt == OP_IGUAL || operadorInt == OP_DIFERENTE)
					acceso = 1;
				break;

			//Prioridad: And Or
			case 4:
				if (operadorInt == OP_AND || operadorInt == OP_OR)
					acceso = 1;
				break;

			//Prioridad: Asignacion
			case 5:
				if (operadorInt == OP_ASIGNACION){

					reinsertarOperador = (nodoOperador*)malloc(sizeof(nodoOperador));
					reinsertarOperador->operador = operadorInt;

					push(operadores, reinsertarOperador);

					listaCuadruplos = generarCuadruploAsignacion(listaCuadruplos, operandos, operadores, cuboSemantico, contadorIndice, availEntero, availDecimal, availTexto, availBoolean);
					return listaCuadruplos;
					
				}
				break;
			
			//Prioridad Lectura
			case 6:
				if (operadorInt == OP_LECTURA){

					reinsertarOperador = (nodoOperador*)malloc(sizeof(nodoOperador));
					reinsertarOperador->operador = operadorInt;

					push(operadores, reinsertarOperador);

					listaCuadruplos = generarCuadruploLectura(listaCuadruplos, operandos, operadores, contadorIndice);
					return listaCuadruplos;
				}
				break;

			//Prioridad Escritura	
			case 7:		
				if (operadorInt == OP_ESCRITURA){

					reinsertarOperador = (nodoOperador*)malloc(sizeof(nodoOperador));
					reinsertarOperador->operador = operadorInt;

					push(operadores, reinsertarOperador);

					listaCuadruplos = generarCuadruploEscritura(listaCuadruplos, operandos, operadores, contadorIndice);
					return listaCuadruplos;
				}
				break;
		}	

		//Checamos que el siguiente no sea una multiplicacion o division
		if (acceso == 1) {
			//Si si entonces ...
			//Sacamos los operandos de pila operandos
			operando2 = pop(operandos);
			operando1 = pop(operandos);

			//Variables para facilitar la lectura y manipulacion de datos
			operando1Tipo = ((nodoOperando*)(operando1->dato))->tipo;
			operando2Tipo = ((nodoOperando*)(operando2->dato))->tipo;
			operando1Temp = ((nodoOperando*)(operando1->dato))->temp;
			operando2Temp = ((nodoOperando*)(operando2->dato))->temp;
			
			//Sacamos de la pila operador2 y operador1
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
				listaCuadruplos = generaCuadruplo(listaCuadruplos, operando1, operando2, operador, resultadoAvail, *contadorIndice);

				//Checamos si no hubo algun error en la generacion de los cuadruplos
				if (listaCuadruplos != NULL) {
					//Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
					HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

					//Lo guardamos en operandos
					push(operandos, accederCuadruplo->resultado);

					//Si alguno de los operandos correspondia a un temporal ENTONCES lo regresamos al avail correspondiente
					//checamos que el operando1 sea temp
					if (operando1Temp == 1) {
						//Reinsercion del nodo en la memoria porque con el pop se habia liberado de memoria
						nuevoAvail = (nodoOperando*)malloc(sizeof(nodoOperando));
						nuevoAvail->temp = ((nodoOperando*)operando1->dato)->temp;
						nuevoAvail->tipo = ((nodoOperando*)operando1->dato)->tipo;
						strcpy(nuevoAvail->nombre, ((nodoOperando*)operando1->dato)->nombre);
						nuevoAvail->direccion = ((nodoOperando*)operando1->dato)->direccion;

						switch(operando1Tipo){
							case 0:
								push(availEntero, nuevoAvail);
								break;

							case 1:
								push(availDecimal, nuevoAvail);
								break;

							case 2:
								push(availTexto, nuevoAvail);
								break;

							case 3:
								push(availBoolean, nuevoAvail);
								break;
						}
					} 

					//checamos que el operando2 sea temp
					if (operando2Temp == 1) {
						//Reinsercion del nodo en la memoria porque con el pop se habia liberado de memoria
						nuevoAvail = (nodoOperando*)malloc(sizeof(nodoOperando));
						nuevoAvail->temp = ((nodoOperando*)operando2->dato)->temp;
						nuevoAvail->tipo = ((nodoOperando*)operando2->dato)->tipo;
						strcpy(nuevoAvail->nombre, ((nodoOperando*)operando2->dato)->nombre);
						nuevoAvail->direccion = ((nodoOperando*)operando2->dato)->direccion;

						switch(operando2Tipo){
							case 0:
								push(availEntero, nuevoAvail);
								break;
							case 1:
								push(availDecimal, nuevoAvail);
								break;
							case 2:
								push(availTexto, nuevoAvail);
								break;
							case 3:
								push(availBoolean, nuevoAvail);
								break;
						}
					}

					//aumentamos en 1 el contador de cuadruplos
					//int aux = *contadorIndice+1;
					*contadorIndice = *contadorIndice+1;

					return listaCuadruplos;
				} else {
					printf("Error al crear el cuadruplo\n");
					exit(1);
				}

			} else {
				//Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
				printf("Operacion Invalida\n");
				exit(1);
			}
		} else {
			//Si no era multiplicacion o division volver a meter a la pila de operadores

			reinsertarOperador = (nodoOperador*)malloc(sizeof(nodoOperador));
			reinsertarOperador->operador = operadorInt;

			push(operadores, reinsertarOperador);
			return listaCuadruplos;
		}
	} else {
		return listaCuadruplos;
	}
}

