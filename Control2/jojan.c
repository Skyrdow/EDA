#include <stdio.h>
#include "grafo.h"

int hay_ciclo(grafo *g, int v1, int v2)
{
    for (int i = 0; i < g->n; i++)
    {
        if (PerteneceArista(g, i, v2))
            return 1;
    }
    return 0;
}
FILE *abrir_archivo(char *nom)
{
	FILE *fp = fopen(nom, "r");
	if( fp == NULL)
	{
		printf("Problema con el archivo\n");
		return NULL;
	}
	else
	{
		printf("Archivo leido\n");
		return fp;
	}
}
grafo *leer_grafo(FILE *fp)
{
    int n,m;
    fscanf(fp, "%d %d", &n, &m);
    grafo *g = CrearGrafo(n);
    int v1, v2, p;
    while (fscanf(fp, "%d %d %d", &v1, &v2 , &p) != EOF)
    {
        InsertarArista(g, v1-1, v2-1, p);
    }
    return g;
}
int main()
{
    grafo *g = leer_grafo(abrir_archivo("peo.txt"));
    MostrarGrafo(g);
    lista *a = ObtenerAdyacentes(g, 1);
    nodo *aux = a->ini;
    while (aux != NULL)
    {
        printf("a%d b%d ", aux->val, aux->pond);
        aux = aux->sig;
    }
    
}