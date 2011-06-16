#include "primitives/baseobject.cpp"
#include "primitives/triangle.cpp"
#include "primitives/quadrilateral.cpp"
#include "primitives/plane.cpp"
#include "primitives/sphere.cpp"

#include "structures/scene.cpp"

Scene scene = Scene();

void InitScene() {
  Quadrilateral* top = new Quadrilateral();
  top->point1 = Point(-1, 1, 1);
  top->point2 = Point(1, 1, 1);
  top->point3 = Point(1, -1, 1);
  top->point4 = Point(-1, -1, 1);
  top->normal = Vector(0, 0, 1);
  top->diffuse = Color(1, 0.85, 0.63);
  top->emittance = 1.6;
  scene.addObject(top);

  Quadrilateral* back = new Quadrilateral();
  back->point1 = Point(-1, 1, -1);
  back->point2 = Point(1, 1, -1);
  back->point3 = Point(1, 1, 1);
  back->point4 = Point(-1, 1, 1);
  back->normal = Vector(0, 1, 0);
  back->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(back);

  Quadrilateral* bottom = new Quadrilateral();
  bottom->point1 = Point(-1, -1, -1);
  bottom->point2 = Point(1, -1, -1);
  bottom->point3 = Point(1, 1, -1);
  bottom->point4 = Point(-1, 1, -1);
  bottom->normal = Vector(0, 0, -1);
  bottom->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(bottom);

  Quadrilateral* left = new Quadrilateral();  
  left->point1 = Point(-1, -1, 1);
  left->point2 = Point(-1, 1, 1);
  left->point3 = Point(-1, 1, -1);
  left->point4 = Point(-1, -1, -1);
  left->normal = Vector(-1, 0, 0);
  left->diffuse = Color(0.75, 0.25, 0.25);
  scene.addObject(left);

  Quadrilateral* right = new Quadrilateral();
  right->point1 = Point(1, -1, 1);
  right->point2 = Point(1, 1, 1);
  right->point3 = Point(1, 1, -1);
  right->point4 = Point(1, -1, -1);
  right->normal = Vector(1, 0, 0);
  right->diffuse = Color(0.25, 0.25, 0.75);
  scene.addObject(right);
/*
  Quadrilateral* light = new Quadrilateral();
  light->point1 = Point(-0.4, -0.4, 0.999999);
  light->point2 = Point(0.4, -0.4, 0.999999);
  light->point3 = Point(0.4, 0.4, 0.999999);
  light->point4 = Point(-0.4, 0.4, 0.999999);
  light->normal = Vector(0, 0, 1);
  light->diffuse = Color(1, 0.85, 0.43);
  light->emittance = 20;
  scene.addObject(light);
*/
  Sphere* sphere1 = new Sphere();
  sphere1->position = Point(-0.5, -0.5, -0.5);
  sphere1->radius = 0.5;
  sphere1->diffuse = Color(1, 1, 1);
  sphere1->reflectionType = DIFFUSE;
  scene.addObject(sphere1);
  
  Sphere* sphere2 = new Sphere();
  sphere2->position = Point(0.5, 0.5, -0.5);
  sphere2->radius = 0.5;
  sphere2->diffuse = Color(1, 1, 1);
  sphere2->reflectionType = DIFFUSE;
  scene.addObject(sphere2);
  
  Camera camera = Camera();
  camera.position = Point(0, -4.995, 0);
  camera.setFocus(Point(0, 0, -1));
  camera.setSize(0.5, 0.5);
  camera.offset = 1;
  camera.setPixelDensity(300);
  scene.setCamera(camera);
  
  CellImage* image = new CellImage();
  image->setSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
  scene.setImage(image);
}
