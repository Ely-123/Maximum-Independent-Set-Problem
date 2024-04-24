
#include <iostream>
#include "grafo.h"
using namespace std;

Grafo::Grafo(Conjunto<array<int, 2>> aristas)

{
    E = new map<int, vector<int>>;
    for (int i = 0; i < aristas.getCard(); i++)
    {
        int v1 = aristas.at(i)[0];
        int v2 = aristas.at(i)[1];
        if (E->count(v1) == 0)
        {
            (*E)[v1] = vector<int>();
        }
        if ((*E).count(v2) == 0)
        {
            (*E)[v2] = vector<int>();
        }
        (*E)[v1].push_back(v2);
        (*E)[v2].push_back(v1);
    }
}

Grafo::Grafo(map<int, vector<int>> grafo)
{
    E = new map<int, vector<int>>;
    for (auto v : grafo)
        (*E)[v.first] = v.second;
}

Grafo::~Grafo()
{
}

map<int, vector<int>> *Grafo::getAristas()
{
    return E;
};

int Grafo::getSize()
{
    return (*E).size();
}

void Grafo::dibujar()
{
    bool *visitados = new bool[getSize()];
    string nombreArchivo = "grafo.dot";
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    archivo << "graph Grafo {" << endl;
    for (auto const &par : *E)
    {
        int v1 = par.first;
        if (!visitados[v1])
        {
            for (auto const &v2 : par.second)
            {
                archivo << "    " << v1 << " -- " << v2 << ";" << endl;
                visitados[v2] = true;
            }
        }
    }
    archivo << "}" << endl;

    archivo.close();

    system("dot -Tpng grafo.dot -o grafo.png");
    system("rm grafo.dot");
    cout << "grafo creado con exito" << endl;
}
