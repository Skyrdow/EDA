#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

#define INT_MAX 2147483647

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
grafo *leer_grafo(FILE *fp, int val)
{
    int n,m;
    fscanf(fp, "%d %d", &n, &m);
    grafo *g = CrearGrafo(n);
    int v1, v2, p;
    while (fscanf(fp, "%d %d %d", &v1, &v2 , &p) != EOF)
    {
        InsertarArista(g, v1-val, v2-val, p);
    }
    return g;
}

int aristas_sobre_prom(grafo *g)
{
    int **aristas = ObtenerAristas(g);
    float acum = 0;
    for (int i = 0; i < g->m; i++)
    {
        // peso total
        acum += aristas[i][2];
    } 
    // peso promedio
    acum = acum / g->m;
    int res = 0;
    for (int i = 0; i < g->m; i++)
    {
        // se compara para saber cuantas aristas estan sobre el promedio
        if (acum < aristas[i][2])
        {
            res++;
        }
    }
    return res;
}

float grado_promedio(grafo *g)
{
    int *grados = ObtenerGrados(g);
    int acum = 0;
    for (int i = 0; i < g->n; i++)
    {
        acum += grados[i];
    }
    return acum / g->n;
}

float densidad_grafo(grafo *g)
{
    float res = (2*g->m);
    return res / (g->n*(g->n - 1));
}

// retorna si existe un ciclo al agregar una arista
int hay_ciclo(grafo *g, int v1, int v2)
{
    for (int i = 0; i < g->n; i++)
    {
        if (PerteneceArista(g, i, v2))
            return 1;
    }
    return 0;
}

grafo *PRIM(grafo *g)
{
    grafo *res = CrearGrafo(g->n);
    int **aristas = ObtenerAristas(g);
    lista *conectados = CrearLista();

    lista **ady_no_conectados = malloc(sizeof(lista*)* g->n);
    for (int i = 0; i < g->n; i++)
    {
        ady_no_conectados[i] = CrearLista();
    }
    // se agrega el nodo 0 como inicio para prim
    AgregarFin(conectados, 0, 1);

    nodo *aux_conectados = conectados->ini;
    while (LargoLista(conectados) != g->n)
    {
        printf("a");
        // se obtienen los adyacentes del ultimo vertice conectado
        lista *aux_ady_l = ObtenerAdyacentes(g, aux_conectados->val);
        nodo *aux_ady = aux_ady_l->ini;
        while (aux_ady != NULL)
        {
            // Se agrega a la lista de ady no conectados, del ultimo conectado, los adyacentes que no estan conectados
            if (IsInLista(conectados, aux_ady->val) == 0)
            {
                AgregarFin(ady_no_conectados[aux_conectados->val], aux_ady->val, aux_ady->pond);
            }
            aux_ady = aux_ady->sig;
        }
        // buscar ady no conectado con ponderacion minima
        int min = INT_MAX, 
            ante_min, 
            suce_min;
        for (int i = 0; i < g->n; i++)
        {
            nodo *aux = ady_no_conectados[i]->ini;
            while (aux != NULL)
            {
                if(aux->pond < min)
                {
                    min = aux->pond;
                    ante_min = i;
                    suce_min = aux->val;
                }
                aux = aux->sig;
            }
        }
        
        // se conecta al grafo
        AgregarFin(conectados, suce_min, 1);
        
        // falta eliminar de ady no conectados la arista recien agregada
        EliminarElemento(ady_no_conectados[ante_min], suce_min);        
        
        // se inserta la arista minima adyacente no conectada
        InsertarArista(res, ante_min, suce_min, min);
        
        aux_conectados = aux_conectados->sig;
    }
    printf("Arbol creado:\n");
    return res;

}

int main(int argc, char *argv[])
{
    grafo *g;
    printf("Cargando archivo\n");
    FILE *fp = abrir_archivo(argv[2]);
    if (fp == NULL)
        return 1;
    int menu;   
    do
    {
        printf("Seleccione modo: \n1.Aristas desde 0\n2.Aristas desde 1 (este modo transformara las aristas para que empiecen desde 0)\n");
        scanf("%d", &menu);
    } while (menu > 2);
    if (menu == 1)
        g = leer_grafo(fp, 0);
    if (menu == 2)
        g = leer_grafo(fp, 1);
    printf("Grafo leido correctamente\n");
    MostrarGrafo(g);

    do
    {
        printf("Seleccione modo: \n1.Estadisticas\n2.Arbol de cobertura minimo\n");
        scanf("%d", &menu);
    } while (menu > 2);
    if (menu == 1)
    {
        printf("Numero de aristas que superan el peso promedio de las aristas del grafo: %d\n", aristas_sobre_prom(g));
        printf("Grado promedio: %.f\n", grado_promedio(g));
        printf("Densidad: %f\n", densidad_grafo(g));
    }
    if (menu == 2)
    {
        MostrarGrafo(PRIM(g));
    }
    fclose(fp);
}