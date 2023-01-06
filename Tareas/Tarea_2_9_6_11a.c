#include <stdio.h>
#include <stdlib.h>

void leer_matriz(int **matriz, int largo);
void mostrar_matriz(int **matriz, int largo);
void suma_diagonal(int **matriz, int largo);
int **crear_matriz(int *largo);


int main()
{
	int *largo;
	int **matriz;
	matriz = crear_matriz(largo);
	leer_matriz(matriz, *largo);
	mostrar_matriz(matriz, *largo);
	suma_diagonal(matriz, *largo);
	return 0;
}

int **crear_matriz(int *largo)
{
	do
	{
		printf("Introduzca el tamaño de la matriz NxN mayor a 1: ");
		scanf("%d", largo);
	} while (*largo <= 1);
	int **matriz = malloc(sizeof(int *)*(*largo));
	for (int i = 0; i < *largo; i++)
	{
		matriz[i] = malloc(sizeof(int)*(*largo));
	}
	return matriz;
}

void mostrar_matriz(int **matriz, int largo)
{
	printf("Matriz de largo %d: \n", largo);
	for (int i = 0; i < largo; i++)
	{
		for (int j = 0; j < largo; j++)
		{
			printf("%2.d", matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void leer_matriz(int **matriz, int largo)
{
	printf("Introduzca la matriz: \n");
	for (int i = 0; i < largo; i++)
	{
		for (int j = 0; j < largo; j++)
		{

			printf("Valor de coordenada (%d, %d): ", i + 1, j + 1);
			scanf("%d", &matriz[i][j]);
		}
	}
	printf("\n");
}

void suma_diagonal(int **matriz, int largo)
{
	int acum = 0;
	for (int i = 0; i < largo; i++)
	{
		for (int j = 0; j < largo; j++)
		{
			if(i != j)
				acum += matriz[i][j];
		}
	}
	printf("La suma de todos los valores que no son de la diagonal principal es: %d\n", acum);
}