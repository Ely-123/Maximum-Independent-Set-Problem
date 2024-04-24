// C++ program for above approach
#include <iostream>
#include <map>
#include <vector>
#include "conjunto.h"
#include "grafo.h"
using namespace std;

Conjunto<int> MIS(Grafo graph)
{
    // Caso base: el grafo dado no tiene nodos
    if (graph.getSize() == 0)
    {
        return Conjunto<int>();
    }

    // Caso base: el grafo tiene un nodo
    if (graph.getSize() == 1)
    {
        Conjunto<int> v;
        for (auto const &element : *(graph.getAristas()))
        {
            v.add(element.first);
        }
        return v;
    }

    // Se selecciona el primer vertice
    int vCurrent = graph.getAristas()->begin()->first;

    /**
     * Caso 1 - Se eliminar el vértice seleccionado
    del Conjunto Máximo
    */
    Grafo graph2(*graph.getAristas());

    // se elimina el vértice actual del gráfico
    graph2.getAristas()->erase(vCurrent);

    /*

    Llamada recursiva: obtiene el conjunto máximo,
     suponiendo que el vértice actual no esté seleccionado/*
    */
    Conjunto<int> res1 = MIS(graph2);

    /*
     Caso 2 - Proceder considerando el vértice seleccionado
    como parte del conjunto máximo

    Recorre sus vecinos (nodos adyacentes)
    */
    for (auto v : graph.getAristas()->at(vCurrent))
    {
        // Elimina el vecino del subgrafo actual(m
        if (graph2.getAristas()->count(v))
        {
            graph2.getAristas()->erase(v);
        }
    }

    /**
     *  Este conjunto de resultados contiene vCurrent,
     y el resultado de la llamada recursiva asumiendo vecinos
    de vCurrent no están seleccionados
    */

    Conjunto<int> res2;
    res2.add(vCurrent);
    Conjunto<int> res2Sub = MIS(graph2);
    res2.getElementos()->insert(res2.getElementos()->end(), res2Sub.getElementos()->begin(), res2Sub.getElementos()->end());

    // See retorna el subconjunto mas grande
    if (res1.getCard() > res2.getCard())
    {
        res1.print();
        res2.print();
        return res1;
    }
    return res2;
}

int main()
{

    // Aristas del grafo
    Conjunto<array<int, 2>> E;

    E.add({1});



    Grafo g1(E);
    Conjunto<int> CIM = MIS(g1);

    CIM.print();
    g1.dibujar();

    return 0;
}