#include <stdio.h>
#include <stdbool.h>


FILE *abrir_archivo(char *nombre_archivo, char *modo);

int main()
{
	FILE *archp = abrir_archivo("notas.txt", "r");
	return 0;
}

FILE *abrir_archivo(char *nombre_archivo, char *modo)
{
	FILE *archp;
	if (archp = fopen(nombre_archivo, modo))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	
	fclose(archp);
	return NULL;
}
