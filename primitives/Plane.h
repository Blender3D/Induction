#pragma once

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"
#include "primitives/Primitive.h"

class Plane: public Primitive {
	public:
		Plane();
		Plane(Vector);

	public:
		virtual bool intersects(Ray*) const;
		virtual float getIntersection(Ray*) const;
		virtual Vector getNormal(Point*) const;

	public:
		Vector normal;
};
