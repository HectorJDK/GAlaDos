//Encabezado pilaChar.h
//La estructura almacaaaaaaaena un dato tipo char
//Estructuras para los nodos y la pila
typedef struct nodoChar_est
{
	char* dato;
	struct nodoChar_est *siguiente;		
} nodo;

typedef struct pilaChar_est
{	
	int tamanio;
	struct nodoChar_est *primero;
}pilaChar;


//Firmas de los metodos
void push(pilaChar *x, char* dato);
char* pop(pilaChar *x);
int pilaVacia(pilaChar *x);
void imprimirPilaChar(pilaChar * x);

