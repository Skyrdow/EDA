#include <stdio.h>
#include <stdlib.h>
#define LARGO_LIN 200

FILE *abrir_archivo( char *nomA_E, char *modo_lec);
void escribir_contenido_archivo(FILE *fil_e, FILE *fil_s);
char *leer_nombre_archivo(char *);

int main()
{
	FILE *fp_e, *fp_s;
	char *nombre_entrada = leer_nombre_archivo("entrada");
	char *nombre_salida = leer_nombre_archivo("salida");
	fp_e = abrir_archivo(nombre_entrada, "r");
	fp_s = abrir_archivo(nombre_salida, "w");
	escribir_contenido_archivo(fp_e, fp_s);
	return 0;
}

char *leer_nombre_archivo(char *str)
{
	int largo;
	printf("Introduzca el largo del nombre: ");
	scanf("%d", largo);
	char *nombre = (char *)malloc(sizeof(char) * largo);
	printf("Introduzca el nombre del archivo de %s: ", str);
	scanf("%s", nombre);
	return nombre;
}
FILE *abrir_archivo(char *nomA_E, char *modo_lec)
{
	FILE *archp;
	if (archp = fopen(nomA_E, modo_lec))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	return NULL;
}

void escribir_contenido_archivo(FILE *fil_e, FILE *fil_s)
{
	char linea[LARGO_LIN];
	while((fgets(linea, LARGO_LIN, fil_e)) != NULL)
	{
		fputs(linea, fil_s);
	}
	fclose(fil_e);
	fclose(fil_s);
}
