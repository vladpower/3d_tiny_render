#include "figure.hpp"

Hexahedron::Hexahedron()
{
    addPoints();
    addEdges();
    addFaces();
}

void Hexahedron::addPoints()
{
    verts.push_back(sf::Vector3f(-1.0f, -0.5f, -0.5f));
    verts.push_back(sf::Vector3f(-1.0f, 0.5f, -0.5f));
    verts.push_back(sf::Vector3f(-1.0f, 0.5f, 0.5f));
    verts.push_back(sf::Vector3f(-1.0f, -0.5f, 0.5f));
    verts.push_back(sf::Vector3f(1.0f, -0.5f, -0.5f));
    verts.push_back(sf::Vector3f(1.0f, 0.5f, -0.5f));
    verts.push_back(sf::Vector3f(1.0f, 0.5f, 0.5f));
    verts.push_back(sf::Vector3f(1.0f, -0.5f, 0.5f));
}

void Hexahedron::addEdges()
{
    edges.push_back(sf::Vector2i(0, 1));
    edges.push_back(sf::Vector2i(1, 2));
    edges.push_back(sf::Vector2i(2, 3));
    edges.push_back(sf::Vector2i(0, 3));
    edges.push_back(sf::Vector2i(4, 5));
    edges.push_back(sf::Vector2i(5, 6));
    edges.push_back(sf::Vector2i(6, 7));
    edges.push_back(sf::Vector2i(4, 7));
    edges.push_back(sf::Vector2i(0, 4));
    edges.push_back(sf::Vector2i(1, 5));
    edges.push_back(sf::Vector2i(2, 6));
    edges.push_back(sf::Vector2i(3, 7));
}

void Hexahedron::addFaces()
{
    faces.push_back(sf::Vector3i(2, 1, 0));
    faces.push_back(sf::Vector3i(3, 2, 0));
    faces.push_back(sf::Vector3i(4, 5, 6));
    faces.push_back(sf::Vector3i(4, 6, 7));
    faces.push_back(sf::Vector3i(0, 1, 4));
    faces.push_back(sf::Vector3i(5, 4, 1));
    faces.push_back(sf::Vector3i(1, 2, 5));
    faces.push_back(sf::Vector3i(6, 5, 2));
    faces.push_back(sf::Vector3i(2, 3, 6));
    faces.push_back(sf::Vector3i(7, 6, 3));
    faces.push_back(sf::Vector3i(4, 3, 0));
    faces.push_back(sf::Vector3i(3, 4, 7));
}

Hexahedron::~Hexahedron()
{

}


Icosahedron::Icosahedron()
{
    addPoints();
    addEdges();
    addFaces();
}

void Icosahedron::addPoints()
{
    verts.push_back(sf::Vector3f(0, 0, 1.17557));
    verts.push_back(sf::Vector3f(1.05146, 0, 0.525731));
    verts.push_back(sf::Vector3f(0.32492, 1., 0.525731));
    verts.push_back(sf::Vector3f(-0.850651, 0.618034, 0.525731));
    verts.push_back(sf::Vector3f(-0.850651, -0.618034, 0.525731));
    verts.push_back(sf::Vector3f(0.32492, -1., 0.525731));
    verts.push_back(sf::Vector3f(0.850651, 0.618034, -0.525731));
    verts.push_back(sf::Vector3f(0.850651, -0.618034, -0.525731));
    verts.push_back(sf::Vector3f(-0.32492, 1., -0.525731));
    verts.push_back(sf::Vector3f(-1.05146, 0, -0.525731));
    verts.push_back(sf::Vector3f(-0.32492, -1., -0.525731));
    verts.push_back(sf::Vector3f(0, 0, -1.17557));
}

void Icosahedron::addEdges()
{
    edges.push_back(sf::Vector2i(0,1));
    edges.push_back(sf::Vector2i(0,2));
    edges.push_back(sf::Vector2i(0,3));
    edges.push_back(sf::Vector2i(0,4));
    edges.push_back(sf::Vector2i(0,5));
    edges.push_back(sf::Vector2i(1,2));
    edges.push_back(sf::Vector2i(1,5));
    edges.push_back(sf::Vector2i(1,6));
    edges.push_back(sf::Vector2i(1,7));
    edges.push_back(sf::Vector2i(2,3));
    edges.push_back(sf::Vector2i(2,6));
    edges.push_back(sf::Vector2i(2,8));
    edges.push_back(sf::Vector2i(3,4));
    edges.push_back(sf::Vector2i(3,8));
    edges.push_back(sf::Vector2i(3,9));
    edges.push_back(sf::Vector2i(4,5));
    edges.push_back(sf::Vector2i(4,9));
    edges.push_back(sf::Vector2i(4,10));
    edges.push_back(sf::Vector2i(5,7));
    edges.push_back(sf::Vector2i(5,10));
    edges.push_back(sf::Vector2i(6,7));
    edges.push_back(sf::Vector2i(6,8));
    edges.push_back(sf::Vector2i(6,11));
    edges.push_back(sf::Vector2i(7,10));
    edges.push_back(sf::Vector2i(7,11));
    edges.push_back(sf::Vector2i(8,9));
    edges.push_back(sf::Vector2i(8,11));
    edges.push_back(sf::Vector2i(9,10));
    edges.push_back(sf::Vector2i(9,11));
    edges.push_back(sf::Vector2i(10,11));
}

void Icosahedron::addFaces()
{
    faces.push_back(sf::Vector3i(0,1,2));
    faces.push_back(sf::Vector3i(0,2,3));
    faces.push_back(sf::Vector3i(0,3,4));
    faces.push_back(sf::Vector3i(0,4,5));
    faces.push_back(sf::Vector3i(0,5,1));
    faces.push_back(sf::Vector3i(1,5,7));
    faces.push_back(sf::Vector3i(1,7,6));
    faces.push_back(sf::Vector3i(1,6,2));
    faces.push_back(sf::Vector3i(2,6,8));
    faces.push_back(sf::Vector3i(2,8,3));
    faces.push_back(sf::Vector3i(3,8,9));
    faces.push_back(sf::Vector3i(3,9,4));
    faces.push_back(sf::Vector3i(4,9,10));
    faces.push_back(sf::Vector3i(4,10,5));
    faces.push_back(sf::Vector3i(5,10,7));
    faces.push_back(sf::Vector3i(6,7,11));
    faces.push_back(sf::Vector3i(6,11,8));
    faces.push_back(sf::Vector3i(7,10,11));
    faces.push_back(sf::Vector3i(8,11,9));
    faces.push_back(sf::Vector3i(9,11,10));
}

Icosahedron::~Icosahedron()
{

}