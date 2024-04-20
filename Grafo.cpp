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
    cout<<"grafo creado con exito"<<endl;
}

int main()
{
    Conjunto<int> c1;
    c1.add(1);
    c1.add(2);
    c1.add(3);
    int m[3][3] = {{0, 1, 1}, {1, 0, 0}, {1, 0, 0}};

    // Definir un puntero a puntero de enteros
    int **matriz_convertida = new int *[3];

    // Iterar sobre cada fila de la matriz
    for (int i = 0; i < 3; ++i)
    {
        // Asignar la dirección de cada fila a la matriz convertida
        matriz_convertida[i] = m[i];
    }
    Grafo g(c1, matriz_convertida);

    g.Dibujar();
    return 0;
}
