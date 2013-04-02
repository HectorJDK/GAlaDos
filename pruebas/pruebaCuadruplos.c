#include "cuadruplos.h"
#include "cuboSemantico.h"
#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Pila generica
pila *p;
pila *op;

//Avail
pila *availEnteros;

nodo *oper1;
nodo *oper2;
nodo *operador;

int operando1Int;
int operando2Int;
int operadorInt;

cuadruplos *accederCuadruplo;

int contadorIndice = 0;

int contadorEntero = 1000;
int contadorDecimal = 2000;

cuadruplos *listaCuadruplos = NULL;
static int cuboSemantico[4][4][14];

void inicializarAvail(){
    int repeticion= 0;
    nodoOperando *datoEntero;

    for(repeticion = 0; repeticion < 1000; repeticion++) {
        datoEntero = (nodoOperando*)malloc(sizeof(nodoOperando));
        datoEntero->temp = 1;
        datoEntero->tipo = 0;
        sprintf(datoEntero->nombre, "tempInt_%d", repeticion);
        datoEntero->direccion = contadorEntero + repeticion;
        //printf("dir%p\n",&datoEntero);
        push(availEnteros, datoEntero);
    }    
}

int main()
{   
    inicializarSemantica(cuboSemantico);

    p = malloc(sizeof(pila));           
    p->tamanio = 0;                     
    p->primero = NULL;

    op = malloc(sizeof(pila));           
    op->tamanio = 0;                     
    op->primero = NULL;

    availEnteros = malloc(sizeof(pila));           
    availEnteros->tamanio = 0;                     
    availEnteros->primero = NULL;

    inicializarAvail();

    //Prueba
    //----------------------------------------------------------------------------------------------------------------------------------------------------  
    nodo *pruebaAux;
    pruebaAux = pop(availEnteros);

    printf("%s\n",((nodoOperando*)pruebaAux->dato)->nombre);
    
    pruebaAux = pop(availEnteros);    
    printf("%s\n",((nodoOperando*)pruebaAux->dato)->nombre);

    pruebaAux = pop(availEnteros);    
    printf("%s\n",((nodoOperando*)pruebaAux->dato)->nombre);

    pruebaAux = pop(availEnteros);    

    printf("%s\n",((nodoOperando*)pruebaAux->dato)->nombre);
    //----------------------------------------------------------------------------------------------------------------------------------------------------

    //Asumimos que los enteros empiezan en 1000
    //Asumimos que los decimales empiezan en 2000
    //Aqui empieza la simulacion del algoritmo
    //Algoritmo para cuadruplo:
    // A * I * B;
    // A es entero
    // I es decimal

    // * A I temp1
    // * temp1 B temp2

    //Entramos en SEXPRESION
    //Entramos en EXPRESION
    //Entramos en EXP
    //Entrams en TERMINO
    //Entramos en FACTOR
    //Encontramos A y lo guardamos a la PilaOpernado

//     //----------------------------------------------------------------------------------------------------------------------------------------------------
//     //Checar si la variable esta declarada
//     //----------------------------------------------------------------------------------------------------------------------------------------------------
//     nodoOperando prueba;
//     prueba.temp = 0;
//     prueba.tipo = 0;
//     strcpy(prueba.nombre, "A");
//     //La direccion la tendremos que sacar de tabla de variables
//     prueba.direccion = contadorEntero;
//     contadorEntero++;

//     push(p,&prueba);

//     //Todo esto puede ir en una funcion
//     //----------------------------------------------------------------------------------------------------------------------------------------------------
//     //Salimos de FACTOR
//     //Checamos que la pila de operadores no este vacia
//     if (pilaVacia(op) == 1) {
//         //Si no esta vacia ...

//         //Sacamos de la pila (momentariamente) para validar
//         operador = pop(op);
        
//         int banderaMultiplicacionDivision;;
//         //Obtenemos el valor dentro del nodo que sacamos (este sera entero)
//         banderaMultiplicacionDivision = *(int*)operador->dato;
//         //Checamos que el siguiente no sea una multiplicacion o division
//         if (banderaMultiplicacionDivision == 2 || banderaMultiplicacionDivision == 3) {
//             //Si si entonces ...
//             oper2 = pop(p);
//             oper1 = pop(p);

//             //Variables para facilitar la lectura y manipulacion de datos
//             operando1Int = ((nodoOperando*)(oper1->dato))->tipo;
//             operando2Int = ((nodoOperando*)(oper2->dato))->tipo;
//             operadorInt = *(int*)(operador->dato);

//             //Sacamos de la pila operador2 y operador1
//             //Checamos que el cuadruplo sea posible de realizar
//             if (cuboSemantico[operando1Int][operando2Int][operadorInt] >= 0) {
//                 //Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
//                 listaCuadruplos = generaCuadruplo(listaCuadruplos, oper1, oper2, operador, cuboSemantico[operando1Int][operando2Int][operadorInt], contadorIndice);

//                 //Checamos si no hubo algun error en la generacion de los cuadruplos
//                 if (listaCuadruplos != NULL) {
//                     //Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
//                     HASH_FIND_INT(listaCuadruplos, &contadorIndice, accederCuadruplo);

//                     //Lo guardamos en operandos
//                     push(p, accederCuadruplo->resultado);

//                     //aumentamos en 1 el contador de cuadruplos
//                     contadorIndice++;    
//                 } else {
//                     exit(1);
//                 }
                
//             } else {
//                 //Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
//                 printf("Operacion Invalida\n");
//                 exit(1);
//             }
//         } else {
//             //Si no era multiplicacion o division volver a meter a la pila de operadores
//             push(op, operador);
//         }
//     }
//     //----------------------------------------------------------------------------------------------------------------------------------------------------

//     //Preguntamos si el operador encontrado es una multiplicacion
//     //Encontramos el operador lo metemos en la pila
//     nodoOperador prueba3;
//     prueba3.operador = 3;

//     push(op, &prueba3);

//     //Nos metemos en FACTOR
//     //Encontramos I y lo guardamos a la PilaOpernado
//     nodoOperando prueba2;
//     prueba2.temp = 0;
//     prueba2.tipo = 0;
//     strcpy(prueba2.nombre, "I");
//     prueba2.direccion = contadorDecimal;
//     contadorDecimal++;

//     push(p,&prueba2);

//     //----------------------------------------------------------------------------------------------------------------------------------------------------
//     //Salimos de FACTOR
//     //Checamos que la pila de operadores no este vacia
//     if (pilaVacia(op) == 1) {
//         //Si no esta vacia ...

//         //Sacamos de la pila (momentariamente) para validar
//         operador = pop(op);
        
//         int banderaMultiplicacionDivision;;
//         //Obtenemos el valor dentro del nodo que sacamos (este sera entero)
//         banderaMultiplicacionDivision = *(int*)(operador->dato);
//         //Checamos que el siguiente no sea una multiplicacion o division
//         if (banderaMultiplicacionDivision == 2 || banderaMultiplicacionDivision == 3) {
//             //Si si entonces ...
//             oper2 = pop(p);
//             oper1 = pop(p);

//             //Variables para facilitar la lectura y manipulacion de datos
//             operando1Int = ((nodoOperando*)(oper1->dato))->tipo;
//             operando2Int = ((nodoOperando*)(oper2->dato))->tipo;
//             operadorInt = *(int*)(operador->dato);

//             //Sacamos de la pila operador2 y operador1
//             //Checamos que el cuadruplo sea posible de realizar
//             if (cuboSemantico[operando1Int][operando2Int][operadorInt] >= 0) {
//                 //Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
//                 listaCuadruplos = generaCuadruplo(listaCuadruplos, oper1, oper2, operador, cuboSemantico[operando1Int][operando2Int][operadorInt], contadorIndice);

//                 //Checamos si no hubo algun error en la generacion de los cuadruplos
//                 if (listaCuadruplos != NULL) {
//                     //Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
//                     HASH_FIND_INT(listaCuadruplos, &contadorIndice, accederCuadruplo);

//                     //Lo guardamos en operandos
//                     push(p, accederCuadruplo->resultado);

//                     //aumentamos en 1 el contador de cuadruplos
//                     contadorIndice++;    
//                 } else {
//                     exit(1);
//                 }
                
//             } else {
//                 //Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
//                 printf("Operacion Invalida\n");
//                 exit(1);
//             }
//         } else {
//             //Si no era multiplicacion o division volver a meter a la pila de operadores
//             push(op, operador);
//         }
//     }
//     //----------------------------------------------------------------------------------------------------------------------------------------------------

//     //Preguntamos si el operador encontrado es una multiplicacion
//     //Encontramos el operador lo metemos en la pila
//     nodoOperador prueba4;
//     prueba4.operador = 3;

//     push(op, &prueba4);

//     //Nos metemos en FACTOR
//     //Encontramos I y lo guardamos a la PilaOpernado
//     nodoOperando prueba5;
//     prueba5.temp = 0;
//     prueba5.tipo = 0;
//     strcpy(prueba5.nombre, "B");
//     prueba5.direccion = contadorDecimal;
//     contadorDecimal++;

//     push(p,&prueba5);


//     //----------------------------------------------------------------------------------------------------------------------------------------------------
//     //Salimos de FACTOR
//     //Checamos que la pila de operadores no este vacia
//     if (pilaVacia(op) == 1) {
//         //Si no esta vacia ...

//         //Sacamos de la pila (momentariamente) para validar
//         operador = pop(op);
        
//         int banderaMultiplicacionDivision;;
//         //Obtenemos el valor dentro del nodo que sacamos (este sera entero)
//         banderaMultiplicacionDivision = *(int*)(operador->dato);
//         //Checamos que el siguiente no sea una multiplicacion o division
//         if (banderaMultiplicacionDivision == 2 || banderaMultiplicacionDivision == 3) {
//             //Si si entonces ...
//             oper2 = pop(p);
//             oper1 = pop(p);

//             //Variables para facilitar la lectura y manipulacion de datos
//             operando1Int = ((nodoOperando*)(oper1->dato))->tipo;
//             operando2Int = ((nodoOperando*)(oper2->dato))->tipo;
//             operadorInt = *(int*)(operador->dato);

//             //Sacamos de la pila operador2 y operador1
//             //Checamos que el cuadruplo sea posible de realizar
//             if (cuboSemantico[operando1Int][operando2Int][operadorInt] >= 0) {
//                 //Generamos el cuadruplo y lo guardamos en la lista de cuadruplos actuales
//                 listaCuadruplos = generaCuadruplo(listaCuadruplos, oper1, oper2, operador, cuboSemantico[operando1Int][operando2Int][operadorInt], contadorIndice);

//                 //Checamos si no hubo algun error en la generacion de los cuadruplos
//                 if (listaCuadruplos != NULL) {
//                     //Buscamos el cuadruplo reciencreado para guardar su resultado en la tabla de operandos el cual lo pondra en 
//                     HASH_FIND_INT(listaCuadruplos, &contadorIndice, accederCuadruplo);

//                     //Lo guardamos en operandos
//                     push(p, accederCuadruplo->resultado);

//                     //aumentamos en 1 el contador de cuadruplos
//                     contadorIndice++;    
//                 } else {
//                     exit(1);
//                 }
                
//             } else {
//                 //Si la operacion es invalida se debe desplegar el mensaje correspondiente y terminar
//                 printf("Operacion Invalida\n");
//                 exit(1);
//             }
//         } else {
//             //Si no era multiplicacion o division volver a meter a la pila de operadores
//             push(op, operador);
//         }
//     }
//     //----------------------------------------------------------------------------------------------------------------------------------------------------

//     //----------------------------------------------------------------------------------------------------------------------------------------------------
//     imprimeCuadruplos(listaCuadruplos, 0);
//     free(p);
//     return 0;
 }

