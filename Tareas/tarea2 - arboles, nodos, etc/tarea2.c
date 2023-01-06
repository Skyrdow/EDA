#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista.h"

FILE *AbrirArchivo(char *nom)
{
	FILE *fp = fopen(nom, "r");
	if( fp == NULL)
	{
		printf("Problema al abrir el archivo\n");
		return NULL;
	}
	else
	{
		printf("Archivo leido correctamente\n");
		return fp;
	}
}

void ProfRecursivo(grafo *g, int vert, int **datos)
{
    pila *ady = ObtenerAdyacentes(g, vert);
    while (PilaVacia(ady) != 1)
    {
        int vertW = Desapilar(ady);
        // revisar si el vertice no esta visitado
        if (datos[0][vertW] == -1)
        {
            // asignar nivel anterior +1
            datos[0][vertW] = datos[0][vert] + 1;
            // asignar misma componente conexa que la raiz
            datos[1][vertW] = datos[1][vert];
            ProfRecursivo(g, vertW, datos);
        }
    }
}

// recorrido en profundidad
// retorna un array con los datos obtenidos
int **ObtenerDatosArboles(grafo *g, pila *raices, int r)
{
    // datos[0] = niveles | datos[1] = componente conexa a la que pertenece
    int **datos = malloc(sizeof(int *) * 2);
    datos[0] = malloc(sizeof(int) * g->n);
    // iniciar los datos de nivel a -1 para vertice no visitado
    for (int i = 1; i < g->n; i++)
    {
        datos[0][i] = -1;
    }
    
    datos[1] = malloc(sizeof(int) * g->n);
    for (int i = 1; i < g->n; i++)
    {
        datos[1][i] = 0;
    }
    int con = 0;

    while (PilaVacia(raices) != 1)
    {
        int raiz = Desapilar(raices);
        datos[0][raiz] = 0;
        datos[1][raiz] = con;
        ProfRecursivo(g, raiz, datos);
        con++;
    }
    return datos;
}

int CaminoRecursivo(grafo *g, int vert, int fin, int *niveles, lista *camino)
{
    // caso base, vertice que se esta revisando == vertice fin
    if (vert == fin)
    {
        AgregarFin(camino, vert);
        return vert;
    }
    pila *ady = ObtenerAdyacentes(g, vert);
    // para cada adyacente
    while (PilaVacia(ady) != 1)
    {
        int vertW = Desapilar(ady);
        // revisar si el vertice no esta visitado
        if (niveles[vertW] == -1)
        {
            // asignar nivel anterior +1
            niveles[vertW] = niveles[vert] + 1;
            // si se llega al vertice fin se agregará cada 
            // vertice del camino a la pila camino
            int cam = CaminoRecursivo(g, vertW, fin, niveles, camino);
            if (cam != 0)
            {
                AgregarFin(camino, vert);
                return vert;
            }
        }
    }
    return 0;
}

lista *ObtenerCamino(grafo *g, int ini, int fin)
{
    lista *camino = CrearLista();

    int *niveles = malloc(sizeof(int) * g->n);
    // iniciar los datos de nivel a -1 para vertice no visitado
    for (int i = 1; i < g->n; i++)
    {
        niveles[i] = -1;
    }
    niveles[ini] = 0;

    CaminoRecursivo(g, ini,fin, niveles, camino);
    // retornar la lista con el conjunto de vertices
    return camino;
    
}

int main(int argc, char **argv)
{
    // se abre el archivo
    FILE *fp = AbrirArchivo(argv[2]);
    if (fp == NULL)
        return 1;
    // archivo de salida
    FILE *fsalida = fopen("output.txt", "w");

    // se lee la primera linea de CRSQ
    int c, r, s, q;
    fscanf(fp, "%d %d %d %d", &c, &r, &s, &q);
    // se itera hasta encontrar la 0 0 0 0
    while (c != 0 && r != 0 && s != 0 && q != 0)
    {
        fprintf(fsalida, "\n");
        if (argv[1] == "V")
            printf("Entrada:\n%d %d %d %d\n");

        // nueva linea, parte de los requerimientos del archivo de salida

        // asignacion de memoria para arreglos
        int *raices = malloc(sizeof(int) * r);
        pila *raicesP = CrearPila();
        // preguntas[0]: vert1 // preguntas[1]: vert2
        // preguntas[2]: respuesta a imprimir
        int **preguntas = malloc(sizeof(int *) * q);
        for (int i = 0; i < q; i++)
            preguntas[i] = malloc(sizeof(int) * 3);

        // lectura de raices
        for (int i = 0; i < r; i++)
        {
            fscanf(fp, "%d", &raices[i]);
            Apilar(raicesP, raices[i]);
            if (argv[1] == "V" && i != r-1)
                printf("%d ", raices[i]);
            if (argv[1] == "V" && i == r-1)
                printf("%d", raices[i]);
        }
        if (argv[1] == "V")
            printf("\n");

        grafo *g = CrearGrafo(c);
        int vert1, vert2;
        // lectura de aristas
        for (int i = 0; i < s; i++)
        {
            fscanf(fp, "%d %d", &vert1, &vert2);
            InsertarArista(g, vert1, vert2);
            if (argv[1] == "V")
                printf("%d %d\n", vert1, vert2);
            
        }

        // lectura de preguntas
        for (int i = 0; i < q; i++)
        {
            fscanf(fp, "%d %d", &preguntas[i][0], &preguntas[i][1]);
            if (argv[1] == "V")
                printf("%d %d\n", preguntas[i][0], preguntas[i][1]);
        }

        if (argv[1] == "S" || argv[1] == "V")
            printf("Salida:\n");
        // obtener niveles y componente conexa de cada vertice
        int **datosArboles = ObtenerDatosArboles(g, raicesP, r);

        // Responder cada pregunta
        for (int i = 0; i < q; i++)
        {
            // Revisar si los vertices de la pregunta estan en la misma
            // componente conexa/rio
            if(datosArboles[1][preguntas[i][0]] != datosArboles[1][preguntas[i][1]])
            {
                // las ciudades estan en rios distintos, no se puede llegar
                preguntas[i][2] = -1;
            }
            else
            {
                // obtener el camino y transformarlo de lista a array
                lista *camino = ObtenerCamino(g, preguntas[i][0], preguntas[i][1]);
                int largo = LargoLista(camino);
                int *caminoA = malloc(sizeof(int) * largo);
                for (int j = 0; j < largo; j++)
                {
                    caminoA[j] = EliminarIni(camino);
                }
                // calcular los cambios de flujo
                int flujo = datosArboles[0][caminoA[0]] - datosArboles[0][caminoA[1]];
                int cambio = 0;
                for (int j = 0; j < (largo - 1); j++)
                {
                    // la diferencia de niveles es siempre -1 o 1, si cambia es porque cambio el flujo
                    if (datosArboles[0][caminoA[j]] - datosArboles[0][caminoA[j+1]] != flujo)
                    {
                        cambio = caminoA[j];
                        flujo = datosArboles[0][caminoA[j]] - datosArboles[0][caminoA[j+1]];
                    }
                }
                preguntas[i][2] = cambio;
            }            
            if (argv[1] == "S" || argv[1] == "V")
                printf("%d\n", preguntas[i][2]);
            // escribir respuesta al archivo
            fprintf(fsalida, "%d\n", preguntas[i][2]);
            
        }
        if (argv[1] == "S" || argv[1] == "V")
            printf("\n");
        // Lectura iterativa de CRSQ
        fscanf(fp, "%d %d %d %d", &c, &r, &s, &q);
    }
    fclose(fsalida);
    fclose(fp);
}