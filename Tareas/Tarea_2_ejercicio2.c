#include <stdio.h>

FILE *abrir_archivo();
void mostrar_contenido_archivo(FILE *fil);

int main()
{
	FILE *archp;
	archp = abrir_archivo();
	mostrar_contenido_archivo(archp);
	return 0;
}

FILE *abrir_archivo()
{
	char nombre_archivo[30];
	printf("Ingrese nombre del archivo que va a utilizar:\n");
	scanf("%s", nombre_archivo);
	FILE *archp;
	if (archp = fopen(nombre_archivo, "r"))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	return NULL;
}

void mostrar_contenido_archivo(FILE *fil)
{

	char caracter;
	while((caracter = getc(fil)) != EOF)
	{
		printf("%c", caracter);
	}
	printf("\n");
	fclose(fil);
}
