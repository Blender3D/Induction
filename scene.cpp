#include "primitives/primitive.cpp"
#include "primitives/triangle.cpp"
#include "primitives/quadrilateral.cpp"
#include "primitives/plane.cpp"
#include "primitives/sphere.cpp"
#include "primitives/object.cpp"


#include "structures/scene.cpp"
#include "structures/camera.h"

Scene scene = Scene();

void InitScene() {
  Object* topObject = new Object();
  Quadrilateral* top = new Quadrilateral();
  top->point1 = Point(-1, 1, 1);
  top->point2 = Point(1, 1, 1);
  top->point3 = Point(1, -1, 1);
  top->point4 = Point(-1, -1, 1);
  top->normal = Vector(0, 0, 1);
  
  topObject->material.reflectance = 1;
  topObject->material.diffuse = ColorRGB(1, 1, 1);
  
  topObject->addPrimitive(top);
  scene.addObject(topObject);
  
  
  Object* bottomObject = new Object();
  Quadrilateral* bottom = new Quadrilateral();
  bottom->point1 = Point(-1, 1, -1);
  bottom->point2 = Point(1, 1, -1);
  bottom->point3 = Point(1, -1, -1);
  bottom->point4 = Point(-1, -1, -1);
  bottom->normal = Vector(0, 0, -1);
  
  bottomObject->material.reflectance = 1;
  bottomObject->material.diffuse = ColorRGB(0.76, 0.75, 0.75);
  
  bottomObject->addPrimitive(bottom);
  scene.addObject(bottomObject);

  
  Object* leftObject = new Object();
  Quadrilateral* left = new Quadrilateral();
  left->point1 = Point(-1, 1, 1);
  left->point2 = Point(-1, -1, 1);
  left->point3 = Point(-1, -1, -1);
  left->point4 = Point(-1, 1, -1);
  left->normal = Vector(-1, 0, 0);
  
  leftObject->material.reflectance = 1;
  leftObject->material.diffuse = ColorRGB(0.63, 0.06, 0.04);
  
  leftObject->addPrimitive(left);
  scene.addObject(leftObject);

  
  Object* rightObject = new Object();
  Quadrilateral* right = new Quadrilateral();
  right->point1 = Point(1, 1, 1);
  right->point2 = Point(1, -1, 1);
  right->point3 = Point(1, -1, -1);
  right->point4 = Point(1, 1, -1);
  right->normal = Vector(1, 0, 0);
  
  rightObject->material.reflectance = 1;
  rightObject->material.diffuse = ColorRGB(0.15, 0.48, 0.09);
  
  rightObject->addPrimitive(right);
  scene.addObject(rightObject);

  
  Object* backObject = new Object();
  Quadrilateral* back = new Quadrilateral();
  back->point1 = Point(-1, 1, -1);
  back->point2 = Point(1, 1, -1);
  back->point3 = Point(1, 1, 1);
  back->point4 = Point(-1, 1, 1);
  back->normal = Vector(0, 1, 0);
  
  backObject->material.reflectance = 1;
  backObject->material.diffuse = ColorRGB(0.76, 0.75, 0.75);
  
  backObject->addPrimitive(back);
  scene.addObject(backObject);
  
  
  Object* sphereObject = new Object();
  Sphere* sphere = new Sphere();
  sphere->radius = 0.5;
  sphere->position = Point(0, 0, -0.5);
  
  sphereObject->material.reflectance = 1;
  sphereObject->material.diffuse = ColorRGB(1, 1, 1);
  
  sphereObject->addPrimitive(sphere);
  scene.addObject(sphereObject);


  Object* lightObject = new Object();
  Quadrilateral* light = new Quadrilateral();
  light->point1 = Point(-0.4, 0.4, 0.999);
  light->point2 = Point(0.4, 0.4, 0.999);
  light->point3 = Point(0.4, -0.4, 0.999);
  light->point4 = Point(-0.4, -0.4, 0.999);
  light->normal = Vector(0, 0, 1);
  
  lightObject->material.emittance = 15;
  //lightObject->material.diffuse = ColorRGB(1, 0.85, 0.43);
  lightObject->material.diffuse = ColorRGB(1.0, 0.97, 0.88);
  
  lightObject->addPrimitive(light);
  scene.addObject(lightObject);


  Object* obstructionObject = new Object();
  Quadrilateral* obstruction = new Quadrilateral();
  obstruction->point1 = Point(-0.6, 0.6, 0.6);
  obstruction->point2 = Point(0.6, 0.6, 0.6);
  obstruction->point3 = Point(0.6, -0.6, 0.6);
  obstruction->point4 = Point(-0.6, -0.6, 0.6);
  obstruction->normal = Vector(0, 0, 1);
  
  obstructionObject->material.reflectance = 1;
  obstructionObject->material.diffuse = ColorRGB(1, 1, 1);
  
  obstructionObject->addPrimitive(obstruction);
  scene.addObject(obstructionObject);


  Camera camera = Camera();
  camera.position = Point(0, -4.995, 0);
  camera.setFocus(Point(0, 0, -1));
  camera.setSize(0.5, 0.5);
  camera.offset = 1;
  camera.setPixelDensity(500);
  scene.setCamera(camera);

  
  CellImage* image = new CellImage();
  image->setSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
  scene.setImage(image);
}
