#include <stdio.h>   /* gets */
#include <stdlib.h>  /* atoi, malloc */
#include <string.h>  /* strcpy */
#include "uthash.h"

typedef struct directorio {
        char nombre[20];              /* key */
        int tipo;
        unsigned long direccion;
        UT_hash_handle hh;         /* makes this structure hashable */
} directorio;

typedef struct directorioProcedimientos {
        char nombre[20];
        directorio *variablesLocales;
        UT_hash_handle hh;
}directorioProcedimientos;

typedef struct directorioObjetos {
        char nombre[20];
        directorio *variablesGlobales;
        directorioProcedimientos *procedimientos;
        UT_hash_handle hh;
}directorioObjetos;

directorioObjetos *objetos = NULL;

void add_variablesLocales(char *objeto, char *funcion, char *nombre, unsigned short tipo, unsigned long direccion) {
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

void add_variablesGlobales(char *objeto, char *nombre, unsigned short tipo, unsigned long direccion) {
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
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Objeto no se encuentra");
        }
}



void agregarFuncion(char *objeto, char *nombre) {
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
                } else {
                        printf("Error, la llave se repite");
                }
        } else {
                printf("Error Funcion no se encuentra");
        }
}

void agregarObjeto(char *nombre){
        directorioObjetos *temp;

        HASH_FIND_STR(objetos, nombre, temp);  /* id already in the hash? */
        if (temp==NULL) {
                temp = (directorioObjetos*)malloc(sizeof(directorioObjetos));
                strcpy(temp->nombre, nombre);
                temp->variablesGlobales = NULL;
                temp->procedimientos = NULL;
          HASH_ADD_STR(objetos, nombre, temp);  /* id: name of key field */
        } else {
                printf("Error, la llave se repite");
        }       

}
// struct directorio *find_variable(char *variable) {
//      struct directorio *s;

//      HASH_FIND_INT(variables, &variable, s);  /* s: output pointer */
//      return s;
// }

// void delete_variable(struct directorio *variable) {
//      HASH_DEL(variables, variable);  /* user: pointer to deletee */
//      free(variable);
// }

// void delete_all() {
//      struct directorio *current_variable, *tmp; 

//      HASH_ITER(hh, variables, current_variable, tmp) {
//      HASH_DEL(variables,current_variable);  /* delete it (users advances to next) */
//      free(current_variable);            /* free it */
//      } 
// }

// void imprimirVariables() {
//      struct directorio *s;

//      for(s=variables; s!= NULL; s=(struct directorio*)(s->hh.next)) {
//              printf("Nombre de la variable: %s , tipo: %i , direccion: %lu \n", s->nombre, s->tipo, s->direccion);
//      }
// }

	void imprimirFunciones() {
			directorioObjetos *o;
	        directorioProcedimientos *s;
	        directorio *p;

	        for(o = objetos; o != NULL; o=(directorioObjetos*)(o->hh.next)){
		        printf("Nombre del objeto: %s \n", o->nombre);
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

int main(int argc, char *argv[]) {
        char in[10];
        int running=1;
        struct directorio *s;



        while (running) {
                printf(" 1. add variable to main obj1\n");
                printf(" 2. add variable to otro obj1\n");
                printf(" 3. agregar variable main obj2\n");
                printf(" 4. agregar variable otro obj2\n");
                printf(" 5. crear objeto\n");
                printf(" 6. crear funcion otro\n");
                printf(" 7. crear funcion main\n");
                printf(" 8. Imprimir funciones con variables");
                printf(" 9. quit\n");
                gets(in);
                switch(atoi(in)) {
                        case 1:
                        printf("variable a main?\n");
                        add_variablesLocales("obj1","main" ,gets(in), 1, 15);
                        break;
                        case 2:
                        printf("variable a otro?\n");
                        add_variablesLocales("obj1","otro" ,gets(in), 1, 15);
                        break;
                        case 3:
                        add_variablesLocales("obj2","main" ,gets(in), 1, 15);
                        //printf("name?\n");
                        //s = find_variable(gets(in));
                        //printf("user: %s\n", s ? s->nombre : "unknown");
                        break;
                        case 4:
                        add_variablesLocales("obj2","otro" ,gets(in), 1, 15);
                        //printf("name?\n");
                        //s = find_variable(gets(in));
                        //printf("user: %s\n", s ? s->nombre : "unknown");
                        break;
                        case 5:
                        printf("funcion\n");
                        agregarObjeto("obj1");
                        agregarObjeto("obj2");
                        break;
                        case 6:
                        printf("funcion\n");
                        agregarFuncion("obj1","otro");
                        agregarFuncion("obj2","otro");
                        break;
                        case 7:
                        printf("funcion\n");
                        agregarFuncion("obj1", "main");
                        agregarFuncion("obj2", "main");
                        break;
                        case  8:
                        imprimirFunciones();
                        break;
                        case 9:
                        running=0;
                        break;
                }
        }

        //delete_all();  /* free any structures */
        return 0;
}