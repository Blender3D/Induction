#include <math.h>
#include <stdlib.h>

#include "lightpath.h"

using namespace std;

HitPoint::HitPoint() {
	normal = Vector();
	input = Vector();
	output = Vector();

	material = Material();
}

HitPoint::HitPoint(Vector _normal, Vector _input, Vector _output, Material _material) {
	normal = _normal;
	input = _input;
	output = _output;

	material = _material;
}

LightPath::LightPath() {}

void LightPath::addPoint(HitPoint point) {
	points.push_back(point);
}