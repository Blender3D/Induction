#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Primitive.h"

#include "constants.h"

class Plane: public Primitive {
	public:
		Plane();
		Plane(Vector);

	public:
		virtual float getIntersection(Ray*) const;
		virtual Vector getNormal(Point*) const;

	public:
		void setNormal(Vector);

	private:
		Vector normal;
};
