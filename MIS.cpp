// C++ program for above approach
#include <iostream>
#include <map>
#include <vector>
#include "conjunto.h"

using namespace std;

/**
 * Crea un grafo a partir de un conjunto de aristas.
 *
 * Toma un conjunto de arreglos de enteros de tamaño 2 representando aristas
 * y construye un grafo no dirigido a partir de estas aristas. Cada vértice del grafo se
 * representa como una clave en el mapa, y los valores asociados son vectores que contienen
 * los vértices adyacentes a cada vértice.
 *
 * @param E Conjunto de aristas representadas como arreglos de enteros de tamaño 2.
 * @return Mapa donde las claves son los vértices del grafo y los valores son vectores
 *         que contienen los vértices adyacentes a cada vértice.
 */
map<int, vector<int>> Grafo(Conjunto<array<int, 2>> E)
{
    map<int, vector<int>> grafo;
    for (int i = 0; i < E.getCard(); i++)
    {
        int v1 = E.at(i)[0];
        int v2 = E.at(i)[1];
        if (grafo.count(v1) == 0)
        {
            grafo[v1] = vector<int>();
        }
        if (grafo.count(v2) == 0)
        {
            grafo[v2] = vector<int>();
        }
        grafo[v1].push_back(v2);
        grafo[v2].push_back(v1);
    }

    return grafo;
};
Conjunto<int> MIS(map<int, vector<int>> graph)
{
    // Caso base: el grafo dado no tiene nodos
    if (graph.size() == 0)
    {
        return Conjunto<int>();
    }

    // Caso base: el grafo tiene un nodo
    if (graph.size() == 1)
    {
        Conjunto<int> v;
        for (auto const &element : graph)
        {
            v.add(element.first);
        }
        return v;
    }

    // Se selecciona el primer vertice
    int vCurrent = graph.begin()->first;

    /**
     * Caso 1 - Se eliminar el vértice seleccionado
    del Conjunto Máximo
    */
    map<int, vector<int>> graph2(graph);

    // se elimina el vértice actual del gráfico
    graph2.erase(vCurrent);

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
    for (auto v : graph.at(vCurrent))
    {
        // Elimina el vecino del subgrafo actual(m
        if (graph2.count(v))
        {
            graph2.erase(v);
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
    int V = 12;

    // Aristas del grafo
    Conjunto<array<int, 2>> E;

    E.add({1, 2});
    E.add({2, 3});
    E.add({3, 4});
    E.add({4, 1});

     map<int, vector<int>> g1 = Grafo(E);

    Conjunto<int> CIM = MIS(g1);

   CIM.print();

    return 0;
}