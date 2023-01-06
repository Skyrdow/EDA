#include <stdio.h>

#define A_SALIDA "salida.txt"

FILE *abrir_archivo(char *nom);
void escribir_datos(FILE *archp);

int main()
{
	FILE *archp = abrir_archivo(A_SALIDA);
	escribir_datos(archp);
	return 0;
}

FILE *abrir_archivo(char *nom)
{
	FILE *archp;
	if (archp = fopen(nom, "w"))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	return NULL;
}

void escribir_datos(FILE *archp)
{
	int iteracion;
	printf("Ingrese el numero de iteraciones: ");
	scanf("%d", &iteracion);
	fprintf(archp, "HOLA MUNDO!!.. estoy escribiendo en este archivo ");
	fprintf(archp, "datos de %d personas\n", iteracion);
	int edad;
	int i;
	for (i = 1; i <= iteracion; i++)
	{
		edad = 20+i;
		fprintf(archp, "Edad y nombre persona %d:\n", i);
		fprintf(archp, "\t%d %s%d\n\n",edad,"nombre",i);
	}
	printf("Contenido escrito correctamente\n");
	fclose(archp);
}