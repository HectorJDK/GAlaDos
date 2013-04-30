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

//Estructura Variables uthash-------------------------------------------------------
typedef struct directorioParametros {
	int numeroParametro;              /* key */
	int tipo;
	UT_hash_handle hh;         /* makes this structure hashable */
} directorioParametros;

//Estructura Procedimientos uthash-------------------------------------------------------
typedef struct directorioProcedimientos {
	//Key
	char nombre[25];
	int regresa;
	int permiso;
	int direccionCuadruplo;
	directorioParametros *parametros;
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
directorioObjetos* agregarParametros(directorioObjetos *objetos, char *objeto, char *funcion, int tipo, int cantidadParametros);
int checarParametro(directorioObjetos *objetos, char *objeto, char *funcion, int numeroParametro, int tipo);
directorioObjetos* agregarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre, unsigned short tipo, unsigned long direccion);
directorio* buscarVariablesGlobales(directorioObjetos *objetos, char *objeto, char *nombre);
directorioObjetos* agregarFuncion(directorioObjetos *objetos, char *objeto, char *nombre);
directorioProcedimientos* buscarFuncion(directorioObjetos *objetos, char *objeto, char *nombre);
directorioObjetos* agregarObjeto(directorioObjetos *objetos, char *nombre);
directorioObjetos* buscarObjeto(directorioObjetos *objetos, char *nombre);
directorio* agregarConstante(directorio *constantes, char *nombre, unsigned short tipo, int direccion);
directorio* buscarConstante(directorio *constantes, char *nombre);
void imprimirObjetos(directorioObjetos *objetos);
void generarDatos(directorioObjetos *objetos, directorio *constantes );