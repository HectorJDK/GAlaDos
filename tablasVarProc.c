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
							printf("Error Variable %s ya esta delcarada \n", nombre);
							exit(1);
					}
				} else {
					printf("Error Funcion %s no se encuentra declarada \n", funcion);
					exit(1);
				}
		} else {
			printf("Error Clase %s no se encuentra declarada \n", objeto);
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
						//Primero buscamos en nuestra variables locales, si es null el resultado debemos buscar en globales
						return NULL;
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
						printf("Error Variable %s ya esta delcarada \n", nombre);
						exit(1);
				}
		} else {
				printf("Error Clase %s no se encuentra declarada \n", objeto);
				exit(1);
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
					printf("Error Variable %s no esta delcarada \n", nombre);
					exit(1);
				} else {
					//Si la variable existe regresar el directorio de la variable
					return temp;
				}
		} else {
			printf("Error Clase %s no se encuentra declarada \n", objeto);
			exit(1);
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
					printf("Error Funcion %s ya se encuentra declarada \n", nombre);
					exit(1);
				}
		} else {
				printf("Error Clase %s no se encuentra declarada \n", objeto);
				exit(1);
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
					printf("Eror Funcion %s no declarada", nombre);
					exit(1);
				} else {
					//Si existe regresamos el directorioProcedmientos
					return temp;
				}
		} else {
			printf("Error Clase %s no se encuentra declarada \n", objeto);
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
			printf("Error Clase %s ya se encuentra declarada \n", nombre);
			exit(1);

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
			printf("Error Clase %s no se encuentra declarada \n", nombre);
			exit(1);
		} else {
			//Regresamos al apuntador al directorio del objeto
			return temp;
		}       
}

/*
* Funcion para agregar objetos (main y clases) al directorio de objetos.
*/
directorio* agregarConstante(directorio *constantes, char *nombre, unsigned short tipo, int direccion){
		
		//Variable ausxiliar
		directorio *temp;

		//Buscar la constante en el directorio
		HASH_FIND_STR(constantes, nombre, temp);  
		if (temp==NULL) {
				//Agregar la nueva constante al directorio
				temp = (directorio*)malloc(sizeof(directorio));
				strcpy(temp->nombre, nombre);
				temp->direccion = direccion;
				temp->tipo = tipo;
				HASH_ADD_STR(constantes, nombre, temp);  
				return constantes;    
		}else {
			//No hacer nada, porque ya esta grabada
			return constantes;
		}
}

/*
* Funcion para agregar objetos (main y clases) al directorio de objetos.
*/
directorio* buscarConstante(directorio *constantes, char *nombre){
		
		//Variable auxiliar
		directorio *temp;

		//Buscar el objeto en el directorio
		HASH_FIND_STR(constantes, nombre, temp);  
		if (temp==NULL) {
			//SI no existe solo regresamos NULL
			return NULL;
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

/*
* Funcion para escribir en un archivo los elementos del directorio de objetos asi como los 
* elementos del directorio de funciones y variables que esten asociados.
* El archivo se almacenará en disco.
*/
void generarDatos(directorioObjetos *objetos) {
	
	//Estructuras auxiliares		
	directorioObjetos *o;
	directorioProcedimientos *s;
	directorio *p;
	
	//Crear el archivo y guardarlo en carpeta raiz
	FILE *fp;
	fp = fopen("datos.txt", "w");
		
	fprintf(fp,  "<GALaDos>\n");
			//Imprimir tabla de objetos
			for(o = objetos; o != NULL; o=(directorioObjetos*)(o->hh.next)){
				fprintf(fp,  "<%s>\n", o->nombre);
						

				//Imprimir variables globales (main)
				fprintf(fp,  "<variablesGlobales>\n");
				for(p=o->variablesGlobales; p!= NULL; p=(struct directorio*)(p->hh.next)) {						
							fprintf(fp,  "<%lu>\n", p->direccion);
							fprintf(fp,  "<nombre>%s</nombre>\n", p->nombre);
							fprintf(fp,  "<tipo>%i</tipo>\n", p->tipo);
							fprintf(fp,  "</%lu>\n", p->direccion);
				}
				fprintf(fp,  "</variablesGlobales>\n");

				//Imprimir procedimientos del objeto y sus tablas de variables
				fprintf(fp,  "<procedimientos>\n");
				for(s=o->procedimientos; s!= NULL; s=(directorioProcedimientos*)(s->hh.next)) {
						fprintf(fp,  "<%s>\n", s->nombre);
							fprintf(fp,  "<regresa>%i</regresa>\n", s->regresa);
							fprintf(fp,  "<permiso>%i</permiso>\n", s->permiso);
							fprintf(fp,  "<direccionCuadruplo>%i</direccionCuadruplo>\n", s->direccionCuadruplo);
							
						fprintf(fp,  "<variablesLocales>\n");
						for(p=s->variablesLocales; p!= NULL; p=(struct directorio*)(p->hh.next)) {
							fprintf(fp,  "<%lu>\n", p->direccion);
							fprintf(fp,  "<nombre>%s</nombre>\n", p->nombre);
							fprintf(fp,  "<tipo>%i</tipo>\n", p->tipo);
							fprintf(fp,  "</%lu>\n", p->direccion);
						}
						fprintf(fp,  "</variablesLocales>\n");
						fprintf(fp,  "</%s>\n", s->nombre);
				}
				fprintf(fp,  "</procedimientos>\n");
				fprintf(fp,  "</%s>\n", o->nombre);						       
			}
		fprintf(fp,  "</GALaDos>\n");
	}
	