#include <stdio.h>

FILE *abrir_archivo(char *nom_archivo, char *modo);
void escribir_y_mostrar(FILE *entrada, FILE *salida);

int main(int argc, char *argv[]) // arg 1: archivo de entrada arg 2: archivo de salida
{
	FILE *fp_e,*fp_s;
	fp_e = abrir_archivo(argv[2],"r");
	fp_s = abrir_archivo(argv[3],"w");
	escribir_y_mostrar(fp_e,fp_s);
}

FILE *abrir_archivo(char *nom_archivo, char *modo)
{
	FILE *archp;
	if (archp = fopen(nom_archivo, modo))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	return NULL;
}

void escribir_y_mostrar(FILE *entrada, FILE *salida)
{	
	char caracter;
	while((caracter = getc(entrada)) != EOF)
	{
		putc(caracter, salida);
		printf("%c", caracter);
	}
	printf("\n");
	printf("Archivo creado y escrito\n");
	fclose(entrada);
	fclose(salida);
}
