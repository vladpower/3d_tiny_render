#include "rotation.hpp"
#include "matrix.hpp"
#include <cmath>

// sf::Vector3f turnCam(sf::Vector3f camPos, sf::Vector3f &camUp, Matrix4 matView, float radius, float angleX, float angleY)
// {
//     // float x0 = camPos.x, y0 = camPos.y, z0 = camPos.z;
//     // float A = -rad * z0, B = 0, C = x0 * rad, D = -rad;
//     // float x = -(1 + B * rad + C * z0) / A;
//     // float y = rad;
//     // float z = (-rad * (D + y0) + x0 / A * (1 + B * rad) / (z0 - C * x0 / A));

//     camUp = sf::Vector3f( matView.matrix[4], matView.matrix[5], matView.matrix[6]);
//     Matrix4  rotMat;
//     float cAng = cos(angleX);
//     float sAng = sin(angleX);
//     float vAng = 1 - cAng;
//     rotMat.matrix[0] = pow(camUp.x, 2) * vAng + cAng;
//     rotMat.matrix[1] = camUp.x * camUp.y * vAng - camUp.z * sAng;
//     rotMat.matrix[2] = camUp.x * camUp.z * vAng + camUp.y * sAng;
//     rotMat.matrix[4] = camUp.x * camUp.y * vAng + camUp.z * sAng;
//     rotMat.matrix[5] = pow(camUp.y, 2) * vAng + cAng;
//     rotMat.matrix[6] = camUp.y * camUp.z * vAng - camUp.x * sAng;
//     rotMat.matrix[8] = camUp.x * camUp.z * vAng - camUp.y * sAng;
//     rotMat.matrix[9] = camUp.y * camUp.z * vAng + camUp.x * sAng;
//     rotMat.matrix[10] = pow(camUp.z, 2) * vAng + cAng;
//     rotMat.matrix[15] = 1;

//     Vector4f position(camPos, 1);

//     return (rotMat * position).toVector3();
// }
