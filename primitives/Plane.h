#include "Primitive.h"
#include "Vector.h"

#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

class Plane: public Primitive {
	public:
		Plane();
		Plane(Vector);
		~Plane();

	public:
		float getIntersection(Ray*) const;
		Vector getNormal(Point*) const;
		Point getLightSample() const;
		float getSurfaceArea() const;
		float getVolume() const;

	public:
		void createBoundingBox();
		void setNormal(Vector);

	private:
		Vector normal;
		const int sample_radius = 1000;
		const BoundingBox boundingBox(
			Point(-INFINITY, -INFINITY, -INFINITY),
			Point(INFINITY, INFINITY, INFINITY)
		);
};
