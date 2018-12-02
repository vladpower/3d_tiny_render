#ifndef Matrix_H
#define Matrix_H
#include <SFML/System.hpp>
#include <vector>
enum Axis {x,y,z};

struct Vector4f
{
	float x;
	float y;
	float z;
	float w;
	Vector4f(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.f){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Vector4f(sf::Vector3f xyz, float w)
	{
		x = xyz.x;
		y = xyz.y;
		z = xyz.z;
		this->w = w;
	}
	sf::Vector3f toVector3()
	{
		sf::Vector3f vec(x, y, z);
		return vec;
	}
	sf::Vector2f toVector2()
	{
		sf::Vector2f vec(x, y);
		return vec;
	}
};

class Matrix3
{
public:
	Matrix3();
	~Matrix3();
	void Identity();
	float Determinant();
	float matrix[9];
};

class Matrix4
{
public:
	Matrix4();
	~Matrix4();
	void Identity();
	void Translate(sf::Vector3f vec);
	void Scale(sf::Vector3f vec);
	void Rotate(float angle, Axis ax);
	Matrix4& operator= (const Matrix4 &matr);
	Matrix4& operator*= (const Matrix4 &matr);
	float Determinant();
	Matrix4* Transpose();
	Matrix4* Inverse();
	Matrix4* LookAt(sf::Vector3f cameraPos, sf::Vector3f cameraTarget, sf::Vector3f cameraUp);
	// Matrix4* Perspective( float field_of_view, float aspect_ratio,
    //                        float near_plane, float far_plane );
	Matrix4* Projection( float dist, float aspect_ratio);
	Matrix4* ViewPort(int x, int y, int w, int h);



	float matrix[16];
	
};

Vector4f operator*(Vector4f vec, float a);
Vector4f operator+(Vector4f vec1, Vector4f vec2);
Vector4f operator-(Vector4f vec1, Vector4f vec2);

float PosRelativeLine(sf::Vector3f a, sf::Vector3f b, sf::Vector3f d);
bool PointInTriangle (sf::Vector3f pt, sf::Vector3f v1, sf::Vector3f v2, sf::Vector3f v3);
bool IsLit(sf::Vector3f normal, sf::Vector3f point0, sf::Vector3f point);
sf::Vector3f GetNormal(sf::Vector3f* face);
float Length2(sf::Vector3f vec);
sf::Vector3f Normalize(sf::Vector3f vec);
float Dot(sf::Vector3f vec1, sf::Vector3f vec2);
float Norm(sf::Vector3f vec);
Matrix4 operator*(Matrix4 &matr1, Matrix4 &matr2);
Vector4f operator*(Matrix4 &matr, Vector4f &vec);
Vector4f operator/(Vector4f a, float b);
sf::Vector3f operator*(sf::Vector3f a, sf::Vector3f b);
sf::Vector3f operator-(sf::Vector3f vec);
sf::Vector3f operator/(sf::Vector3f a, float b);
sf::Vector3f worldToScreen(sf::Vector3f point, Matrix4& vp, sf::Vector2u size);
sf::Vector3f screenToWorld(sf::Vector3f point, Matrix4 vp, sf::Vector2u size, float wKoef);
sf::Vector3f Reflect(sf::Vector3f incident, sf::Vector3f normal);

#endif // Matrix_H