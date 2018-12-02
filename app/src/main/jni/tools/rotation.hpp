#ifndef Rotation_H
#define Rotation_H
#include <SFML/System.hpp>
#include <vector>
#include "matrix.hpp"

sf::Vector3f turnCam(sf::Vector3f camPos, sf::Vector3f &camUp, Matrix4 matView, float radius, float angleX, float angleY);

#endif // Rotation_H