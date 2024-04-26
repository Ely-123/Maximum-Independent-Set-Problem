// C++ program for above approach
#include <iostream>
#include <map>
#include <vector>
#include "conjunto.h"
#include "grafo.h"
using namespace std;

/**
 * @brief Encuentra un Conjunto Independiente Maximal (MIS) en un grafo no dirigido.
 *
 * @param grafo El grafo en el que se buscará el MIS.
 * @return Conjunto<int> El Conjunto Independiente Maximal encontrado.
 *
 * Esta función utiliza un algoritmo de búsqueda exhaustiva (brute force) con backtracking para encontrar un MIS en un grafo.
 *
 * El Conjunto Independiente Maximal (MIS) es un conjunto de vértices en un grafo en el que ningún par de vértices adyacentes está en el conjunto.
 *
 * @note La función asume que el grafo es representado por un objeto de tipo Grafo que tiene un método getSize() que devuelve el número de nodos en el grafo,
 *       y un método getAristas() que devuelve un puntero a un mapa que contiene los vértices y sus vecinos.
 *       Además, el tipo Conjunto<int> se utiliza para representar un conjunto de enteros y se asume que tiene métodos como add(), getCard() y print().
 */
Conjunto<int> MIS(Grafo grafo)
{
    // Caso base: el grafo dado no tiene nodos
    if (grafo.getSize() == 0)
    {
        return Conjunto<int>();
    }

    // Caso base: el grafo tiene un nodo
    if (grafo.getSize() == 1)
    {
        Conjunto<int> v;
        for (auto const &element : *(grafo.getAristas()))
        {
            v.add(element.first);
        }
        return v;
    }

    // Se selecciona el primer vertice
    int vCurrent = grafo.getAristas()->begin()->first;

    /**
     * Caso 1 - Se eliminar el vértice seleccionado
    del Conjunto Máximo
    */
    Grafo grafo2(*grafo.getAristas());

    // se elimina el vértice actual del gráfico
    grafo2.getAristas()->erase(vCurrent);

    /*

    Llamada recursiva: obtiene el conjunto máximo,
    suponiendo que el vértice actual no esté seleccionado/*
    */
    Conjunto<int> res1 = MIS(grafo2);

    /*
    Caso 2 - Proceder considerando el vértice seleccionado
    como parte del conjunto máximo

    Recorre sus vecinos (nodos adyacentes)
    */
    for (auto v : grafo.getAristas()->at(vCurrent))
    {
        // Elimina el vecino del subgrafo actual(m
        if (grafo2.getAristas()->count(v))
        {
            grafo2.getAristas()->erase(v);
        }
    }

    /**
     *  Este conjunto de resultados contiene vCurrent,
     y el resultado de la llamada recursiva asumiendo vecinos
    de vCurrent no están seleccionados
    */

    Conjunto<int> res2;
    res2.add(vCurrent);
    Conjunto<int> res2Sub = MIS(grafo2);
    // res2.getElementos()->insert(res2.getElementos()->end(), res2Sub.getElementos()->begin(), res2Sub.getElementos()->end());
    res2 = res2.Union(res2Sub);

    // See retorna el subconjunto mas grande
    if (res1.getCard() > res2.getCard())
    {
    
        return res1;
    }
    return res2;
}

int main()
{

    // Aristas del grafo
    Conjunto<array<int, 2>> E;

    E.add({1, 2});
    E.add({1, 3});
    E.add({1, 8});


    Grafo g1(E);
    Conjunto<int> CIM = MIS(g1);

    CIM.print();
    g1.dibujar(CIM,0);

    return 0;
}