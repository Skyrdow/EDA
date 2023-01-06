#include <stdio.h>
#include "ABB.h"

int main()
{
    arbol *a = CrearArbol();
    a->raiz = CrearNodoA('a');
    Insertar(a, 'a', 'b');
    Insertar(a, 'b', 'e');
    Insertar(a, 'b', 'f');
    Insertar(a, 'a', 'c');
    Insertar(a, 'c', 'd');
    Insertar(a, 'c', 'x');

    arbol *b = CrearArbol();
    b->raiz = CrearNodoA('a');
    Insertar(b, 'a', 'b');
    Insertar(b, 'b', 'e');
    Insertar(b, 'b', 'f');
    Insertar(b, 'a', 'c');
    Insertar(b, 'c', 'd');

    printf("Preorden: ");
    Preorden(a->raiz);
    printf("\n");
    printf("Inorden: ");
    Inorden(a->raiz);
    printf("\n");
    printf("Postorden: ");
    Postorden(a->raiz);
    printf("\n");

    printf("BuscarPadre(x): %c \n", BuscarPadre(a->raiz, 'x')->dato);
    printf("ProfundidadNodo(d): %d \n", ProfundidadNodo(a, 'd'));
    printf("NivelNodo(d): %d \n", NivelNodo(a, 'd'));
    printf("AlturaNodo(d): %d \n", AlturaNodo(a, 'd'));
    printf("AlturaNodo(b): %d \n", AlturaNodo(a, 'b'));
    printf("ContarNodos: %d \n", ContarNodos(a));
    printf("ContarHojas: %d \n", ContarHojas(a));
    printf("SonSimilares: %d \n", SonSimilares(a, b));
    printf("EsCompleto: %d \n", EsCompleto(a));
    printf("EsCompleto: %d \n", EsCompleto(b));
}
