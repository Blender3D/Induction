#include "Vector.h"
#include "Point.h"

#include <cmath>

Vector::Vector() : x(0), y(0), z(0) {}
Vector::Vector(Point &point): x(point.x), y(point.y), z(point.z) {}
Vector::Vector(float k) : x(k), y(k), z(k) {}
Vector::Vector(float x, float y) : x(x), y(y), z(0) {}
Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector Vector::operator+(Vector &other) {
	return Vector(x + other.x, y + other.y, z + other.z);
}

Point Vector::operator+(Point &point) {
	return Point(x + point.x, y + point.y, z + point.z);
}

Point Vector::operator-(Point &point) {
	return Point(x - point.x, y - point.y, z - point.z);
}

Vector Vector::operator-(Vector &other) {
	return Vector(other.x - x, other.y - y, other.z - z);
}

Vector Vector::operator*(float k) {
	return Vector(x * k, y * k, z * k);
}

Vector Vector::operator/(float k) {
	assert(k != 0);
	return Vector(x / k, y / k, z / k);
}

bool Vector::operator==(Vector &other) {
	return ((x == other.x) && (y == other.y) && (z == other.z));
}

bool Vector::operator!=(Vector &other) {
	return ((x != other.x) || (y != other.y) || (z != other.z));
}

ostream& operator<<(ostream& stream, Vector &other) {
	stream << "Point(" << other.x << ", " << other.y << ", " << other.z << ")";

	return stream;
}

float Vector::operator[](int index) {
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

float Vector::length() {
	return sqrt(x*x + y*y + z*z);
}

Vector Vector::norm() {
	float len = length();
	assert(len > 0);

	return *this / len;
}

float Vector::dot(Vector &other) {
	return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(Vector &other) {
	return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}
