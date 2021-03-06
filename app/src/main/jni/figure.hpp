#ifndef figure_hpp
#define figure_hpp
#include "model.hpp"

class Hexahedron: public Model {
private:
    void addPoints();
    void addEdges();
    void addFaces();

public:
    Hexahedron();
    ~Hexahedron();
protected:

};

class Icosahedron: public Model {
private:
    void addPoints();
    void addEdges();
    void addFaces();

public:
    Icosahedron();
    ~Icosahedron();
protected:

};

class Sphere: public Model {
private:
    float rad = 1.17557f;

    void addPoints();
    void addEdges();
    void addFaces();
    void splitTriangles(int n);

public:
    Sphere();
    ~Sphere();
protected:

};

#endif //figure_hpp