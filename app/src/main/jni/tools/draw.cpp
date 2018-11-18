#include "draw.hpp"
#include "../lamp.hpp"
#define NOT_FOUND (-10000)
#define NOT_FOUND_PAIR (std::pair<int, int>( NOT_FOUND, NOT_FOUND))

LineX::LineX(int x1, int x2, float z1, float z2, sf::Vector3f worldBeg, sf::Vector3f worldEnd)
{
    this->x1 = x1;
    this->x2 = x2;
    this->z1 = z1;
    this->z2 = z2;
    this->worldBeg = worldBeg;
    this->worldEnd = worldEnd;
};

LineGuroX::LineGuroX(int x1, int x2, float z1, float z2, sf::Vector3f worldBeg, sf::Vector3f worldEnd)
{
    this->x1 = x1;
    this->x2 = x2;
    this->z1 = z1;
    this->z2 = z2;
    this->worldBeg = worldBeg;
    this->worldEnd = worldEnd;
};

ZBuffer::ZBuffer(int width, int height)
{
    this->width = width;
    this->height = height;
    
}

void ZBuffer::clear()
{
    buf.clear();
}

float ZBuffer::byCoords(int x, int y)
{
    std::unordered_map<long long, float>::iterator it = buf.find((static_cast<long long>(x)<<32) | y);
    if(it != buf.end())
        return it->second;
    return Z_OUT;
}

void ZBuffer::setZ(int x, int y, float z)
{
    buf[(static_cast<long long>(x)<<32) | y] = z;
}

ZBuffer::~ZBuffer()
{
    
}

float abs(float val)
{
    return val > 0 ? val : -val;
}

void line(sf::Vector3f beg, sf::Vector3f end, std::list<sf::Vector3f>& result)
{
    bool steep = abs(end.y - beg.y) > abs(end.x - beg.x);
    if (steep) {
        std::swap(beg.x, beg.y);
        std::swap(end.x, end.y);
    }
    if (beg.x > end.x) {
        std::swap(beg.x, end.x);
        std::swap(beg.y, end.y);
        std::swap(beg.z, end.z);
    }
    int dx = end.x - beg.x;
    int dy = abs(end.y - beg.y);
    int error = dx / 2;
    int ystep = (beg.y < end.y) ? 1 : -1;
    int y = int(beg.y + 0.5);
    float z = beg.z;
    float zstep = (end.z-beg.z) / (end.x-beg.x);
    for (int x = int(beg.x + 0.5); x <= int(end.x + 0.5); x++, z+=zstep)
    {
        sf::Vector3f point(steep ? y : x, steep ? x : y, z);
        result.push_back(point);
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void line(Dot3D beg, Dot3D end, std::list<Dot3D>& result)
{
    bool steep = abs(end.cam.y - beg.cam.y) > abs(end.cam.x - beg.cam.x);
    if (steep) {
        std::swap(beg.cam.x, beg.cam.y);
        std::swap(end.cam.x, end.cam.y);
    }
    if (beg.cam.x > end.cam.x) {
        std::swap(beg, end);
    }
    int dx = end.cam.x - beg.cam.x;
    int dy = abs(end.cam.y - beg.cam.y);
    int error = dx / 2;
    int ystep = (beg.cam.y < end.cam.y) ? 1 : -1;
    int y = int(beg.cam.y + 0.5);
    float z = beg.cam.z;
    float zstep = (end.cam.z-beg.cam.z) / (end.cam.x-beg.cam.x);
    sf::Vector3f delta = (end.world - beg.world) / (end.cam.x - beg.cam.x);
    sf::Vector3f worldPoint = beg.world;
    for (int x = int(beg.cam.x + 0.5); x <= int(end.cam.x + 0.5); x++, z+=zstep, worldPoint+=delta)
    {
        sf::Vector3f camPoint(steep ? y : x, steep ? x : y, z);
        result.push_back(Dot3D(worldPoint ,camPoint));
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void line(GuroDot beg, GuroDot end, std::list<GuroDot>& result)
{
    bool steep = abs(end.cam.y - beg.cam.y) > abs(end.cam.x - beg.cam.x);
    if (steep) {
        std::swap(beg.cam.x, beg.cam.y);
        std::swap(end.cam.x, end.cam.y);
    }
    if (beg.cam.x > end.cam.x) {
        std::swap(beg, end);
    }
    float fdx = (end.cam.x - beg.cam.x);
    int dx = static_cast<int>(fdx);
    int dy = abs(end.cam.y - beg.cam.y);
    int error = dx / 2;
    int ystep = (beg.cam.y < end.cam.y) ? 1 : -1;
    int y = int(beg.cam.y + 0.5);
    float z = beg.cam.z;
    float zstep = (end.cam.z-beg.cam.z) / (end.cam.x-beg.cam.x);
    sf::Vector3f delta = (end.world - beg.world) / fdx;
    sf::Vector3f worldPoint = beg.world;
    std::vector<Vector4f> curIntens = beg.intens;
    std::vector<Vector4f> deltaIntens = end.intens;
    for(int i=0;i<beg.intens.size();i++) {
        const Vector4f& dlt = deltaIntens[i];
        const Vector4f& begInt = beg.intens[i];
        deltaIntens[i] = (dlt - begInt);
        deltaIntens[i] = deltaIntens[i] / fdx;
    }
        
    for (int x = int(beg.cam.x + 0.5); x <= int(end.cam.x + 0.5); x++, z+=zstep, worldPoint+=delta)
    {
        sf::Vector3f camPoint(steep ? y : x, steep ? x : y, z);
        result.push_back(GuroDot(worldPoint ,camPoint, curIntens));
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
        for(int i=0;i<beg.intens.size();i++)
            curIntens[i] = curIntens[i] + deltaIntens[i];
    }
}

void drawLine(sf::Vector3f beg, sf::Vector3f end, sf::Image& image, ZBuffer& zbuffer, sf::Color color)
{
    std::list<sf::Vector3f> dotList;
    line(beg, end, dotList);
    std::list<sf::Vector3f>::iterator point;
    for(point = dotList.begin(); point!=dotList.end();point++) 
    {
        // int r = 128 - point->z*100;
        // if(r>255) r = 255;
        // if(r<0) r = 0;
        // if(isValidPoint(*point, image, zbuffer))
        //     image.setPixel( point->x, point->y, sf::Color(r, 0, 0, 255));
        if(isValidPoint(*point, image, zbuffer))
            image.setPixel( point->x, point->y, color);
    }
}

void interpolateLine(GuroDot beg, GuroDot end, sf::Image& image, ZBuffer& zbuffer)
{
    std::list<GuroDot> dotList;
    line(beg, end, dotList);
    std::list<GuroDot>::iterator point;
    for(point = dotList.begin(); point!=dotList.end();point++) 
    {
        std::vector<Vector4f>& intens = point->intens;
        Vector4f colorVec(0.f, 0.f, 0.f, 1.f);
        for(int i=0;i<intens.size();i++) {
            colorVec = colorVec + intens[i];
        }
        sf::Color color(std::min(colorVec.x, 255.f), std::min(colorVec.y, 255.f), std::min(colorVec.z, 255.f));
        if(isValidPoint(point->cam, image, zbuffer))
            image.setPixel( point->cam.x, point->cam.y, color);
    }
}

void shadeLine(Dot3D beg, Dot3D end, sf::Image& image, ZBuffer& zbuffer, sf::Vector3f normal)
{
    std::list<Dot3D> dotList;
    line(beg, end, dotList);
    std::list<Dot3D>::iterator point;
    for(point = dotList.begin(); point!=dotList.end();point++) 
    {
        sf::Color color = Lamp::calcSumLight(point->world, normal);
        if(isValidPoint(point->cam, image, zbuffer))
            image.setPixel( point->cam.x, point->cam.y, color);
    }
}

void addBorderLine(Dot3D beg, Dot3D end, std::map<int, LineX>& lines)
{
    std::list<Dot3D> dotList;
    line(beg, end, dotList);
    std::list<Dot3D>::iterator point;
    for(point = dotList.begin(); point!=dotList.end();point++) 
    {
        addBorderPixel(Dot3D(point->world, point->cam), lines);
    }
    sf::Vector3f lastCamPoint(int(end.cam.x + 0.5), int(end.cam.y + 0.5), end.cam.z);
    addBorderPixel(Dot3D(end.world, lastCamPoint), lines);
}

void addBorderLine(GuroDot beg, GuroDot end, std::map<int, LineGuroX>& lines)
{
    std::list<GuroDot> dotList;
    line(beg, end, dotList);
    std::list<GuroDot>::iterator point;
    for(point = dotList.begin(); point!=dotList.end();point++) 
    {
        addBorderPixel(*point, lines);
    }
    sf::Vector3f lastCamPoint(int(end.cam.x + 0.5), int(end.cam.y + 0.5), end.cam.z);
    addBorderPixel(end, lines);
}

void addBorderPixel(sf::Vector3f point, std::map<int, LineX>& lines)
{
    Dot3D dot(sf::Vector3f(0.f, 0.f, 0.f), point);
    addBorderPixel(dot, lines);
}

void addBorderPixel(Dot3D point, std::map<int, LineX>& lines)
{
    int x = static_cast<int>(point.cam.x+0.5);
    int y = static_cast<int>(point.cam.y+0.5);
    float z = point.cam.z;
    std::map<int, LineX>::iterator it;
    it = lines.find(y);
    if(it != lines.end()) {
        LineX line = it->second;
        if(x < line.x1) {
            line.x1 = x;
            line.z1 = z;
            line.worldBeg = point.world;
        } else if( x > line.x2) {
            line.x2 = x;
            line.z2 = z;
            line.worldEnd = point.world;
        }
        lines[y] = line;
    } else {
        LineX line(x, x, z, z, point.world, point.world);
        lines[y] = line;
    }
}

void addBorderPixel(GuroDot point, std::map<int, LineGuroX>& lines)
{
    int x = static_cast<int>(point.cam.x+0.5);
    int y = static_cast<int>(point.cam.y+0.5);
    float z = point.cam.z;
    std::map<int, LineGuroX>::iterator it;
    it = lines.find(y);
    if(it != lines.end()) {
        LineGuroX line = it->second;
        if(x < line.x1) {
            line.x1 = x;
            line.z1 = z;
            line.worldBeg = point.world;
            line.begIntens = point.intens;
        } else if( x > line.x2) {
            line.x2 = x;
            line.z2 = z;
            line.worldEnd = point.world;
            line.endIntens = point.intens;
        }
        lines[y] = line;
    } else {
        LineGuroX line(x, x, z, z, point.world, point.world);
        line.begIntens = point.intens;
        line.endIntens = point.intens;
        lines[y] = line;
    }
}

void shadeFace(sf::Vector3f* worldFace,sf::Vector3f* camFace, sf::Image& image, ZBuffer& zbuffer)
{
    sf::Vector2f vec1(camFace[1].x-camFace[0].x, camFace[1].y-camFace[0].y);
    sf::Vector2f vec2(camFace[2].x-camFace[1].x, camFace[2].y-camFace[1].y);
    float z = vec1.x * vec2.y - vec2.x * vec1.y;
    if(z > 0)
        return;
    
    std::map<int, LineX> lines;
    Dot3D face[] = {Dot3D(worldFace[0], camFace[0]), Dot3D(worldFace[1], camFace[1]), Dot3D(worldFace[2], camFace[2])};
    addBorderLine(face[0], face[1], lines);
    addBorderLine(face[1], face[2], lines);
    addBorderLine(face[2], face[0], lines);

    shadeLambFong(lines, worldFace, image, zbuffer);
}

void shadeVertex(sf::Vector3f* worldFace,sf::Vector3f* camFace, std::vector<Vector4f> *intens, sf::Image& image, ZBuffer& zbuffer)
{
    sf::Vector2f vec1(camFace[1].x-camFace[0].x, camFace[1].y-camFace[0].y);
    sf::Vector2f vec2(camFace[2].x-camFace[1].x, camFace[2].y-camFace[1].y);
    float z = vec1.x * vec2.y - vec2.x * vec1.y;
    if(z > 0)
        return;
    
    std::map<int, LineGuroX> lines;
    GuroDot face[] = {GuroDot(worldFace[0], camFace[0], intens[0]), GuroDot(worldFace[1], camFace[1], intens[1]), GuroDot(worldFace[2], camFace[2], intens[2])};
    addBorderLine(face[0], face[1], lines);
    addBorderLine(face[1], face[2], lines);
    addBorderLine(face[2], face[0], lines);

    std::map<int, LineGuroX>::iterator it;;
    for(it = lines.begin(); it != lines.end(); it++) {
        LineGuroX lin = it->second;
        GuroDot beg(lin.worldBeg, sf::Vector3f(lin.x1, it->first, lin.z1), lin.begIntens);
        GuroDot end(lin.worldEnd, sf::Vector3f(lin.x2, it->first, lin.z2), lin.endIntens);
        interpolateLine(beg, end, image, zbuffer);
    }
}

void shadeLambFong(std::map<int, LineX>& lines, sf::Vector3f* worldFace, sf::Image& image, ZBuffer& zbuffer)
{
    sf::Vector3f normal = GetNormal(worldFace);
    std::map<int, LineX>::iterator it;;
    for(it = lines.begin(); it != lines.end(); it++) {
        LineX lin = it->second;
        Dot3D beg(lin.worldBeg, sf::Vector3f(lin.x1, it->first, lin.z1));
        Dot3D end(lin.worldEnd, sf::Vector3f(lin.x2, it->first, lin.z2));
        shadeLine(beg, end, image, zbuffer, normal);
    }
}

bool isValidPoint(const sf::Vector3f &pt, sf::Image& img, ZBuffer& zbuffer)
{
    int x = pt.x;
    int y = pt.y;
    sf::Vector2u size = img.getSize();
    if ((x >= size.x) || (y >= size.y))
        return false;
    if ((x < 0) || (y < 0))
        return false;

    #ifdef ENABLE_ZBUFFER
    if (pt.z < zbuffer.byCoords(x, y))
        return false;
    zbuffer.setZ(x, y, pt.z);
    #endif
    return true;
}

void bresCircle( sf::Vector3f point, int x, int y, std::map<int, LineX>& lines)
{ 
    int xc = static_cast<int>(point.x);
    int yc = static_cast<int>(point.y);
    float zc = point.z;
    addBorderPixel(sf::Vector3f(xc+x, yc+y, zc), lines);
    addBorderPixel(sf::Vector3f(xc-x, yc+y, zc), lines);
    addBorderPixel(sf::Vector3f(xc+x, yc-y, zc), lines);
    addBorderPixel(sf::Vector3f(xc-x, yc-y, zc), lines);
    addBorderPixel(sf::Vector3f(xc+y, yc+x, zc), lines);
    addBorderPixel(sf::Vector3f(xc-y, yc+x, zc), lines);
    addBorderPixel(sf::Vector3f(xc+y, yc-x, zc), lines);
    addBorderPixel(sf::Vector3f(xc-y, yc-x, zc), lines);
}

void addBorderCircle(sf::Vector3f center, int radius, std::map<int, LineX>& lines)
{ 
    int x = 0, y = radius; 
    int d = 3 - 2 * radius; 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
        bresCircle(center, x, y, lines); 
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
    } 
} 