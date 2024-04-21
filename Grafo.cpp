#include <iostream>
#include "vertice.h"
#include "conjunto.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Grafo
{
private:
    int **matA;
    Conjunto<int> elementos;

public:
    Grafo(Conjunto<int>, int **);
    ~Grafo();
    void Dibujar();
    vector<Conjunto<int>> Ciclos();
    Conjunto<int> rProfundidad(int, int, bool *, Conjunto<int>);
};

Grafo::Grafo(Conjunto<int> e, int **m)

{
    elementos = e;
    matA = new int *[e.getCard()];

    for (int i = 0; i < e.getCard(); i++)
    {
        matA[i] = new int[e.getCard()];
        for (int j = 0; j < e.getCard(); j++)
            matA[i][j] = m[i][j];
    }
}

Grafo::~Grafo()
{
}

void Grafo::Dibujar()

{
    string nombreArchivo = "grafo.dot";
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    archivo << "graph Grafo {" << endl;
    for (int i = 0; i < elementos.getCard(); ++i)
    {
        // archivo << "    " << i << ";" << endl;
        for (int j = i + 1; j < elementos.getCard(); ++j)
        {
            if (matA[i][j] == 1)
            {
                archivo << "    " << elementos.getElementos()->at(i) << " -- " << elementos.getElementos()->at(j) << ";" << endl;
            }
        }
    }
    archivo << "}" << endl;

    archivo.close();

    system("dot -Tpng grafo.dot -o grafo.png");
    system("rm grafo.dot");
    cout << "grafo creado con exito" << endl;
}

/**
 * Busca ciclos en un grafo
 */
vector<Conjunto<int>> Grafo::Ciclos()
{

    vector<Conjunto<int>> ciclos;
    bool *visited = new bool[elementos.getCard()];

    for (int i = 0; i < elementos.getCard(); i++)
    {

        visited[i] = false;
    }

    for (int i = 0; i < elementos.getCard(); i++)
    {

        if (!visited[i])
        {
            Conjunto<int> ciclo;
            visited[i] = true;
            rProfundidad(-1, i, visited, ciclo);
            ciclos.push_back(ciclo);
        }
    }

    for (int i = 0; i < ciclos.size(); i++)
    {
        ciclos.at(i).print();
    }
    return ciclos;
}

Conjunto<int> Grafo::rProfundidad(int padre, int hijo, bool *visited, Conjunto<int> c)
{

    c.add(elementos.at(hijo));
    if (padre < elementos.getCard())
    {

        for (int i = 0; i < elementos.getCard(); i++)
        {
            // buscamos en sus hijos
            if (matA[i][hijo])
            {
                // verificamos si esta visitado
                if (visited[i])
                {
                    // si el elemento visitado es distinto del padre
                    if (i != padre && padre != -1)
                    {

                        c.add(elementos.at(i));
                        c.remove(i - 1);
                        return c;
                    }
                }
                else
                {
                    visited[i] = true;
                    rProfundidad(hijo, i, visited, c);
                    if (c.getCard() != 0)
                        return c;
                }
            }
        }
    }

    return *(new Conjunto<int>);
};
int main()
{
    Conjunto<int> c1;
    c1.add(1);
    c1.add(2);
    c1.add(3);
    c1.add(4);
    c1.add(5);
    c1.add(6);
    c1.add(7);
    int m[c1.getCard()][c1.getCard()] = {
        {0, 1, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 0}};

    // Definir un puntero a puntero de enteros
    int **matriz_convertida = new int *[c1.getCard()];

    // Iterar sobre cada fila de la matriz
    for (int i = 0; i < c1.getCard(); ++i)
    {
        // Asignar la dirección de cada fila a la matriz convertida
        matriz_convertida[i] = m[i];
    }
    Grafo g(c1, matriz_convertida);

    g.Ciclos();
    // g.Dibujar();
    return 0;
}
