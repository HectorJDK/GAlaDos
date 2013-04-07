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
		directorioObjetos *exiteObjeto;
		directorioProcedimientos *existeProcedimiento;
		directorio *temp;

		//Buscar el objeto en el directorio
		HASH_FIND_STR(objetos, objeto, exiteObjeto);  /* existe el objeto? */
		if (exiteObjeto) {
				//Buscar la funcion en el directorio
				HASH_FIND_STR(exiteObjeto->procedimientos, funcion, existeProcedimiento);  /* existe el procedimiento? */
				if (existeProcedimiento) {
					//Checar si la variable ya existe
					HASH_FIND_STR(existeProcedimiento->variablesLocales, nombre, temp);
					if (temp==NULL) {
							//Agregar la nueva variable al directorio
							temp = (directorio*)malloc(sizeof(directorio));
							strcpy(temp->nombre, nombre);
							temp->tipo = tipo;
							temp->direccion = direccion;
							HASH_ADD_STR(existeProcedimiento->variablesLocales, nombre, temp);  
							return objetos;   
					} else {
							printf("Error, la llave se repite \n");
							exit(1);
					}
				} else {
					printf("Error Funcion no se encuentra\n");
					exit(1);
				}
		} else {
			printf("Error Objeto no se encuentra\n");
			exit(1);
		}
}

/*
* Funcion para buscar en la tabla de variables de una funcion, solo regresa el directorio de la variable para ser usada
*/
directorio* buscarVariablesLocales(directorioObjetos *objetos, char *objeto, char *funcion, char *nombre) {
		
		//Variables auxiliares
		directorioObjetos *exiteObjeto;
		directorioProcedimientos *existeProcedimiento;
		directorio *temp;

		//Buscar el objeto en el directorio
		HASH_FIND_STR(objetos, objeto, exiteObjeto);  /* existe el objeto? */
		if (exiteObjeto) {
				//Buscar la funcion en el directorio
				HASH_FIND_STR(exiteObjeto->procedimientos, funcion, existeProcedimiento);  /* existe el procedimiento? */
				if (existeProcedimiento) {
					//Checar si la variable ya existe
					HASH_FIND_STR(existeProcedimiento->variablesLocales, nombre, temp);
					if (temp == NULL) {
						printf("Error la variable: %s no ha sido declarada\n", nombre);
						exit(1);
					} else {
							return temp;
					}
				} else {
					printf("Error Funcion: %s no declarada\n", funcion);
					exit(1);
				}
		} else {
			printf("Error Clase: %s no declarada\n", objeto);
			exit(1);
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
* Funcion para buscar en la tabla de variables globales de funcion, solo regresa el directorio de la variable para ser usada
*/
directorio* buscarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre) {
		
		//Variables auxiliares
		directorioObjetos *existe;
		directorio *temp;

		//Buscar el objeto en el directorio
		HASH_FIND_STR(objetos, objeto, existe); 
		if (existe) {
				//Checar si la variable ya existe
				HASH_FIND_STR(existe->variablesGlobales, nombre, temp);
				//Si ya existe manejar el error y terminar compilacion
				if (temp == NULL) {
					printf("Error la variable no ha sido declarada");
					exit(1);
				} else {
					//Si la variable existe regresar el directorio de la variable
					return temp;
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
* Funcion para buscar una funcione en el directorio del objeto
*/
directorioProcedimientos* buscarFuncion(directorioObjetos *objetos, char *objeto, char *nombre) {
		
		//Variables auxiliares
		directorioProcedimientos *temp;
		directorioObjetos *existe;  

		//Buscar el objeto en el directorio
		HASH_FIND_STR(objetos, objeto, existe);  
		if (existe) {
				//Checar si la funcion ya existe
				HASH_FIND_STR(existe->procedimientos, nombre, temp);
				if (temp == NULL) {
					//La funcion no esta declarada en el objeto
					printf("Funcion no declarada");
					exit(1);
				} else {
					//Si existe regresamos el directorioProcedmientos
					return temp;
				}
		} else {
				printf("Error clase no existe");
				exit(1);
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
* Funcion para agregar objetos (main y clases) al directorio de objetos.
*/
directorioObjetos* buscarObjeto(directorioObjetos *objetos, char *nombre){
		
		//Variable auxiliar
		directorioObjetos *temp;

		//Buscar el objeto en el directorio
		HASH_FIND_STR(objetos, nombre, temp);  
		if (temp==NULL) {
			//Si no existe el objeto marcar error
			printf("Clase no declarada");
			exit(1);
		} else {
			//Regresamos al apuntador al directorio del objeto
			return temp;
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