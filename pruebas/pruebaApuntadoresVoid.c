#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
   int type;
   void* info;
} Data;

struct X { 
    int i; 
};

Data* insert_data(int t, void* s)
{
    Data * d = malloc(sizeof(Data));
    d->type = t;
    d->info = s;
    
    return d;
}
 
Data* prueba(Data* d){
    double id = 12.8687;
    d = insert_data(1, &id);
    return d;
}

 
int main()
{
    // struct X x;
    // x.i = 5;
    // int id = 12;
    // Data* d = insert_data(1, &id);
    Data* d;
    d = prueba(d);
    
    if (d->type == 1)
    {
        double resultado = *(double*)(d->info);
        printf("Ya sabemos: %f\n", resultado);
    }

    free(d);
 
    return 0;
}