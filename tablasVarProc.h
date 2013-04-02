#include "uthash.h"

//Hector Jesus De La Garza Ponce
//Oziel Alonso Garza Lopez

//Estructura Variables uthash-------------------------------------------------------
typedef struct directorio {
        char nombre[25];              /* key */
        int tipo;
        unsigned long direccion;
        UT_hash_handle hh;         /* makes this structure hashable */
} directorio;

//Estructura Procedimientos uthash-------------------------------------------------------
typedef struct directorioProcedimientos {
        char nombre[25];
        directorio *variablesLocales;
        UT_hash_handle hh;
}directorioProcedimientos;

//Estructura Objetos uthash-------------------------------------------------------
typedef struct directorioObjetos {
        char nombre[25];
        directorio *variablesGlobales;
        directorioProcedimientos *procedimientos;
        UT_hash_handle hh;
}directorioObjetos;

directorioObjetos* agregarVariablesLocales(directorioObjetos *objetos, char *objeto, char *funcion, char *nombre, unsigned short tipo, unsigned long direccion);
directorioObjetos* agregarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre, unsigned short tipo, unsigned long direccion);
directorioObjetos* agregarFuncion(directorioObjetos *objetos, char *objeto, char *nombre); 
directorioObjetos* agregarObjeto(directorioObjetos *objetos, char *nombre);
void imprimirObjetos(directorioObjetos *objetos);
