#ifndef VERTICE_H
#define VERTICE_H

class Vertice
{
private:
    int key;

public:
    Vertice();
    Vertice(int);
    ~Vertice();
    int getKey();
    void setKey(int);
};

#endif
