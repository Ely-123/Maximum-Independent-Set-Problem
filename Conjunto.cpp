#include <iostream>
#include <vector>
#include "conjunto.h"
using namespace std;

template <typename T>
Conjunto<T>::Conjunto()
{
    elementos = new vector<T>;
}
template <typename T>
Conjunto<T>::Conjunto(vector<T> *e)
{
    elementos = e;
}
template <typename T>
Conjunto<T>::~Conjunto()
{
}

template <typename T>
int Conjunto<T>::getCard() { return elementos->size(); }

template <typename T>

vector<T> *Conjunto<T>::getElementos()
{
    return elementos;
}
template <typename T>
/**
 * Busca un elemento n en un conjunto
 */
bool Conjunto<T>::search(T n)
{

    for (int i = 0; i < elementos->size(); i++)
        if (n == elementos->at(i))
            return true;
    return false;
}

/**
 * Agrega un elemento n al conjunto
 */
template <typename T>
void Conjunto<T>::add(T n)
{
    if (!search(n))
        elementos->push_back(n);
}

template <typename T>
void Conjunto<T>::print()
{
    cout << "{ ";
    for (int i = 0; i < elementos->size(); i++)
        cout << elementos->at(i) << (i + 1 < elementos->size() ? "," : "");
    cout << " }" << endl;
}

template <typename T>

Conjunto<T> Conjunto<T>::Union(Conjunto c)
{
    Conjunto<T> newC(elementos);

    for (int i = 0; i < c.getCard(); i++)
        newC.add(c.getElementos()->at(i));

    return newC;
}

template <typename T>

Conjunto<T> Conjunto<T>::Intersection(Conjunto c)
{
    Conjunto<T> newC;

    for (int i = 0; i < c.getCard(); i++)
        if (search(c.getElementos()->at(i)))
            newC.add(c.getElementos()->at(i));

    return newC;
}

template <typename T>
T Conjunto<T>::at(int i) { return elementos->at(i); }

template <typename T>
void Conjunto<T>::remove(int i)
{
   if (i >= 0 && i < elementos->size()) {
        elementos->erase(elementos->begin() + i);
    }
}

/*
    int main(int argc, char const *argv[])
    {
        Conjunto<int> c1;
        c1.add(1);
        c1.add(2);
        c1.add(3);
        c1.add(4);

        Conjunto<int> c2;
        c2.add(4);
        c2.add(6);
        c2.add(7);
        c2.add(8);

        c1.Intersection(c2).print();
        return 0;
    }
*/