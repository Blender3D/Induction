#pragma once

#include "Vector.h"
#include <iostream>

class Point {
	public:
		float x, y, z;

		Point();
		Point(Vector&);
		Point(float);
		Point(float, float);
		Point(float, float, float);

		Point operator+(Point&);
		Point operator+(Vector&);
		Vector operator-(Point&);

		Point operator*(float);
		Point operator/(float);

		bool operator==(Point&);
		bool operator!=(Point&);
		bool operator>(Point&);
		bool operator<(Point&);    

		float operator[](int index);

		float distanceFrom(Point&);

		friend std::ostream& operator<<(std::ostream&, Point&);
};
