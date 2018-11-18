#include "lamp.hpp"

int Lamp::illuminationType = NoIllumination;
sf::Vector3f Lamp::camPos;

Lamp::Lamp(sf::Vector3f pos, float rad, sf::Color col) : MoveObject(pos, rad)
{
    color = sf::Vector3f(col.r, col.g, col.b);
    lamps.push_back(this);
    intensity = sf::Vector2f(0.1f, 0.4f);
    attenuation = sf::Vector2f(0.1f, 0.05f);
    roundColor = col;
    radius = 5.f;
    radius2 = radius * radius;

}

Lamp* Lamp::getLampByPoint(sf::Vector2i point)
{
    std::vector<Lamp*>::iterator it;
    for(it = lamps.begin(); it != lamps.end(); it++) {
        if((*it)->isYourPoint(point))
            return *it;
    }
    return nullptr;
}

sf::Color Lamp::calcSumLight(sf::Vector3f worldPos, sf::Vector3f normal)
{
    std::vector<Lamp*>::iterator it;
    Vector4f col;
    for(it = lamps.begin(); it != lamps.end(); it++) {
        if(IsLit(normal, worldPos, (*it)->position))
            col = col + (*it)->calcPointLight(worldPos, normal);
    }
    return sf::Color(std::min(col.x, 255.f), std::min(col.y, 255.f), std::min(col.z, 255.f));
}

Vector4f Lamp::fongCalcPointLight(sf::Vector3f worldPos, sf::Vector3f normal)
{
    sf::Vector3f lightDirection = worldPos - position;
    float dist2 = Length2(lightDirection);
    if (dist2 > radius2) {
        return Vector4f();
    }
    float dist = sqrt(dist2);
    lightDirection = Normalize(lightDirection);

    Vector4f color = calcLightInternal(lightDirection, worldPos, normal);

    float attenuation = 1.0 + this->attenuation.x * dist + this->attenuation.y * dist2;
    attenuation = std::max(1.f, attenuation);

    return color / attenuation;
}



Vector4f Lamp::calcLightInternal(sf::Vector3f lightDirection, sf::Vector3f worldPos, sf::Vector3f normal) {
    Vector4f ambientColor = Vector4f(color, 1.f) * intensity.x;
    float diffuseFactor = Dot(normal, -lightDirection);

    Vector4f diffuseColor;
    Vector4f specularColor;

    if (diffuseFactor > 0) {
        diffuseColor = Vector4f(color, 1.0) * intensity.y * diffuseFactor;

        sf::Vector3f vertexToEye = Normalize(worldPos - camPos);
        sf::Vector3f lightReflect = Normalize(Reflect(lightDirection, normal));
        float specularFactor = Dot(vertexToEye, lightReflect);
        specularFactor = powf(specularFactor, LIGHT_SpecularPower);
        if (specularFactor > 0.0) {
            specularColor = Vector4f(color, 1.0) * (LIGHT_MatSpecularIntensity * specularFactor);
        }
    }

    return (diffuseColor + specularColor);
}

Vector4f Lamp::lambertCalcPointLight(sf::Vector3f worldPos, sf::Vector3f normal)
{
    sf::Vector3f lightDirection = worldPos - position;
    float dist2 = Length2(lightDirection);
    if (dist2 > radius2) {
        return Vector4f();
    }
    float dist = sqrt(dist2);
    lightDirection = Normalize(lightDirection);
    Vector4f ambientColor = Vector4f(color, 1.f) * intensity.x;
    float diffuseFactor = Dot(normal, -lightDirection);
    Vector4f diffuseColor = Vector4f(color, 1.0) * intensity.y * diffuseFactor;
    float attenuation = 1.0 + this->attenuation.x * dist + this->attenuation.y * dist2;
    attenuation = std::max(1.f, attenuation);
    return diffuseColor / attenuation;
}

// vec4 calcDirectionalLight(DirectionalLight light, sf::Vector3f worldPos, sf::Vector3f normal) {
//     return calcLightInternal(light.base, light.direction, worldPos, normal);
// }

void Lamp::getIntensVector(sf::Vector3f worldPos, sf::Vector3f normal, std::vector<Vector4f>& intens) {
    std::vector<Lamp*>::iterator it;
    for(it = lamps.begin(); it != lamps.end(); it++) {
        intens.push_back((*it)->calcPointLight(worldPos, normal));
    }
}

Vector4f Lamp::calcPointLight(sf::Vector3f worldPos, sf::Vector3f normal) {
    switch(illuminationType) {
        case LambertIllumination:
            return lambertCalcPointLight(worldPos, normal);
        case GuroIllumination:
            return fongCalcPointLight(worldPos, normal);
        case FongIllumination:
            return fongCalcPointLight(worldPos, normal);
    }
}

Lamp::~Lamp()
{

}