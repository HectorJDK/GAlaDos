#include "cuboSemantico.h"
#include <stdio.h>

static int cuboSemantico[5][5][14];

int main(int argc, char const *argv[])
{
	inicializarSemantica(cuboSemantico);
	printf("%i\n", cuboSemantico[BOOLEANO][TEXTO][AND]);
	return 0;
}