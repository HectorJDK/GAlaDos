#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablasVarProc.h"
#include "uthash.h"

//Hector Jesus De La Garza Ponce
//Oziel Alonso Garza Lopez

/*
* Funcion para agregar las variables locales al directorio de funciones.
*/
directorioObjetos* agregarVariablesLocales(directorioObjetos *objetos, char *objeto, char *funcion, char *nombre, unsigned short tipo, unsigned long direccion) {
        
        //Variables auxiliares
        directorioObjetos *existeO;
        directorioProcedimientos *existeP;
        directorio *temp;

        //Buscar el objeto en el directorio
        HASH_FIND_STR(objetos, objeto, existeO);  /* existe el objeto? */
        if (existeO) {
                //Buscar la funcion en el directorio
        	    HASH_FIND_STR(existeO->procedimientos, funcion, existeP);  /* existe el procedimiento? */
       			if (existeP) {
                    //Checar si la variable ya existe
	                HASH_FIND_STR(existeP->variablesLocales, nombre, temp);
	                if (temp==NULL) {
                            //Agregar la nueva variable al directorio
	                        temp = (directorio*)malloc(sizeof(directorio));
	                        strcpy(temp->nombre, nombre);
	                        temp->tipo = tipo;
	                        temp->direccion = direccion;
	                        HASH_ADD_STR(existeP->variablesLocales, nombre, temp);  
	                        return objetos;   
                    } else {
	                        printf("Error, la llave se repite");
	                }
	            } else {
               		printf("Error Funcion no se encuentra");
        		}
        } else {
            printf("Error Objeto no se encuentra");
        }
}

/*
* Funcion para agregar las variables globales al directorio de objetos.
*/
directorioObjetos* agregarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre, unsigned short tipo, unsigned long direccion) {
       
        //Variables auxiliares
        directorioObjetos *existe;
        directorio *temp;

        //Buscar el objeto en el directorio
        HASH_FIND_STR(objetos, objeto, existe); 
        if (existe) {
                //Checar si la variable ya existe
                HASH_FIND_STR(existe->variablesGlobales, nombre, temp);
                if (temp==NULL) {
                        //Agregar la nueva variable al directorio
                        temp = (directorio*)malloc(sizeof(directorio));
                        strcpy(temp->nombre, nombre);
                        temp->tipo = tipo;
                        temp->direccion = direccion;
                        HASH_ADD_STR(existe->variablesGlobales, nombre, temp);  
                        return objetos;   
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Objeto no se encuentra");
        }
}

/*
* Funcion para agregar las funciones al directorio de objetos.
*/
directorioObjetos* agregarFuncion(directorioObjetos *objetos, char *objeto, char *nombre) {
        
        //Variables auxiliares
        directorioProcedimientos *temp;
        directorioObjetos *existe;  

        //Buscar el objeto en el directorio
        HASH_FIND_STR(objetos, objeto, existe);  
        if (existe) {
                //Checar si la funcion ya existe
                HASH_FIND_STR(existe->procedimientos, nombre, temp);
                if (temp==NULL) {
                        //Agregar la nueva funcion al directorio
                        temp = (directorioProcedimientos*)malloc(sizeof(directorioProcedimientos));
                        strcpy(temp->nombre, nombre);                      
                        temp->variablesLocales = NULL;
                        HASH_ADD_STR(existe->procedimientos, nombre, temp); 
                        return objetos;   
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Funcion no se encuentra");
        }
}

/*
* Funcion para agregar objetos (main y clases) al directorio de objetos.
*/
directorioObjetos* agregarObjeto(directorioObjetos *objetos, char *nombre){
        
        //Variable auxiliar
        directorioObjetos *temp;

        //Buscar el objeto en el directorio
        HASH_FIND_STR(objetos, nombre, temp);  
        if (temp==NULL) {
                //Agregar el nuevo objeto al directorio
                temp = (directorioObjetos*)malloc(sizeof(directorioObjetos));
                strcpy(temp->nombre, nombre);
                temp->variablesGlobales = NULL;
                temp->procedimientos = NULL;
                HASH_ADD_STR(objetos, nombre, temp);  
                return objetos;    
        } else {
                printf("Error, la llave se repite");
        }       

}


/*
* Funcion para desplegar los elementos del directorio de objetos asi como los 
* elementos del directorio de funciones y variables que esten asociados
*/
void imprimirObjetos(directorioObjetos *objetos) {
			
			directorioObjetos *o;
	        directorioProcedimientos *s;
	        directorio *p;

	        //Imprimir tabla de objetos
	        for(o = objetos; o != NULL; o=(directorioObjetos*)(o->hh.next)){
		        printf("Nombre del objeto: %s \n", o->nombre);
		        //Imprimir variables globales (main)
		        for(p=o->variablesGlobales; p!= NULL; p=(struct directorio*)(p->hh.next)) {
		                printf("Sus variables globales son \n");
		                printf("Nombre de la variable: %s , tipo: %i , direccion: %lu \n", p->nombre, p->tipo, p->direccion);
		        }
		        //Imprimir procedimientos del objeto y sus tablas de variables
		        printf("Sus procedimientos son: \n");
		        for(s=o->procedimientos; s!= NULL; s=(directorioProcedimientos*)(s->hh.next)) {
		                printf("Nombre del procedimiento: %s \n", s->nombre);
		                printf("Sus variables son \n");
		                for(p=s->variablesLocales; p!= NULL; p=(struct directorio*)(p->hh.next)) {
		                        printf("Nombre de la variable: %s , tipo: %i , direccion: %lu \n", p->nombre, p->tipo, p->direccion);
		                }
		        }		        
	    	}
	}