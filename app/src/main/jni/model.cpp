#include "model.hpp"
#include "lamp.hpp"

std::vector<Model*> Model::models;

Model::Model()
{
    models.push_back(this);
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