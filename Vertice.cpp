#include <iostream>
using namespace std;

class Vertice
{
private:
    int key;

public:
    Vertice(/* args */);
    Vertice(int);
    ~Vertice();
    int getKey();
    void setKey(int);
};

Vertice::Vertice(/* args */)
{
}

Vertice::Vertice(int n)
{
    key = n;
}
Vertice::~Vertice()
{
}

int Vertice::getKey() { return key; }
void Vertice::setKey(int n) { key = n; }
