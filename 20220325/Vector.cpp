#include <iostream>
#include <math.h>
#include <vector>

typedef float real; 

struct Vector
{
	real x;
	real y;
	real z;
};

Vector cross_product(Vector a, Vector b);
float dot_product(Vector a, Vector b);
float magnitude(Vector a, Vector b);

int main(void)
{
	Vector v1, v2, v3;

	v1.x = 8, v1.y = 1, v1.z = 3;
	v2.x = 2, v2.y = 9, v2.z = 6;
	
	v3 = cross_product(v1, v2);

	std::cout <<  "crrss_x = " << v3.x << std::endl << "cross_y = " << v3.y << std::endl <<  "cross_z = " << v3.z << std::endl;
	std::cout << "magnitude = " << magnitude(v1, v2) << std::endl;
	std::cout << "dot = " << dot_product(v1, v2) << std::endl;


	return 0;
}

Vector cross_product(Vector a, Vector b)
{
	Vector vt;

	vt.x = a.y * b.z - a.z * b.y;

	vt.y = a.z * b.x - a.x * b.z;

	vt.z = a.x * b.y - a.y * b.x;

	return vt;
}

float dot_product(Vector a, Vector b)
{
	return a.x * b.x + a.y + b.y + a.z * b.z;
}

float magnitude(Vector a, Vector b)
{
	return sqrtf(a.x * b.x + a.y * b.y + a.z * b.z);
}
