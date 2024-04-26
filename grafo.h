#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <fstream>
#include <string>
#include <map>
#include "conjunto.h"
using namespace std;

class Grafo
{
private:
   

    map<int, vector<int>>* E;

public:
    Grafo(Conjunto<array<int, 2>> );
    Grafo(map<int, vector<int>> );
    ~Grafo();
  
    map<int, vector<int>>* getAristas();
    int getSize();
    void dibujar(Conjunto<int>,int );
};
#include "Grafo.cpp"
#endif
