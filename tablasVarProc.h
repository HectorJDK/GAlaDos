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
	//Key
	char nombre[25];
	int regresa;
	int direccionCuadruplo;
	int permiso;
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
directorio* buscarVariablesLocales(directorioObjetos *objetos, char *objeto, char *funcion, char *nombre);
directorioObjetos* agregarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre, unsigned short tipo, unsigned long direccion);
directorio* buscarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre);
directorioObjetos* agregarFuncion(directorioObjetos *objetos, char *objeto, char *nombre); 
directorioProcedimientos* buscarFuncion(directorioObjetos *objetos, char *objeto, char *nombre);
directorioObjetos* agregarObjeto(directorioObjetos *objetos, char *nombre);
directorioObjetos* buscarObjeto(directorioObjetos *objetos, char *nombre);
void imprimirObjetos(directorioObjetos *objetos);
