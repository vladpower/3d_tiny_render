#ifndef Draw_H
#define Draw_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "matrix.hpp"
#include <map>
#include <unordered_map> 
#include <list>

//#define ENABLE_ZBUFFER

#define Z_OUT -10000.0

struct Dot3D {
    Dot3D(sf::Vector3f world, sf::Vector3f cam)
    {
        this->world = world;
        this->cam = cam;
    }
    sf::Vector3f world;
    sf::Vector3f cam;
};

struct GuroDot {
    GuroDot(sf::Vector3f world, sf::Vector3f cam, std::vector<Vector4f>& intens)
    {
        this->world = world;
        this->cam = cam;
        this->intens = intens;
    }
    sf::Vector3f world;
    sf::Vector3f cam;
    std::vector<Vector4f> intens;
};

struct FongDot {
    FongDot(sf::Vector3f world, sf::Vector3f cam, sf::Vector3f normal)
    {
        this->world = world;
        this->cam = cam;
        this->normal = normal;
    }
    sf::Vector3f world;
    sf::Vector3f cam;
    sf::Vector3f normal;
};

struct LineX {
    LineX() {};
    LineX(int x1, int x2, float z1, float z2, sf::Vector3f worldBeg, sf::Vector3f worldEnd);
    int x1, x2;
    float z1, z2;
    sf::Vector3f worldBeg;
    sf::Vector3f worldEnd;
};

struct LineGuroX {
    LineGuroX() {};
    LineGuroX(int x1, int x2, float z1, float z2, sf::Vector3f worldBeg, sf::Vector3f worldEnd);
    int x1, x2;
    float z1, z2;
    sf::Vector3f worldBeg;
    sf::Vector3f worldEnd;
    std::vector<Vector4f> begIntens;
    std::vector<Vector4f> endIntens;
};

struct LineFongX {
    LineFongX() {};
    LineFongX( int x1, int x2, float z1, float z2, sf::Vector3f worldBeg, sf::Vector3f worldEnd);
    int x1, x2;
    float z1, z2;
    sf::Vector3f worldBeg;
    sf::Vector3f worldEnd;
    sf::Vector3f begNormal;
    sf::Vector3f endNormal;
};

struct Cell {
    Cell() {
        z = Z_OUT;
        //color = sf::Color::White;
    };
	double z;
	sf::Color color;
};

class ZBuffer
{
    private:
        std::unordered_map<long long, float> buf;
        int width;
        int height;
    public:
        ZBuffer(int width, int height);
        void clear();
        float byCoords(int x, int y);
        void setZ(int x, int y, float z);

        ~ZBuffer();
};

void line(sf::Vector3f beg, sf::Vector3f end, std::list<sf::Vector3f>& result);
void line(Dot3D beg, Dot3D end, std::list<Dot3D>& result);
void line(GuroDot beg, GuroDot end, std::list<Dot3D>& result);
void line(FongDot beg, FongDot end, std::list<Dot3D>& result);
bool isValidPoint(const sf::Vector3f &pt, sf::Image& img, ZBuffer& zbuffer);
void drawLine(sf::Vector3f beg, sf::Vector3f end, sf::Image& image, ZBuffer& zbuffer, sf::Color color = sf::Color::Black);
void interpolateLine(GuroDot beg, GuroDot end, sf::Image& image, ZBuffer& zbuffer);
void internormalLine(FongDot beg, FongDot end, sf::Image& image, ZBuffer& zbuffer);
void shadeLine(Dot3D beg, Dot3D end, sf::Image& image, ZBuffer& zbuffer, sf::Vector3f normal);
void shadeFace(sf::Vector3f* worldFace,sf::Vector3f* camFace, sf::Image& image, ZBuffer& zbuffer);
void shadeVertex(sf::Vector3f* worldFace,sf::Vector3f* camFace, std::vector<Vector4f> *intens, sf::Image& image, ZBuffer& zbuffer);
void shadeFongFace(sf::Vector3f* worldFace,sf::Vector3f* camFace, sf::Vector3f* normals, sf::Image& image, ZBuffer& zbuffer);
void shadeFong(std::map<int, LineFongX>& lines, sf::Vector3f* worldFace, sf::Image& image, ZBuffer& zbuffer);
void addBorderLine(Dot3D beg, Dot3D end, std::map<int, LineX>& lines);
void addBorderLine(GuroDot beg, GuroDot end, std::map<int, LineGuroX>& lines);
void addBorderLine(FongDot beg, FongDot end, std::map<int, LineFongX>& lines);
void addBorderPixel(sf::Vector3f point, std::map<int, LineX>& lines);
void addBorderPixel(Dot3D point, std::map<int, LineX>& lines);
void addBorderPixel(GuroDot point, std::map<int, LineGuroX>& lines);
void addBorderPixel(FongDot point, std::map<int, LineFongX>& lines);
void addBorderCircle(sf::Vector3f center, int radius, std::map<int, LineX>& lines);
void bresCircle( sf::Vector3f point, int x, int y, std::map<int, LineX>& lines);
void shadeLambFong(std::map<int, LineX>& lines, sf::Vector3f* worldFace, sf::Image& image, ZBuffer& zbuffer);


#endif // Draw_H