#pragma once

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"
#include "primitives/Primitive.h"

class Sphere: public Primitive {
	public:
		Sphere();
		Sphere(float);

	public:
		virtual bool intersects(Ray*) const;
		virtual float getIntersection(Ray*) const;
		virtual Vector getNormal(Point*) const;

	public:
		void setRadius(float);
		float getRadius() const;

	public:
		float radius;
};
