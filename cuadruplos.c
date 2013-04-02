#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuadruplos.h"
#include "uthash.h"

/*
* Clase que implementa una estructura de pila en C
*/

/*
*GenerarCuadruplo 
*Crea un cruadruplo y lo guarda en la lista de cuadruplos correspondiente, usa nodos en donde se tiene la informacion general
*/
cuadruplos* generaCuadruplo(cuadruplos *listaCuadruplos, nodo *oper1, nodo *oper2, nodo *op, int temp, int indice){
	cuadruplos *existe;
	nodoOperando *tempOper1;
	nodoOperando *tempOper2;
	nodoOperando *tempResultado;
	
	//Obtenemos una nueva direccion reservada para nuestro resultado, asi obtenemos independencia
	tempOper1 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempOper2 = (nodoOperando*)malloc(sizeof(nodoOperando));
	tempResultado = (nodoOperando*)malloc(sizeof(nodoOperando));
	

	//Checamos si se ha agregado el cuadruplo anteriromente
	HASH_FIND_INT(listaCuadruplos, &indice, existe);  /* id already in the hash? */
	if (existe==NULL) {
		//Si no se ha agregado el cuadruplo se crea y se llena sus datos
		existe = (cuadruplos*)malloc(sizeof(cuadruplos));

		//Pasamos todos los datos de oper1
		tempOper1->temp = ((nodoOperando*)oper1->dato)->temp;
		tempOper1->tipo = ((nodoOperando*)oper1->dato)->tipo;
		strcpy(tempOper1->nombre, ((nodoOperando*)oper1->dato)->nombre);
		tempOper1->direccion = ((nodoOperando*)oper1->dato)->tipo;

		//Pasamos todos los datos de oper2
		tempOper2->temp = ((nodoOperando*)oper2->dato)->temp;
		tempOper2->tipo = ((nodoOperando*)oper2->dato)->tipo;
		strcpy(tempOper2->nombre, ((nodoOperando*)oper2->dato)->nombre);
		tempOper2->direccion = ((nodoOperando*)oper2->dato)->tipo;

		//Genera el nodo resultado y lo asigna como temporal
		tempResultado->temp = 1;
		tempResultado->tipo = temp;
		//------------------------------------------------------
		//Borrar tronara el programa solo para pruebas
		sprintf(tempResultado->nombre, "temp_%d", indice);
		//------------------------------------------------------
		//strcpy(, strcat("temp", indice));		
		//Sacar direccion del avail
		//tempResultado.direccion = 1152;

		//Pasar todos los datos al recien creado cuadruplo
		existe->indice = indice;
		existe->operando1 = tempOper1;
		existe->operando2 = tempOper2;
		existe->operador = *(int*)(op->dato);
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

//Todo esto puede ir en una funcion
//----------------------------------------------------------------------------------------------------------------------------------------------------
cuadruplos* algoritmoCuadruplo (cuadruplos *listaCuadruplos, pila *p, pila *op, nodo *operador, nodo *oper1, nodo *oper2, int cuboSemantico[4][4][14], int *contadorIndice){
    
    int operando1Int;
	int operando2Int;
	int operadorInt;

	cuadruplos *accederCuadruplo;

    //Salimos de FACTOR
    //Checamos que la pila de operadores no este vacia
    if (pilaVacia(op) == 1) {
        //Si no esta vacia ...

        //Sacamos de la pila (momentariamente) para validar
        operador = pop(op);
        
        int banderaMultiplicacionDivision;;
        //Obtenemos el valor dentro del nodo que sacamos (este sera entero)
        banderaMultiplicacionDivision = *(int*)operador->dato;
        //Checamos que el siguiente no sea una multiplicacion o division
        if (banderaMultiplicacionDivision == 2 || banderaMultiplicacionDivision == 3) {
            //Si si entonces ...
            oper2 = pop(p);
            oper1 = pop(p);

            //Variables para facilitar la lectura y manipulacion de datos
            operando1Int = ((nodoOperando*)(oper1->dato))->tipo;
            operando2Int = ((nodoOperando*)(oper2->dato))->tipo;
            operadorInt = *(int*)(operador->dato);

            //Sacamos de la pila operador2 y operador1
            //Checamos que el cuadruplo sea posible de realizar
            if (cuboSemantico[operando1Int][operando2Int][operadorInt] >= 0) {
                //Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
                listaCuadruplos = generaCuadruplo(listaCuadruplos, oper1, oper2, operador, cuboSemantico[operando1Int][operando2Int][operadorInt], *contadorIndice);

                //Checamos si no hubo algun error en la generacion de los cuadruplos
                if (listaCuadruplos != NULL) {
                    //Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
                    HASH_FIND_INT(listaCuadruplos, contadorIndice, accederCuadruplo);

                    //Lo guardamos en operandos
                    push(p, accederCuadruplo->resultado);

                    //aumentamos en 1 el contador de cuadruplos
                    //int aux = *contadorIndice+1;
                    *contadorIndice = *contadorIndice+1;

                	return listaCuadruplos;
                } else {
                    exit(1);
                }
                
            } else {
                //Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
                printf("Operacion Invalida\n");
                exit(1);
            }
        } else {
            //Si no era multiplicacion o division volver a meter a la pila de operadores
            push(op, operador);
            return listaCuadruplos;
        }
    }
}
    //----------------------------------------------------------------------------------------------------------------------------------------------------

