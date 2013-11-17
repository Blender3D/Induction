#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

class Sphere: public Primitive {
	public:
		Sphere();
		Sphere(float);
		~Sphere();

	public:
		float getIntersection(Ray*) const;
		Vector getNormal(Point*) const;
		Point getLightSample() const;
		float getSurfaceArea() const;
		float getVolume() const;

	public:
		void createBoundingBox();
		void setRadius(float);

	public:
		float getRadius() const;

	private:
		float radius;
		BoundingBox boundingBox;
};
