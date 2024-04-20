#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Función para escribir un archivo DOT que representa el grafo
void dibujarGrafo(const string &nombreArchivo, const vector<vector<int>> &grafo)
{
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    archivo << "graph Grafo {" << endl;
    for (int i = 0; i < grafo.size(); ++i)
    {
        archivo << "    " << i << ";" << endl;
        for (int j = i + 1; j < grafo[i].size(); ++j)
        {
            if (grafo[i][j] == 1)
            {
                archivo << "    " << i << " -- " << j << ";" << endl;
            }
        }
    }
    archivo << "}" << endl;

    archivo.close();
}

int main()
{
    // Definir un grafo de ejemplo como una matriz de adyacencia
    vector<vector<int>> grafo = {{0, 1, 1, 0},
                                 {1, 0, 1, 1},
                                 {1, 1, 0, 1},
                                 {0, 1, 1, 0}};

    // Escribir el archivo DOT
    dibujarGrafo("grafo.dot", grafo);

    // Generar el gráfico usando GraphViz
    system("dot -Tpng grafo.dot -o grafo.png");

    cout << "Grafo generado como grafo.png." << endl;

    return 0;
}
