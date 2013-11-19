#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Primitive.h"

class Sphere: public Primitive {
	public:
		Sphere();
		Sphere(float);

	public:
		virtual float getIntersection(Ray*) const;
		virtual Vector getNormal(Point*) const;

	public:
		void setRadius(float);
		float getRadius() const;

	private:
		float radius;
};
