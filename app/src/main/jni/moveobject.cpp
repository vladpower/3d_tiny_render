#include "moveobject.hpp"

MoveObject::MoveObject(sf::Vector3f pos, float rad)
{
    position = pos;
    radius = rad;
    radius2 = radius * radius;
    screenPos = sf::Vector3f(0, 0, 0);
    isMoved = false;
    isHidden = false;
}

void MoveObject::buildLines(Matrix4& vp, sf::Vector2u size)
{
    
    lines.clear();
    screenPos = worldToScreen(position, vp, size);
    Vector4f pos(position, 1);
    pos = vp * pos;
    wKoef = pos.w;
    // float z = pos.z;
    // pos = viewport * pos;
    // pos = pos / pos.w;
    // pos.z = z;
    // screenPos = pos.toVector3();
    addBorderCircle(screenPos, radius, lines);
}

void MoveObject::render(Matrix4& vp, sf::Image& image, ZBuffer& zbuffer)
{
    sf::Vector2u size = image.getSize();
    if(isMoved) {
        #ifdef ENABLE_ZBUFFER
        float closestZ = zbuffer.byCoords(newScreenPos.x, newScreenPos.y);
        #else
        float closestZ = Model::getClosestZ(newScreenPos.x, newScreenPos.y);
        #endif
        if(closestZ != Z_OUT) closestZ+=1.f;
        newScreenPos.z = std::max(closestZ, newScreenPos.z);
        position = screenToWorld(newScreenPos, vp, size, wKoef);
        isMoved = false;
        isHidden = false;
    }
    buildLines(vp, size);
    #ifndef ENABLE_ZBUFFER
    float closestZ = Model::getClosestZ(screenPos.x, screenPos.y);
    isHidden = closestZ > screenPos.z + 0.1f;
    #endif
    if(!isHidden) {
        std::map<int, LineX>::iterator it;;
        for(it = lines.begin(); it != lines.end(); it++) {
            int y = it->first;
            LineX line = it->second;
            drawLine(sf::Vector3f(line.x1, y, line.z1), sf::Vector3f(line.x2, y, line.z2), image, zbuffer, roundColor);
        }
    }
    
}

bool MoveObject::isYourPoint(sf::Vector2i point)
{
    
    sf::Vector2i vec = sf::Vector2i(screenPos.x, screenPos.y) - point;
    float dist = vec.x*vec.x + vec.y*vec.y;
    if(dist < radius2) {
        printf("%d %d\n", vec.x, vec.y);
        return true;
    } else {
        return false;
    }
}

void MoveObject::setPosition(sf::Vector2i pos)
{
    newScreenPos = sf::Vector3f(pos.x, pos.y, screenPos.z);
    isMoved = true;
}