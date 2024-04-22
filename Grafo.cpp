
#include <iostream>
#include "grafo.h"
using namespace std;

Grafo::Grafo(Conjunto<array<int, 2>> aristas)

{
    for (int i = 0; i < aristas.getCard(); i++)
    {
        int v1 = aristas.at(i)[0];
        int v2 = aristas.at(i)[1];
        if (E.count(v1) == 0)
        {
            E[v1] = vector<int>();
        }
        if (E.count(v2) == 0)
        {
            E[v2] = vector<int>();
        }
        E[v1].push_back(v2);
        E[v2].push_back(v1);
    }
}

Grafo::Grafo(map<int, vector<int>> grafo)
{
    for (const auto &par : grafo)
    {
        E[par.first] = par.second;
    
    }
}

Grafo::~Grafo()
{
}

map<int, vector<int>> Grafo::getAristas()
{
    return E;
};

int Grafo::getSize()
{
    return E.size();
}

