#pragma once

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"

#include "Material.h"

class Primitive {
	public:
		virtual bool intersects(Ray*) const = NULL;
		virtual float getIntersection(Ray*) const = NULL;
		virtual Vector getNormal(Point*) const = NULL;

	public:
		Point position;
		Material material;
};
