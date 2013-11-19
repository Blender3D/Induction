#pragma once

#include "Point.h"
#include <iostream>

class Vector {
	public:
		float x, y, z;

		Vector();
		Vector(Point&);
		Vector(float);
		Vector(float, float);
		Vector(float, float, float);

		Vector operator+(Vector&);
		Point operator+(Point&);
		Vector operator-(Vector&);
		Point operator-(Point&);

		Vector operator*(float);
		Vector operator/(float);

		bool operator==(Vector&);
		bool operator!=(Vector&);

		float operator[](int index);

		float length();
		Vector norm();

		float dot(Vector);
		Vector cross(Vector);

		friend std::ostream& operator<<(std::ostream&, Vector&);
};
