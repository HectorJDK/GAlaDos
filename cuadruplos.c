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
			printf("Cuadruplo: %d | %d %s %s %s \n", temporal->indice, temporal->operador, temporal->operando1->nombre, temporal->operando2->nombre, temporal->resultado->nombre);
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

			//Prioridad: CLiclo
			case 6:
				break;

			case 7:
				if (operadorInt == OP_LECTURA){

					reinsertarOperador = (nodoOperador*)malloc(sizeof(nodoOperador));
					reinsertarOperador->operador = operadorInt;

					push(operadores, reinsertarOperador);

					listaCuadruplos = generarCuadruploLectura(listaCuadruplos, operandos, operadores, contadorIndice);
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

