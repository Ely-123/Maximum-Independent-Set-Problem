#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <vector>
using namespace std;

template <typename T>
class Conjunto
{
private:
    vector<T> *elementos;

public:
    Conjunto(/* args */);
    Conjunto(vector<T> *);
    ~Conjunto();
    int getCard();
    vector<T> *getElementos();
    bool search(T);
    void add(T);
    void remove(int );
    void print();
    T at(int);
    Conjunto<T> Union(Conjunto);
    Conjunto<T> Intersection(Conjunto);
};

#include "Conjunto.cpp"
#endif