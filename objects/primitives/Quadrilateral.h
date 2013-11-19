#pragma once

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Primitive.h"

class Quadrilateral: public Primitive {
	public:
		Quadrilateral();
		Quadrilateral(Point, Point, Point);

	public:
		virtual float getIntersection(Ray*) const;
		virtual Vector getNormal(Point*) const;

	public:
		void setPoint1(Point);
		void setPoint2(Point);
		void setPoint3(Point);
		void setPoint4(Point);

		Point getPoint1() const;
		Point getPoint2() const;
		Point getPoint3() const;
		Point getPoint4() const;

	private:
		Point point1, point2, point3, point4;
		Vector normal;
};
