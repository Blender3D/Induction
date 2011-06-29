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
  top->emittance = 10;
  top->diffuse = Color(1, 0.85, 0.43);
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
  
  Sphere* sphere = new Sphere();
  sphere->position = Point(0, 0, -0.5);
  sphere->radius = 0.5;
  sphere->diffuse = Color(1, 1, 1);
  scene.addObject(sphere);
  
  Camera camera = Camera();
  camera.position = Point(0, -4.995, 0);
  camera.setFocus(Point(0, 0, -1));
  camera.setSize(0.5, 0.5);
  camera.offset = 1;
  camera.setPixelDensity(400);
  scene.setCamera(camera);
  
  CellImage* image = new CellImage();
  image->setSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
  scene.setImage(image);
}
