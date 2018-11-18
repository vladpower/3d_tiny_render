#include "matrix.hpp"
#include <cmath>

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0;
}
Matrix4::~Matrix4()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0;
}

Vector4f operator*(Vector4f vec, float a)
{
	return Vector4f(vec.x * a, vec.y * a, vec.z * a, vec.w * a);
}
Vector4f operator+(Vector4f vec1, Vector4f vec2)
{
	return Vector4f(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
}
Vector4f operator-(Vector4f vec1, Vector4f vec2)
{
	return Vector4f(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
}

bool IsLit(sf::Vector3f normal, sf::Vector3f point0, sf::Vector3f point)
{
	float value = normal.x * (point.x - point0.x) + normal.y * (point.y - point0.y) + normal.z * (point.z - point0.z);
	if(value > 0)
	    return true;
	else
	    return false;
}

sf::Vector3f GetNormal(sf::Vector3f* face)
{
	sf::Vector3f vec1(face[1].x-face[0].x, face[1].y-face[0].y, face[1].z-face[0].z);
    sf::Vector3f vec2(face[2].x-face[1].x, face[2].y-face[1].y, face[2].z-face[1].z);
	return vec1 * vec2;
}

sf::Vector3f Normalize(sf::Vector3f vec)
{
	float normal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
	return{ vec.x /= normal, vec.y /= normal, vec.z /= normal };
}

sf::Vector3f Reflect(sf::Vector3f incident, sf::Vector3f normal)
{
	return incident - (normal * 2.f * Dot(normal, incident));
}

float Length2(sf::Vector3f vec)
{
	return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
}

float Dot(sf::Vector3f vec1, sf::Vector3f vec2)
{
	return (vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z);
}

sf::Vector3f Cross(sf::Vector3f &vec1, sf::Vector3f &vec2)
{
	return{ (vec1.y*vec2.z - vec1.z*vec2.y),(vec1.z*vec2.x - vec1.x*vec2.z),(vec1.x*vec2.y - vec1.y*vec2.x) };
}

sf::Vector3f operator*(sf::Vector3f a, sf::Vector3f b)
{
	return Cross(a, b);
}

sf::Vector3f operator-(sf::Vector3f vec)
{
	return sf::Vector3f(-vec.x, -vec.y, -vec.z);
}

Vector4f operator/(Vector4f& a, float b)
{
	return Vector4f(a.x/b, a.y/b, a.z/b, a.w/b);
}


// Matrix4* Matrix4::LookAt(sf::Vector3f cameraPos, sf::Vector3f cameraTarget, sf::Vector3f cameraUp)
// {
// 	sf::Vector3f zaxis = Normalize(cameraPos - cameraTarget);
// 	sf::Vector3f xaxis = Normalize(Cross(cameraUp, zaxis));
// 	sf::Vector3f yaxis = Normalize(Cross(zaxis, xaxis));
    
// 	matrix[0] = xaxis.x;      matrix[1] = yaxis.x;			matrix[2] =  -zaxis.x;			matrix[3] =  0;
// 	matrix[4] = xaxis.y;      matrix[5] = yaxis.y;			matrix[6] =  -zaxis.y;			matrix[7] =  0;
// 	matrix[8] = xaxis.z;	  matrix[9] = yaxis.z;			matrix[10] = -zaxis.z;			matrix[11] = 0;
// 	matrix[12] = 0;           matrix[13] = 0;		        matrix[14] = 0;		            matrix[15] = 1;

//     Matrix4 Tr;
// 	Tr.Identity();
// 	Tr.matrix[3] = -cameraTarget.x;
// 	Tr.matrix[7] = -cameraTarget.y;
// 	Tr.matrix[11] = -cameraTarget.z;
// 	*this = *this * Tr;
// 	return Inverse();
// 	//return this;
// }


float PosRelativeLine (sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (sf::Vector3f pt, sf::Vector3f v1, sf::Vector3f v2, sf::Vector3f v3)
{
    bool b1, b2, b3;

    b1 = PosRelativeLine(pt, v1, v2) < 0.0f;
    b2 = PosRelativeLine(pt, v2, v3) < 0.0f;
    b3 = PosRelativeLine(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

Matrix4* Matrix4::LookAt(sf::Vector3f cameraPos, sf::Vector3f cameraTarget, sf::Vector3f cameraUp)
{
	sf::Vector3f zaxis = Normalize(cameraPos - cameraTarget);
	sf::Vector3f xaxis = Normalize(Cross(cameraUp, zaxis));
	sf::Vector3f yaxis = Normalize(Cross(zaxis, xaxis));
    
	matrix[0] = xaxis.x;      matrix[1] = xaxis.y;			matrix[2] =  xaxis.z;			matrix[3] =  -Dot(xaxis, cameraTarget);
	matrix[4] = yaxis.x;      matrix[5] = yaxis.y;			matrix[6] =  yaxis.z;			matrix[7] =  -Dot(yaxis, cameraTarget);
	matrix[8] =-zaxis.x;	  matrix[9] =-zaxis.y;			matrix[10] =-zaxis.z;			matrix[11] = -Dot(zaxis, cameraTarget);
	matrix[12] = 0;           matrix[13] = 0;		        matrix[14] = 0;		            matrix[15] = 1;

	return this;
}

// Matrix4* Matrix4::Projection( float dist, float aspect_ratio) {
//     Identity();
// 	float coef = 1.f / dist;
// 	matrix[0] = coef;
// 	matrix[5] = aspect_ratio * coef;
// 	matrix[10] = -coef;
//     return this;
// }

Matrix4* Matrix4::Projection( float dist, float aspect_ratio) {
    Identity();
	float coef = 1.f / dist;
	matrix[0] = coef;
	matrix[5] = aspect_ratio * coef;
	matrix[14] = -coef;
    return this;
}

sf::Vector3f worldToScreen(sf::Vector3f point, Matrix4& vp, sf::Vector2u size)
{
	Vector4f pos(point, 1);
    pos = vp * pos;
    float z = pos.z;
	pos = pos / pos.w;
	pos.x = (((pos.x + 1.f) * 0.5f) * size.x);
    pos.y = (((pos.y + 1.f) * 0.5f) * size.y);
    pos.z = z;
	return pos.toVector3();
}

sf::Vector3f screenToWorld(sf::Vector3f point, Matrix4 vp, sf::Vector2u size, float wKoef)
{
	Vector4f pos(point, 1);
	vp.Inverse();
	pos.x = ((pos.x / ((float) size.x)) * 2.f) - 1.f;
    pos.y = (((pos.y / ((float) size.y)) * 2.f) - 1.f);
    pos = vp * pos;
	pos = pos / pos.w;
	return pos.toVector3();
}

// Matrix4* Matrix4::Perspective( float field_of_view, float aspect_ratio,
//                                float near_plane, float far_plane ) {
//     float f = 1.0f / tanf( ( 0.5f * field_of_view ) ),
// 	      A = far_plane / (far_plane - near_plane),
// 		  B = (-1.f * far_plane * near_plane) / (far_plane - near_plane);
// 	for (int i = 0; i < 16; i++)
// 		matrix[i] = 0;
// 	matrix[0] = f / aspect_ratio;
// 	matrix[5] = f;
// 	matrix[10] = A;
// 	matrix[14] = 1.f;
// 	matrix[11] = B;
	
	
//     return this;
// }

Matrix4* Matrix4::ViewPort(int x, int y, int w, int h)
{
	Identity();
	matrix[3] = x+w/2.f;
	matrix[7] = y+h/2.f;
	matrix[11] = 1.f;
	matrix[0] = w/2.f;
	matrix[5] = h/2.f;
	matrix[10] = 0;

	return this;
}

void Matrix4::Identity()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0;
	matrix[0] = 1;
	matrix[5] = 1;
	matrix[10] = 1;
	matrix[15] = 1; 
}
/*
void Matrix4::Perspective(float FoV, float aspect, float zNear, float zFar)
{
	float f = 1 / tanf(FoV / 2),
		A = (zFar + zNear) / (zNear - zFar),
		B = (2 * zFar * zNear) / (zNear - zFar);

	matrix[0] = f / aspect; matrix[1] = 0; matrix[2] = 0; matrix[3] = 0;
	matrix[4] = 0;          matrix[5] = f; matrix[6] = 0; matrix[7] = 0;
	matrix[8] = 0;          matrix[9] = 0; matrix[10] = A; matrix[11] = B;
	matrix[12] = 0;         matrix[13] = 0; matrix[14] = -1; matrix[15] = 0;
}
*/
void Matrix4::Translate(sf::Vector3f vec) 
{
	matrix[3] += vec.x;
	matrix[7] += vec.y;
	matrix[11] += vec.z;
}
void Matrix4::Scale(sf::Vector3f vec)
{
	matrix[0] *= vec.x;
	matrix[5] *= vec.y;
	matrix[10] *= vec.z;
}
/*
void Matrix4::Rotate(float angle, Axis ax)
{
	float newX, newY, newZ;
	switch (ax)
	{
	case x:
		newY = cosf(angle) * matrix[5] - sinf(angle)*matrix[10];
		newZ = sinf(angle) * matrix[5] + sinf(angle)*matrix[10];
		matrix[5] = newY; matrix[10] = newZ;
		break;
	case y:
		newX = cosf(angle)*matrix[0] + sinf(angle)*matrix[10];
		newZ = -sinf(angle)*matrix[0] + cosf(angle)*matrix[10];
		matrix[0] = newX; matrix[10] = newZ;
		break;
	case z:
		newX = cosf(angle)* matrix[0] - sinf(angle) * matrix[5];
		newY = sinf(angle)*matrix[0] + cosf(angle)*matrix[5];
		matrix[0] = newX; matrix[5] = newY;
		break;
	default:
		break;
	}
}
*/
Matrix4 operator*(Matrix4 &matr1, Matrix4 &matr2)
{
	Matrix4 matr;

	for(int i=0;i<16;i++)
	{
		matr.matrix[i] = 0;
		int x = i% 4, y = i / 4;
		for(int j=0;j<4;j++)
		{
			matr.matrix[i] += matr1.matrix[y*4+j] * matr2.matrix[j*4+x];
		}
	}
	return matr;
}

Matrix4& Matrix4::operator= (const Matrix4 &matr)
{
	if (this == &matr) {
		return *this;
	}

	for (int i = 0; i < 16; i++)
		(*this).matrix[i] = matr.matrix[i];
	return *this;
}
/*
Vector4 Matrix4::ToVector4()
{
	return{ matrix[0],matrix[5],matrix[10],matrix[15] };
}
float* Matrix4::ToGLfloat()
{
	return{ matrix };
}
*/
Vector4f operator*(Matrix4 &matr, Vector4f &vec)
{
	Vector4f ret(
	ret.x = matr.matrix[0]  * vec.x + matr.matrix[1]  * vec.y + matr.matrix[2]  * vec.z + matr.matrix[3]  * vec.w,
	ret.y = matr.matrix[4]  * vec.x + matr.matrix[5]  * vec.y + matr.matrix[6]  * vec.z + matr.matrix[7]  * vec.w,
	ret.z = matr.matrix[8]  * vec.x + matr.matrix[9]  * vec.y + matr.matrix[10] * vec.z + matr.matrix[11] * vec.w,
	ret.w = matr.matrix[12] * vec.x + matr.matrix[13] * vec.y + matr.matrix[14] * vec.z + matr.matrix[15] * vec.w);
	return ret;
}


float Matrix4::Determinant()
{
	float vec[4];
	for(int i=0;i<4;i++)
	{
		Matrix3 mat3;
		int x = i%4, z = 0;
		for(int j=4;j<16;j++) {
			if(j%4!=x) {
				mat3.matrix[z] = matrix[j];
				z++;
			}
		}
		vec[i] = mat3.Determinant();
	}
	float res = 0;
	for(int i=0;i<4;i++)
	    res += vec[i] * matrix[i];
	return res;
}

Matrix4* Matrix4::Transpose()
{
	std::swap(matrix[1], matrix[4]);
	std::swap(matrix[2], matrix[8]);
	std::swap(matrix[3], matrix[12]);
	std::swap(matrix[6], matrix[9]);
	std::swap(matrix[7], matrix[13]);
	std::swap(matrix[11], matrix[14]);
	return this;
}

Matrix4* Matrix4::Inverse()
{
	Matrix4 AT;
	float* inv = AT.matrix, *m = matrix;
	float det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det != 0) {
        det = 1.0 / det;
        for (i = 0; i < 16; i++)
            inv[i] = inv[i] * det;
	    *this = AT;
	}
	return this;

}

Matrix3::Matrix3()
{
	for (int i=0; i < 9; i++)
	{
		matrix[i] = 0;
	}
}

Matrix3::~Matrix3()
{
	for (int i=0; i < 9; i++)
	{
		matrix[i] = 0;
	}
}

void Matrix3::Identity()
{
	for (int i=0; i < 9; i++)
	{
		matrix[i] = 0;
	}
	matrix[0] = matrix[4] = matrix[8] = 1;
}

float Matrix3::Determinant()
{
	float res = ((matrix[0] * matrix[4] * matrix[8]) + (matrix[1] * matrix[5] * matrix[6]) + (matrix[2] * matrix[3] * matrix[7])) -
		((matrix[2] * matrix[4] * matrix[6]) + (matrix[1] * matrix[8] * matrix[3]) + (matrix[0] * matrix[7] * matrix[5]));
	return res;
}

float Norm(sf::Vector3f vec)
{
	return std::sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}
