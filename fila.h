//Estructuras para los nodos y la fila
typedef struct nodo
{
	char* nombre;
	char* dato;
	char* tipo;
	struct nodo *siguiente;		
} nodo;

typedef struct fila
{	
	int tamanio;
	struct nodo *primero;
	struct nodo *ultimo;
}fila;
void push(fila *x, char* nombre, char* dato, char* tipo);
void pop(fila *x);
void imprimirFila(fila * x);
int filaVacia(fila *x);
