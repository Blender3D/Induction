#include "primitives/primitive.cpp"
#include "primitives/triangle.cpp"
#include "primitives/quadrilateral.cpp"
#include "primitives/plane.cpp"
#include "primitives/sphere.cpp"
#include "primitives/object.cpp"

#include "structures/scene.cpp"

Scene scene = Scene();

void InitScene() {
  Object* topObject = new Object();
  Quadrilateral* top = new Quadrilateral();
  top->point1 = Point(-1, 1, 1);
  top->point2 = Point(1, 1, 1);
  top->point3 = Point(1, -1, 1);
  top->point4 = Point(-1, -1, 1);
  top->normal = Vector(0, 0, 1);
  
  topObject->emittance = 10;
  topObject->diffuse = Color(1, 1, 1);
  
  topObject->addPrimitive(top);
  scene.addObject(topObject);
  
  Object* bottomObject = new Object();
  Quadrilateral* bottom = new Quadrilateral();
  bottom->point1 = Point(-1, 1, -1);
  bottom->point2 = Point(1, 1, -1);
  bottom->point3 = Point(1, -1, -1);
  bottom->point4 = Point(-1, -1, -1);
  bottom->normal = Vector(0, 0, -1);
  
  bottomObject->diffuse = Color(0.75, 0.75, 0.75);
  bottomObject->addPrimitive(bottom);
  scene.addObject(bottomObject);
  
  Object* leftObject = new Object();
  Quadrilateral* left = new Quadrilateral();
  left->point1 = Point(-1, 1, 1);
  left->point2 = Point(-1, -1, 1);
  left->point3 = Point(-1, -1, -1);
  left->point4 = Point(-1, 1, -1);
  left->normal = Vector(-1, 0, 0);

  leftObject->diffuse = Color(1, 0.25, 0.25);
  leftObject->addPrimitive(left);
  scene.addObject(leftObject);
  
  Object* rightObject = new Object();
  Quadrilateral* right = new Quadrilateral();
  right->point1 = Point(1, 1, 1);
  right->point2 = Point(1, -1, 1);
  right->point3 = Point(1, -1, -1);
  right->point4 = Point(1, 1, -1);
  right->normal = Vector(1, 0, 0);

  rightObject->diffuse = Color(0.25, 0.25, 1);
  rightObject->addPrimitive(right);
  scene.addObject(rightObject);
  
  Object* backObject = new Object();
  Quadrilateral* back = new Quadrilateral();
  back->point1 = Point(-1, 1, -1);
  back->point2 = Point(1, 1, -1);
  back->point3 = Point(1, 1, 1);
  back->point4 = Point(-1, 1, 1);
  back->normal = Vector(0, 1, 0);

  backObject->diffuse = Color(0.75, 0.75, 0.75);
  backObject->addPrimitive(back);
  scene.addObject(backObject);
  
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
