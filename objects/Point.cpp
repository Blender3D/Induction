#include "Point.h"

#include <iostream>
#include <cmath>

Point::Point() : x(0), y(0), z(0) {}
Point::Point(Point &point): x(point.x), y(point.y), z(point.z) {}
Point::Point(float k) : x(k), y(k), z(k) {}
Point::Point(float x, float y) : x(x), y(y), z(0) {}
Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point Point::operator+(Point &other) {
	return Point(x + other.x, y + other.y, z + other.z);
}

Vector Point::operator-(Point &other) {
	return Vector(x - other.x, y - other.y, z - other.z);
}

Point Point::operator*(float k) {
	return Point(x * k, y * k, z * k);
}

Point Point::operator/(float k) {
	assert(k != 0);
	return Point(x / k, y / k, z / k);
}

bool Point::operator==(Point &other) {
	return ((x == other.x) && (y == other.y) && (z == other.z));
}

bool Point::operator!=(Point &other) {
	return ((x != other.x) || (y != other.y) || (z != other.z));
}

bool Point::operator>(Point &other) {
	return ((x > other.x) && (y > other.y) && (z > other.z));
}

bool Point::operator<(Point &other) {
	return ((x < other.x) && (y < other.y) && (z < other.z));
}

float Point::distanceFrom(Point &other) {
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

float Point::operator[](int index) {
	if (index == 0) {
		return x;
	} else if (index == 1) {
		return y;
	} else if (index == 2) {
		return z;
	} else {
		return 0;
	}
}

std::ostream& operator<<(ostream &stream, Point &point) {
	stream << "Point(" << point.x << ", " << point.y << ", " << point.z << ")";
	return stream;
}
