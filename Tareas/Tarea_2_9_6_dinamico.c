#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double producto_escalar(int n, double a[n], double b[n]);
double norma(int n, double a[n]);
double cosn_angulo_vect(int n, double a[n], double b[n]);
double *crear_vector();
int obtener_dimension();

int main()
{
	int dimension = obtener_dimension(); // dimensión de vectores
	double *a = crear_vector(dimension);
	double *b = crear_vector(dimension);
	printf("producto_escalar %f\n", producto_escalar(dimension, a, b));
	printf("norma del primero %f\n", norma(dimension, a));
	printf("norma norma del segundo %f\n", norma(dimension, b));
	printf("cosn_angulo_vect %f\n", cosn_angulo_vect(dimension, a, b));
	printf("\n");
	return 0;
}

int obtener_dimension()
{
	int largo;
	printf("Ingresar el largo del vector: ");
	scanf("%d", &largo);
	return largo;
}

double *crear_vector(int largo)
{
	double *a = (double *)malloc(sizeof(double)*largo);
	for (int i = 0; i < largo; i++)
	{
		printf("Vector de largo %d, elemento %d: ", largo, i+1);
		scanf("%lf", &a[i]);
	}
	printf("Vector creado\n");
	return a;
}
double producto_escalar(int n, double a[n], double b[n])
{
	double acum = 0;
	for (int i = 0; i < n; i++)
	{
		acum += a[i] * b[i];
	}
	return acum;
}

double norma(int n, double a[n])
{
	return sqrt(producto_escalar(n, a, a));
}

double cosn_angulo_vect(int n, double a[n], double b[n])
{
	return producto_escalar(n,a,b) / (norma(n, a) * norma(n, b));
}