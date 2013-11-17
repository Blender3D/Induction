#pragma once

#include "BoundingBox.h"
#include "Primitive.h"
#include "Ray.h"
#include "Vector.h"

class Object {
	public:
		void addPrimitive(Primitive*);

	public:
		float getIntersection(Ray*) const;
		Vector getNormal(Point*) const;
		Point getLightSample() const;
		float getSurfaceArea() const;
		float getVolume() const;

		BoundingBox* getBoundingBox() const;

	private:
		void createBoundingBox();

	private:
		Point position;
		Material material;

		vector<Primitive*> objects;
		BoundingBox boundingBox;
};
