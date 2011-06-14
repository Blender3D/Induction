#include "primitives/baseobject.cpp"
#include "primitives/triangle.cpp"
#include "primitives/quadrilateral.cpp"
#include "primitives/plane.cpp"
#include "primitives/sphere.cpp"

#include "structures/scene.cpp"

Scene scene = Scene();

void InitScene() {
  Quadrilateral* topPlane = new Quadrilateral();
  topPlane->point1 = Point(-1, 1, 1);
  topPlane->point2 = Point(1, 1, 1);
  topPlane->point3 = Point(1, -1, 1);
  topPlane->point4 = Point(-1, -1, 1);
  topPlane->normal = Vector(0, 0, 1);
  topPlane->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(topPlane);

  Quadrilateral* backPlane = new Quadrilateral();
  backPlane->point1 = Point(-1, 1, -1);
  backPlane->point2 = Point(1, 1, -1);
  backPlane->point3 = Point(1, 1, 1);
  backPlane->point4 = Point(-1, 1, 1);
  backPlane->normal = Vector(0, 1, 0);
  backPlane->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(backPlane);

  Quadrilateral* bottomPlane = new Quadrilateral();
  bottomPlane->point1 = Point(-1, -1, -1);
  bottomPlane->point2 = Point(1, -1, -1);
  bottomPlane->point3 = Point(1, 1, -1);
  bottomPlane->point4 = Point(-1, 1, -1);
  bottomPlane->normal = Vector(0, 0, -1);
  bottomPlane->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(bottomPlane);

  Quadrilateral* leftPlane = new Quadrilateral();  
  leftPlane->point1 = Point(-1, -1, 1);
  leftPlane->point2 = Point(-1, 1, 1);
  leftPlane->point3 = Point(-1, 1, -1);
  leftPlane->point4 = Point(-1, -1, -1);
  leftPlane->normal = Vector(-1, 0, 0);
  leftPlane->diffuse = Color(0.75, 0.25, 0.25);
  scene.addObject(leftPlane);

  Quadrilateral* rightPlane = new Quadrilateral();
  rightPlane->point1 = Point(1, -1, 1);
  rightPlane->point2 = Point(1, 1, 1);
  rightPlane->point3 = Point(1, 1, -1);
  rightPlane->point4 = Point(1, -1, -1);
  rightPlane->normal = Vector(1, 0, 0);
  rightPlane->diffuse = Color(0.25, 0.25, 0.75);
  scene.addObject(rightPlane);

  Quadrilateral* lightPlane = new Quadrilateral();
  lightPlane->point1 = Point(-0.2, -0.2, 0.999999);
  lightPlane->point2 = Point(0.2, -0.2, 0.999999);
  lightPlane->point3 = Point(0.2, 0.2, 0.999999);
  lightPlane->point4 = Point(-0.2, 0.2, 0.999999);
  lightPlane->normal = Vector(0, 0, 1);
  lightPlane->diffuse = Color(1, 0.85, 0.43);
  lightPlane->emittance = 100;
  scene.addObject(lightPlane);

  Sphere* sphere1 = new Sphere();
  sphere1->position = Point(0, 0, -0.5);
  sphere1->radius = 0.5;
  sphere1->diffuse = Color(1, 1, 1);
  sphere1->reflectionType = DIFFUSE;
  sphere1->IOR = 1.53;
  scene.addObject(sphere1);
  
  Camera camera = Camera();
  camera.position = Point(0, -4.995, 0);
  camera.setFocus(Point(0, 0, -1));
  camera.setSize(0.5, 0.5);
  camera.offset = 1;
  camera.setPixelDensity(600);
  scene.setCamera(camera);
  
  CellImage* image = new CellImage();
  image->setSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
  scene.setImage(image);
}
