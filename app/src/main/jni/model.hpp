#ifndef model_hpp
#define model_hpp
#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "tools/matrix.hpp"
#include "tools/draw.hpp"
class Model {
private:
    void shadeFaces(sf::Image& image, ZBuffer& zbuffer);
    void shadeVerts(sf::Image& image, ZBuffer& zbuffer);
    std::vector<Vector4f> dots;
public: 
    Model();
    void render(Matrix4& vp, sf::Image& image, ZBuffer& zbuffer);
    float getZ(int x, int y);
    static float getClosestZ(int x, int y);
    ~Model();

    static std::vector<Model*> models;
protected:
    std::vector<sf::Vector3f> verts;
    std::vector<sf::Vector2i> edges;
    std::vector<sf::Vector3i> faces;

};

#endif //model_hpp