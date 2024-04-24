
#include <iostream>
#include "grafo.h"
using namespace std;

/**
 * @brief Constructor de la clase Grafo que crea un grafo a partir de un conjunto de aristas.
 *
 * @param aristas Conjunto de aristas representado como un conjunto de arrays de enteros de tamaño 2, donde cada array representa una arista entre dos vértices.
 *
 * Este constructor toma un conjunto de aristas y construye un grafo no dirigido a partir de ellas.
 *
 * @note Se asume que la clase Grafo tiene un miembro de datos E de tipo puntero a un mapa de enteros a vectores de enteros.
 *       Este mapa representa la estructura del grafo donde las claves son los vértices y los valores son vectores que contienen los vecinos de cada vértice.
 *       Además, se asume que la clase Conjunto<T> tiene métodos como getCard() para obtener el número de elementos, at() para acceder a un elemento por índice y count() para verificar la existencia de un elemento.
 */
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
/**
 * @brief Constructor de la clase Grafo que crea un grafo a partir de un mapa de vértices y sus vecinos.
 *
 * @param grafo Mapa que representa el grafo, donde las claves son los vértices y los valores son vectores que contienen los vecinos de cada vértice.
 *
 * Este constructor toma un mapa que representa la estructura del grafo, donde las claves son los vértices y los valores son vectores que contienen los vecinos de cada vértice, y construye un grafo no dirigido a partir de esta estructura.
 *
 * @note Se asume que la clase Grafo tiene un miembro de datos E de tipo puntero a un mapa de enteros a vectores de enteros.
 *       Este mapa representa la estructura del grafo donde las claves son los vértices y los valores son vectores que contienen los vecinos de cada vértice.
 */
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

/**
 * @brief Método de la clase Grafo que genera un archivo de imagen representando el grafo utilizando Graphviz.
 * 
 * Este método genera un archivo de imagen que representa visualmente el grafo utilizando el software Graphviz. El grafo se representa como un gráfico no dirigido donde los vértices están conectados por aristas.
 * 
 * @note Se asume que la clase Grafo tiene un miembro de datos E de tipo puntero a un mapa de enteros a vectores de enteros, que representa la estructura del grafo donde las claves son los vértices y los valores son vectores que contienen los vecinos de cada vértice.
 *       Además, se asume que la función getSize() devuelve el número de vértices en el grafo.
 */
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
