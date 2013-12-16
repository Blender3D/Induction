#pragma once

#include "objects/Ray.h"

#include "objects/Vector.h"
#include "objects/Point.h"

class Ray {
	public:
		Ray();
		Ray(const Point&, const Vector&);
	
	public:
		Point position(float time);

	public:
		inline bool operator==(const Ray&);

	public:
		Point origin;
		Vector direction;
};
