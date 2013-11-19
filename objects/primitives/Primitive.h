#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"

class Primitive {
	private:
		Point position;
		Material material;

	public:
		virtual float getIntersection(Ray*) const = 0;
		virtual Vector getNormal(Point*) const = 0;
};
