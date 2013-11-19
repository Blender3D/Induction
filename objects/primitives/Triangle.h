#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Primitive.h"

class Triangle: public Primitive {
	public:
		Triangle();
		Triangle(Point, Point, Point);

	public:
		virtual float getIntersection(*Ray) const;
		virtual Vector getNormal(*Point) const;

	public:
		void setPoint1(Point);
		void setPoint2(Point);
		void setPoint3(Point);

		Point getPoint1(Point) const;
		Point getPoint2(Point) const;
		Point getPoint3(Point) const;

	private:
		Point point1, point2, point3;
		Vector normal;
};
