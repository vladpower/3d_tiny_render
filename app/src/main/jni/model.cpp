#include "model.hpp"
#include "lamp.hpp"

std::vector<Model*> Model::models;

Model::Model()
{
    models.push_back(this);
}

int Model::findIndex(sf::Vector3f v) {
    for(int i=0;i<verts.size();i++) {
        if(verts[i] == v)
            return i;
    }
    return -1;
}

void Model::addPolygon(sf::Vector3f a, sf::Vector3f b, sf::Vector3f c, sf::Vector3f d)
{
    addTriangle(a,b,c);
    if(c!=d) {
        addTriangle(c,d,a);
    }
}

void Model::addPolygon(int a, int b, int c, int d)
{
    addTriangle(a,b,c);
    if(c!=d) {
        addTriangle(c,d,a);
    }
}

void Model::addTriangle(int i, int j, int k)
{
    edges.push_back(sf::Vector2i(i,j));
    edges.push_back(sf::Vector2i(j,k));
    edges.push_back(sf::Vector2i(k,i));
    faces.push_back(sf::Vector3i(i,j,k));
}

void Model::addTriangle(sf::Vector3f a, sf::Vector3f b, sf::Vector3f c)
{
    int i,j,k;
    i = findIndex(a);
    j = findIndex(b);
    k = findIndex(c);
    if(i<0) {
        verts.push_back(a);
        i=verts.size()-1;
    }
    if(j<0) {
        verts.push_back(b);
        j=verts.size()-1;
    }
    if(k<0) {
        verts.push_back(c);
        k=verts.size()-1;
    }
    addTriangle(i, j, k);
}

void Model::render(Matrix4& vp, sf::Image& image, ZBuffer& zbuffer)
{
    dots.clear();
    sf::Vector2u size = image.getSize();
    Matrix4 viewport;
    viewport.ViewPort( 0, 0, size.x, size.y);
    //viewport = viewport * vp;
    
    for (std::vector<sf::Vector3f>::iterator it=verts.begin(); it != verts.end(); ++it)
    {
        Vector4f vec4(*it, 1);
        Vector4f dot = vp * vec4;
        float z = dot.z;
        dot = viewport * dot;
        dot = dot / dot.w;
        dot.z = z;
        dots.push_back(dot);
    }

    if(Lamp::illuminationType == NoIllumination) {
        for (std::vector<sf::Vector2i>::iterator it=edges.begin(); it != edges.end(); ++it)
        {
            drawLine(dots[it->x].toVector3(), dots[it->y].toVector3(), image, zbuffer, sf::Color::White);
        }
    } else {
        if(Lamp::illuminationType == GuroIllumination) {
            shadeVerts(image, zbuffer);
        } else if(Lamp::illuminationType == TrueFongIllumination) {
            shadeFongFaces(image, zbuffer);
        } else {
            shadeFaces(image, zbuffer);
        }
        
    }
}
    
void Model::shadeFaces(sf::Image& image, ZBuffer& zbuffer)
{
    for (std::vector<sf::Vector3i>::iterator it=faces.begin(); it != faces.end(); ++it)
    {
        sf::Vector3f worldFace[] = {verts[it->x], verts[it->y], verts[it->z]};
        sf::Vector3f camFace[] = {dots[it->x].toVector3(), dots[it->y].toVector3(), dots[it->z].toVector3()};
        shadeFace(worldFace, camFace, image, zbuffer);
    }
}

void Model::shadeFongFaces(sf::Image& image, ZBuffer& zbuffer)
{
    std::vector<sf::Vector3f> normalsVerts(verts.size(), sf::Vector3f(0.f,0.f,0.f));
    
    for (std::vector<sf::Vector3i>::iterator it=faces.begin(); it != faces.end(); ++it)
    {
        sf::Vector3f worldFace[] = {verts[it->x], verts[it->y], verts[it->z]};
        sf::Vector3f normal = GetNormal(worldFace);
        normalsVerts[it->x] += normal*0.5f;
        normalsVerts[it->y] += normal;
        normalsVerts[it->z] += normal*0.5f;
    }

    for (std::vector<sf::Vector3i>::iterator it=faces.begin(); it != faces.end(); ++it)
    {
        sf::Vector3f worldFace[] = {verts[it->x], verts[it->y], verts[it->z]};
        sf::Vector3f camFace[] = {dots[it->x].toVector3(), dots[it->y].toVector3(), dots[it->z].toVector3()};
        sf::Vector3f normals[] = {normalsVerts[it->x], normalsVerts[it->y], normalsVerts[it->z]};
        shadeFongFace(worldFace, camFace, normals, image, zbuffer);
    }

}

void Model::shadeVerts(sf::Image& image, ZBuffer& zbuffer)
{
    std::vector<sf::Vector3f> normalsFace;
    std::vector<sf::Vector3f> normalsVerts(verts.size(), sf::Vector3f(0.f,0.f,0.f));
    std::vector<std::vector<Vector4f>> intensVerts;
    
    for (std::vector<sf::Vector3i>::iterator it=faces.begin(); it != faces.end(); ++it)
    {
        sf::Vector3f worldFace[] = {verts[it->x], verts[it->y], verts[it->z]};
        sf::Vector3f normal = GetNormal(worldFace);
        normalsVerts[it->x] += normal;
        normalsVerts[it->y] += normal;
        normalsVerts[it->z] += normal;
        normalsFace.push_back(normal);
    }
    for (int i=0;i<verts.size();i++)
    {
        sf::Vector3f& worldPos = verts[i];
        sf::Vector3f& normal = normalsVerts[i];
        std::vector<Vector4f> intens;
        Lamp::getIntensVector(worldPos, normal, intens);
        intensVerts.push_back(intens);
    }
    for (std::vector<sf::Vector3i>::iterator it=faces.begin(); it != faces.end(); ++it)
    {
        sf::Vector3f worldFace[] = {verts[it->x], verts[it->y], verts[it->z]};
        sf::Vector3f camFace[] = {dots[it->x].toVector3(), dots[it->y].toVector3(), dots[it->z].toVector3()};
        std::vector<Vector4f> intens[] = {intensVerts[it->x], intensVerts[it->y], intensVerts[it->z]};
        shadeVertex(worldFace, camFace, intens, image, zbuffer);
    }

}

float Model::getZ(int x, int y)
{
    sf::Vector3f point(x, y, 0.f);
    float closestZ = Z_OUT;
    for (std::vector<sf::Vector3i>::iterator it=faces.begin(); it != faces.end(); ++it)
    {
        sf::Vector3f camFace[] = {dots[it->x].toVector3(), dots[it->y].toVector3(), dots[it->z].toVector3()};
        if(PointInTriangle(point, camFace[0], camFace[1], camFace[2])) {
            sf::Vector3f normal = GetNormal(camFace);
            float z = (normal.x * (x - camFace[0].x) + normal.y * (y - camFace[0].y) - normal.z * camFace[0].z) / -normal.z;
            if(z > closestZ)
                closestZ = z;
        }
    }
    return closestZ;
}

float Model::getClosestZ(int x, int y)
{
    std::vector<Model*>::iterator it;
    float closestZ = Z_OUT;
    for(it = models.begin();it != models.end();it++) {
        float z = (*it)->getZ(x, y);
        if(z > closestZ)
            closestZ = z;
    }
    return closestZ;
}

Model::~Model()
{

}