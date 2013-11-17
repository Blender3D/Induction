#include "Object.h"
#include "BoundingBox.h"
#include "Primitive.h"
#include "Ray.h"
#include "Vector.h"

#include "random.h"

void Object::addPrimitive(Primitive *primitive) {
	objects.push_back(primitive);
}

BoundingBox Object::createBoundingBox() {
	Point minimum = Point(INFINITY);
	Point maximum = Point(-INFINITY);

	for (unsigned int i = 0; i < objects.size(); i++) {
		BoundingBox *box = objects[i]->getBoundingBox();

		if (box->corner1 < minimum) {
			minimum = box->corner1;
		}

		if (box->corner2 > maximum) {
			maximum = box->corner2;
		}
	}

	boundingBox.corner1 = minimum;
	boundingBox.corner2 = maximum;
}

float Object::getIntersection(Ray *ray) {
	if (!boundingBox->getIntersection(ray)) {
		return false;
	}

	int index = -1;
	float result = INFINITY;

	for (unsigned int i = 0; i < objects.size(); i++) {
		Primitive* target = objects[i];
		float test = target->getIntersection(ray);

		if ((test > 0.0) && (test < result)) {
			result = test;
			index = i;
		}
	}

	if (index == -1) {
		return false;
	}

	lastHit = objects[index];
	return result;
}

Vector Object::getNormal(Point position) {
	return lastHit->getNormal(position);
}

Point Object::getLightSample() {
	return objects[random_int(objects.size())]->getLightSample();
}
