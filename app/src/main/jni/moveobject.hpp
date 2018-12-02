#ifndef moveobject_hpp
#define moveobject_hpp
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "tools/draw.hpp"
#include "tools/matrix.hpp"
#include "model.hpp"


class MoveObject
{
    private:
        float radius;
        float radius2;
        sf::Vector3f screenPos;
        sf::Vector3f newScreenPos;
        bool isMoved;
        bool isHidden;
        float wKoef;
        std::map<int, LineX> lines;
        void buildLines(Matrix4& vp, sf::Vector2u size);
        
    public:
        static bool isAutoMove;
        MoveObject(sf::Vector3f pos, float radius);
        void render(Matrix4& vp, sf::Image& image, ZBuffer& zbuffer);
        bool isYourPoint(sf::Vector2i point);
        void setPosition(sf::Vector2i pos);
        
    protected:
        sf::Vector3f position;
        sf::Color roundColor;
};

#endif //moveobject_hpp