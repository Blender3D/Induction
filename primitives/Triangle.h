#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

class Triangle: public Primitive {
	public:
		Triangle();
		Triangle(Point, Point, Point);
		~Triangle();

	public:
		float getIntersection(*Ray) const;
		Vector getNormal(*Point) const;
		Point getLightSample() const;
		float getSurfaceArea() const;
		float getVolume() const;

	public:
		void createBoundingBox();
		void setPoint1(Point);
		void setPoint2(Point);
		void setPoint3(Point);

	public:
		Point getPoint1(Point) const;
		Point getPoint2(Point) const;
		Point getPoint3(Point) const;

	private:
		Point point1, point2, point3;
		Vector normal;
		BoundingBox boundingBox;
};
