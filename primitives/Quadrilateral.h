#pragma once

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"
#include "primitives/Primitive.h"

class Quadrilateral: public Primitive {
	public:
		Quadrilateral();
		Quadrilateral(Point, Point, Point, Point);

	public:
		virtual bool intersects(Ray*) const;
		virtual float getIntersection(Ray*) const;
		virtual Vector getNormal(Point*) const;

	public:
		Point point1, point2, point3, point4;
		Vector normal;
};
