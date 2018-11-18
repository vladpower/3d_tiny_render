#ifndef lamp_hpp
#define lamp_hpp
#include "moveobject.hpp"
#include <cmath>
#include <vector>

#ifndef LIGHT_SpecularPower
#define LIGHT_SpecularPower 1.f
#endif
#ifndef LIGHT_MatSpecularIntensity
#define LIGHT_MatSpecularIntensity 0.7f
#endif

enum IlluminationType {
    NoIllumination,
    LambertIllumination,
    GuroIllumination,
    FongIllumination
};

class Lamp: public MoveObject {
    private:
        //BaseLight
        sf::Vector3f color;
        sf::Vector2f intensity; // (ambient, diffuse)
        //PointLight
        sf::Vector2f attenuation; // (linear, exp)
        float radius;
        float radius2;
    public:
        Lamp(sf::Vector3f pos, float rad, sf::Color col);
        Vector4f calcLightInternal(sf::Vector3f lightDirection, sf::Vector3f worldPos, sf::Vector3f normal);
        Vector4f calcPointLight(sf::Vector3f worldPos, sf::Vector3f normal);
        Vector4f fongCalcPointLight(sf::Vector3f worldPos, sf::Vector3f normal);
        Vector4f lambertCalcPointLight(sf::Vector3f worldPos, sf::Vector3f normal);

        static sf::Color calcSumLight(sf::Vector3f worldPos, sf::Vector3f normal);
        static std::vector<Lamp*> lamps;
        static int illuminationType;
        static sf::Vector3f camPos;

        static Lamp* getLampByPoint(sf::Vector2i point);
        static void getIntensVector(sf::Vector3f worldPos, sf::Vector3f normal, std::vector<Vector4f>& intens);
        ~Lamp();
};

#endif // lamp_hpp