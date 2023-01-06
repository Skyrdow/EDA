#include <stdio.h>

FILE *abrir_archivo(char *nom);
void mostrar_datos(FILE *archp);

int main()
{
	FILE *archp = abrir_archivo("datos.txt");
	mostrar_datos(archp);
	return 0;
}

FILE *abrir_archivo(char *nom)
{
	FILE *archp;
	if (archp = fopen(nom, "r"))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	return NULL;
}

void mostrar_datos(FILE *archp)
{
	int n1,n2;
	float f1;
	while(!feof(archp))
	{
		fscanf(archp, "%d %d %f", &n1, &n2, &f1);
		printf("%d %d %f\n", n1, n2, f1);
	}
	fclose(archp);
}
