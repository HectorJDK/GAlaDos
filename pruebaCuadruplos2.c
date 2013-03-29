#include "cuadruplos.h"
#include "cuboSemantico.h"
#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Pila generica
pila *p;
pila *op;

nodo *oper1;
nodo *oper2;
nodo *operador;

int cont = 0;
int *contadorIndice = &cont;

int contadorEntero = 1000;
int contadorDecimal = 2000;

cuadruplos *listaCuadruplos = NULL;
static int cuboSemantico[4][4][14];


int main()
{   
    
    inicializarSemantica(cuboSemantico);

    p = malloc(sizeof(pila));           
    p->tamanio = 0;                     
    p->primero = NULL;

    op = malloc(sizeof(pila));           
    op->tamanio = 0;                     
    op->primero = NULL;

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

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    //Checar si la variable esta declarada
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    nodoOperando prueba;
    prueba.temp = 0;
    prueba.tipo = 0;
    strcpy(prueba.nombre, "A");
    //La direccion la tendremos que sacar de tabla de variables
    prueba.direccion = contadorEntero;
    contadorEntero++;

    push(p,&prueba);

    //Accion 4 de la generacion de codigo intermedio
    listaCuadruplos = algoritmoCuadruplo(listaCuadruplos, p, op, operador, oper1, oper2, cuboSemantico, contadorIndice);
    //__________________________________________________________________________________________________________
    //Preguntamos si el operador encontrado es una multiplicacion
    //Encontramos el operador lo metemos en la pila
    nodoOperador prueba3;
    prueba3.operador = 3;

    push(op, &prueba3);

    //Nos metemos en FACTOR
    //Encontramos I y lo guardamos a la PilaOpernado
    nodoOperando prueba2;
    prueba2.temp = 0;
    prueba2.tipo = 1;
    strcpy(prueba2.nombre, "I");
    prueba2.direccion = contadorDecimal;
    contadorDecimal++;

    push(p,&prueba2);
    //Accion 4 de la generacion de codigo intermedio
    listaCuadruplos = algoritmoCuadruplo(listaCuadruplos, p, op, operador, oper1, oper2, cuboSemantico, contadorIndice);
 
        //Preguntamos si el operador encontrado es una multiplicacion
    //Encontramos el operador lo metemos en la pila
    nodoOperador prueba4;
    prueba4.operador = 3;

    push(op, &prueba4);

    //Nos metemos en FACTOR
    //Encontramos I y lo guardamos a la PilaOpernado
    nodoOperando prueba5;
    prueba5.temp = 0;
    prueba5.tipo = 1;
    strcpy(prueba5.nombre, "B");
    prueba5.direccion = contadorDecimal;
    contadorDecimal++;

    push(p,&prueba5);
    //Accion 4 de la generacion de codigo intermedio
    listaCuadruplos = algoritmoCuadruplo(listaCuadruplos, p, op, operador, oper1, oper2, cuboSemantico, contadorIndice);
 


    //----------------------------------------------------------------------------------------------------------------------------------------------------
    imprimeCuadruplos(listaCuadruplos, 1);
    free(p);
    return 0;
}

