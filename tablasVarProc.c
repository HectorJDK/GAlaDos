#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablasVarProc.h"
#include "uthash.h"

directorioObjetos* agregarVariablesLocales(directorioObjetos *objetos, char *objeto, char *funcion, char *nombre, unsigned short tipo, unsigned long direccion) {
        directorioObjetos *existeO;
        directorioProcedimientos *existeP;
        directorio *temp;

        HASH_FIND_STR(objetos, objeto, existeO);  /* existe el objeto? */
        if (existeO) {
        	    HASH_FIND_STR(existeO->procedimientos, funcion, existeP);  /* existe el procedimiento? */
       			if (existeP) {
	                HASH_FIND_STR(existeP->variablesLocales, nombre, temp);
	                if (temp==NULL) {
	                        temp = (directorio*)malloc(sizeof(directorio));
	                        strcpy(temp->nombre, nombre);
	                        temp->tipo = tipo;
	                        temp->direccion = direccion;
	                        HASH_ADD_STR(existeP->variablesLocales, nombre, temp);  /* id: name of key field */
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

directorioObjetos* agregarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre, unsigned short tipo, unsigned long direccion) {
        directorioObjetos *existe;
        directorio *temp;

        HASH_FIND_STR(objetos, objeto, existe);  /* id already in the hash? */
        if (existe) {
                HASH_FIND_STR(existe->variablesGlobales, nombre, temp);
                if (temp==NULL) {
                        temp = (directorio*)malloc(sizeof(directorio));
                        strcpy(temp->nombre, nombre);
                        temp->tipo = tipo;
                        temp->direccion = direccion;
                        HASH_ADD_STR(existe->variablesGlobales, nombre, temp);  /* id: name of key field */
                        return objetos;   
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Objeto no se encuentra");
        }
}


directorioObjetos* agregarFuncion(directorioObjetos *objetos, char *objeto, char *nombre) {
        directorioProcedimientos *temp;
        directorioObjetos *existe;  

        HASH_FIND_STR(objetos, objeto, existe);  /* id already in the hash? */
        if (existe) {
                HASH_FIND_STR(existe->procedimientos, nombre, temp);
                if (temp==NULL) {
                        temp = (directorioProcedimientos*)malloc(sizeof(directorioProcedimientos));
                        strcpy(temp->nombre, nombre);                      
                        temp->variablesLocales = NULL;
                        HASH_ADD_STR(existe->procedimientos, nombre, temp);  /* id: name of key field */
                        return objetos;   
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Funcion no se encuentra");
        }
}

directorioObjetos* agregarObjeto(directorioObjetos *objetos, char *nombre){
        directorioObjetos *temp;

        HASH_FIND_STR(objetos, nombre, temp);  /* id already in the hash? */
        if (temp==NULL) {
                temp = (directorioObjetos*)malloc(sizeof(directorioObjetos));
                strcpy(temp->nombre, nombre);
                temp->variablesGlobales = NULL;
                temp->procedimientos = NULL;
                HASH_ADD_STR(objetos, nombre, temp);  /* id: name of key field */
                return objetos;    
        } else {
                printf("Error, la llave se repite");
        }       

}

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