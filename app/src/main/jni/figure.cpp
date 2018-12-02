#include "figure.hpp"

Hexahedron::Hexahedron()
{
    addPoints();
    // addPolygon(2, 1, 0, 3);
    // addPolygon(4, 5, 6, 7);
    // addPolygon(3, 0, 4, 7);
    // addPolygon(0, 1, 4, 5);
    // addPolygon(1, 2, 5, 6);
    // addPolygon(2, 3, 6, 7);
    addEdges();
    addFaces();
}

void Hexahedron::addPoints()
{
    verts.push_back(sf::Vector3f(-0.5f, -0.5f, -0.5f));
    verts.push_back(sf::Vector3f(-0.5f, 0.5f, -0.5f));
    verts.push_back(sf::Vector3f(-0.5f, 0.5f, 0.5f));
    verts.push_back(sf::Vector3f(-0.5f, -0.5f, 0.5f));
    verts.push_back(sf::Vector3f(0.5f, -0.5f, -0.5f));
    verts.push_back(sf::Vector3f(0.5f, 0.5f, -0.5f));
    verts.push_back(sf::Vector3f(0.5f, 0.5f, 0.5f));
    verts.push_back(sf::Vector3f(0.5f, -0.5f, 0.5f));
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
    faces.push_back(sf::Vector3i(0, 3, 2));
    faces.push_back(sf::Vector3i(4, 5, 6));
    faces.push_back(sf::Vector3i(6, 7, 4));
    faces.push_back(sf::Vector3i(4, 0, 1));
    faces.push_back(sf::Vector3i(1, 5, 4));
    faces.push_back(sf::Vector3i(5, 1, 2));
    faces.push_back(sf::Vector3i(2, 6, 5));
    faces.push_back(sf::Vector3i(6, 2, 3));
    faces.push_back(sf::Vector3i(3, 7, 6));
    faces.push_back(sf::Vector3i(3, 0, 4));
    faces.push_back(sf::Vector3i(4, 7, 3));
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

Sphere::Sphere()
{
    addPoints();
    addEdges();
    addFaces();
    splitTriangles(1);
}

void Sphere::addPoints()
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

void Sphere::addEdges()
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

void Sphere::addFaces()
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

void Sphere::splitTriangles(int n)
{
    std::vector<sf::Vector3i> newFaces;
    std::vector<sf::Vector2i> newEdges;
    std::vector<sf::Vector3i>::iterator it;
    for(it = faces.begin();it!=faces.end();it++) {
        sf::Vector3f midDot[3] = {(verts[it->x] + verts[it->y]) / 2,
        (verts[it->y] + verts[it->z]) / 2, (verts[it->z] + verts[it->x]) / 2};
        int indMid[3];
        for(int i=0;i<3;i++) {
            float prod = rad / Length2(midDot[i]);
            verts.push_back(midDot[i] * prod);
            indMid[i] = verts.size()-1;
        }
        newEdges.push_back(sf::Vector2i(it->x, indMid[0]));
        newEdges.push_back(sf::Vector2i(indMid[0], it->y));
        newEdges.push_back(sf::Vector2i(it->y, indMid[1]));
        newEdges.push_back(sf::Vector2i(indMid[1], it->z));
        newEdges.push_back(sf::Vector2i(it->z, indMid[2]));
        newEdges.push_back(sf::Vector2i(indMid[2], it->x));
        newFaces.push_back(sf::Vector3i(it->x, indMid[0], indMid[2]));
        newFaces.push_back(sf::Vector3i(it->y, indMid[1], indMid[0]));
        newFaces.push_back(sf::Vector3i(it->z, indMid[2], indMid[1]));
        newFaces.push_back(sf::Vector3i(indMid[0], indMid[1], indMid[2]));
    }
    faces = newFaces;
    edges = newEdges;
    if(n>1) {
        splitTriangles(n-1);
    }
}

Sphere::~Sphere()
{

}