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

Conjunto<int> MISR(Grafo grafo, vector<Conjunto<int>> *c)
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
    Conjunto<int> res1 = MISR(grafo2, c);

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
    Conjunto<int> res2Sub = MISR(grafo2, c);
    // res2.getElementos()->insert(res2.getElementos()->end(), res2Sub.getElementos()->begin(), res2Sub.getElementos()->end());
    res2 = res2.Union(res2Sub);

    // See retorna el subconjunto mas grande
    if (res1.getCard() > res2.getCard())
    {

        return res1;
        c->push_back(res1);
    }
    c->push_back(res2);
    return res2;
}

vector<Conjunto<int>> MIS(Grafo grafo)
{

    vector<Conjunto<int>> *c = new vector<Conjunto<int>>;

    MISR(grafo, c);
    int *t = new int[c->size()];
    for (int i = 0; i < c->size(); i++)
        t[i] = c->at(i).getCard();
    int maximo = t[0]; // Suponemos que el primer elemento es el máximo inicialmente

    for (int i = 1; i < c->size(); ++i)
    {
        if (t[i] > maximo)
        {
            maximo = t[i];
        }
    }

    for (int i = c->size() - 1; i >= 0; i--)
    {
        if (c->at(i).getCard() < maximo)
        {
            c->erase(c->begin() + i);
        }
    }

    return *c;
}
int main()
{

    // Aristas del grafo
    Conjunto<array<int, 2>> E;

   E.add({1, 2});
   E.add({2, 3});
E.add({3, 4});
E.add({4, 5});
E.add({5, 6});
E.add({6, 7});
E.add({7, 8});
E.add({8, 9});
E.add({9, 10});
E.add({10, 11});
E.add({11, 12});
E.add({13, 14});
E.add({15, 16});
E.add({17, 18});
E.add({19, 20});
E.add({21, 22});
E.add({23, 24});
E.add({25, 26});
E.add({27, 28});

  
   

    Grafo g1(E);
    vector<Conjunto<int>> CIM = MIS(g1);

    for (int i = 0; i < CIM.size(); i++)
    {
        CIM.at(i).print();
        g1.dibujar(CIM.at(i),i);
    }

    return 0;
}