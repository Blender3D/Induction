#pragma once

#include "Point.h"

#include <iostream>

class Vector {
	public:
		float x, y, z;

	public:
		Vector();
		Vector(Point&);
		Vector(float);
		Vector(float, float);
		Vector(float, float, float);

	public:
		Vector operator+(const Vector&);
		Point operator+(const Point&);
		Vector operator-(const Vector&);
		Point operator-(const Point&);

		Vector operator*(float);
		Vector operator/(float);

		bool operator==(const Vector&);
		bool operator!=(const Vector&);

		float operator[](int index);

	public:
		float length();
		Vector norm();

		float dot(const Vector&);
		Vector cross(const Vector&);

		friend std::ostream& operator<<(const std::ostream&, const Vector&);
};
