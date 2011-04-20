#!/usr/bin/env python

from math import sqrt, isnan
import random, sys, time

epsilon = 0.00001

class Vector:
  def __init__(self, x = 0.0, y = 0.0, z = 0.0):
    self.x = x
    self.y = y
    self.z = z
  
  def __abs__(self):
    return sqrt(self.x**2 + self.y**2 + self.z**2)
  
  def list(self):
    return (int(self.x * 255), int(self.y * 255), int(self.z * 255))
  
  def __call__(self, x, y, z):
    return Vector(x, y, z)
  
  def __str__(self):
    return '<{0}, {1}, {2}>'.format(self.x, self.y, self.z)
  
  def __add__(self, other):
    if type(other) == type(self):
      return Vector(self.x + other.x, self.y + other.y, self.z + other.z)
    else:
      return Vector(self.x + other, self.y + other, self.z + other)
  
  def __sub__(self, other):
    return self.__add__(other * -1.0)
  
  def __mul__(self, other):
    if type(other) == type(self):
      return Vector(self.x * other.x, self.y * other.y, self.z * other.z)
    else:
      return Vector(self.x * other, self.y * other, self.z * other)
  
  def __div__(self, other):
    return self.__mul__(1.0 / float(other))
  
  def __neg__(self):
    return Vector(-self.x, -self.y, -self.z)
  
  def norm(self):
    if abs(self) != 0:
      return self * (1.0 / abs(self))
    else:
      return self
  
  def dot(self, other):
    return self.x * other.x + self.y * other.y + self.z * other.z
  
  def cross(self, other):
    return Vector(self.y * other.z - self.z * other.y, self.z * other.x - self.x * other.z, self.x * other.y - self.y * other.x)



class Point(Vector):  pass
class Color(Vector):  pass



class Ray:
  def __init__(self, origin = Point(), direction = Vector()):
    self.origin = origin
    self.direction = direction.norm()
  
  def position(self, time):
    return self.origin + self.direction * time


class CellImage:
  def __init__(self, width, height):
    self.width = width
    self.height = height
    self.image = [[Color(0, 0, 0) for h in range(height)] for w in range(width)]
  
  def getPixel(self, x, y):
    return self.image[x][y]
  
  def setPixel(self, x, y, color):
    self.image[x][y] = color
  
  def save(self, samples, filename):
    samples = float(samples)
    
    handle = open(filename, 'w')
    contents = 'P3\n{0} {1}\n255\n'.format(self.width, self.height)
    
    for y in range(self.height):
      for x in range(self.width):
        pixel = Clamp(self.image[x][self.height - 1 - y] / float(samples)).list()
        contents += '{0} {1} {2} '.format(pixel[0], pixel[1], pixel[2])
      contents += '\n'
    
    handle.write(contents)
    handle.close()
  


class ViewPlane:
  def __init__(self, width, height, offset, pixelDensity):
    self.pixelDensity = float(pixelDensity)
    self.offset = float(offset)
    self.width = float(width)
    self.height = float(height)
    self.canvasWidth = int(self.width * self.pixelDensity)
    self.canvasHeight = int(self.height * self.pixelDensity)



class Camera:
  def __init__(self, position, focus, viewplane):
    self.pos = position
    self.dir = (position - focus).norm()
    self.viewplane = viewplane
    self.cX = viewplane.width / viewplane.canvasWidth
    self.cY = viewplane.height / viewplane.canvasHeight
  
  def CastRay(self, x, y):
    return Ray(self.pos, Point(x * self.cX - self.viewplane.width / 2.0, 1, y * self.cY - self.viewplane.height / 2.0))



class Plane:
  def __init__(self, origin, point1, point2, normal = None):
    self.pos = origin
    self.point1 = point1
    self.point2 = point2
    
    if normal != None:
      self.normal = normal
    else:
      self.normal = (point1).cross(point2).norm()
    
    self.diffuse = Color(1, 1, 1)
    self.emittance = 0
  
  def intersection(self, ray):
    k = (ray.direction.dot(self.normal))
    
    if k != 0:
      t = (self.pos - ray.origin).dot(self.normal) / k
    else:
      return False
    
    if t < 0.0000001:
      return False
    
    point = ray.position(t)
    toPoint = point - self.pos
    
    test1 = toPoint.dot(self.point1)
    
    if test1 < 0 or test1 > abs(self.point1 - self.pos):
      return False
    
    test2 = toPoint.dot(self.point2)
    
    if test2 < 0 or test2 > abs(self.point2 - self.pos):
      return False
    
    return t

  def normal(self, position):
    return self.normal



class Sphere:
  def __init__(self, position = Point(0, 0, 0), radius = 1):
    self.pos = position
    self.radius = float(radius)
    self.diffuse = Color(0, 0, 0)
    self.emittance = 0
  
  def intersection(self, ray):
    distance = ray.origin - self.pos
    b = distance.dot(ray.direction)
    c = distance.dot(distance) - self.radius**2
    d = b*b - c
    
    if d > 0:
      return -b - sqrt(d)
    else:
      return False
  
  def normal(self, position):
    return (position - self.pos).norm()



def Clamp(color):
  if color.x > 1:  color.x = 1
  if color.y > 1:  color.y = 1
  if color.z > 1:  color.z = 1
  
  return color



def RandomNormalInHemisphere(v):
  v2 = Vector(random.uniform(-1, 1), random.uniform(-1, 1), random.uniform(-1, 1)).norm()

  while v2.dot(v2) > 1.0:
    v2 = Vector(random.uniform(-1, 1), random.uniform(-1, 1), random.uniform(-1, 1)).norm()
  
  return v2 * (v2.dot(v) < 0.0)



def Trace(ray, scene, roulette, n = 0):
  if n > 10 or random.uniform(0, 1) < roulette:
    return Color(0.0, 0.0, 0.0)
  
  result = 1000000.0
  hit = False
  
  for object in scene.objects:
    test = object.intersection(ray)
    
    if test and 0 < test < result:
      result = test
      hit = object
  
  if not hit:
    return Color(0.0, 0.0, 0.0)
  
  point = ray.position(result)
  
  try:
    normal = hit.normal(point)
  except:
    normal = hit.normal
  
  direction = RandomNormalInHemisphere(normal)
  ray = Ray(point, direction)
  
  return hit.diffuse * (Trace(ray, scene, roulette, n + 1) + hit.emittance)



def LoadArg(id, type, default):
  try:
    return (type)(sys.argv[id])
  except:
    return default



class Scene:
  def __init__(self):
    self.objects = []
    self.camera = None


if __name__ == '__main__':
  roulette  = LoadArg(1, float, 0.4)
  pass_save = LoadArg(2, int, 5)
  filename  = LoadArg(3, str, 'image.ppm')
  
  begin = time.time()
  scene = Scene()
  
  light = Plane(Point(-1, 1, 1), Point(2, 0, 0), Point(0, -2, 0), Vector(0, 0, -1))
  light.emittance = 20
  scene.objects.append(light)
  
  sphere = Sphere(Point(0, 0, -0.45), 0.25)
  sphere.diffuse = Color(0.25, 0.25, 0.75)
  scene.objects.append(sphere)
  
  back = Plane(Point(-1, 1, -1), Point(2, 0, 0), Point(0, 0, 2), Vector(0, 1, 0))
  back.diffuse = Color(0.75, 0.75, 0.75)
  scene.objects.append(back)
  
  bottom = Plane(Point(-1, 1, -1), Point(2, 0, 0), Point(0, -2, 0), Vector(0, 0, -1))
  bottom.diffuse = Color(0.75, 0.75, 0.75)
  scene.objects.append(bottom)
  
  left = Plane(Point(-1, 1, -1), Point(0, -2, 0), Point(0, 0, 2), Vector(-1, 0, 0))
  left.diffuse = Color(0.75, 0.25, 0.25)
  scene.objects.append(left)

  scene.camera = Camera(Point(0, -5.0, 0), Point(0, 0, 0), ViewPlane(0.8, 0.5, 1, 300))
  
  image = CellImage(scene.camera.viewplane.canvasWidth, scene.camera.viewplane.canvasHeight)
  
  print(' * Using continuous sampling...')
  print(' * Using [{0}] as Russian Roulette constant...'.format(roulette))
  print(' * Saving every [{0}] passes...'.format(pass_save))
  print('')
  
  i = 0
  
  while True:
    i += 1
    
    for y in range(0, scene.camera.viewplane.canvasHeight):
      sys.stdout.write(' * Rendering pass {0}: [{1}%]... \r'.format(i, int(0.5 + 100.0 * float(y) / scene.camera.viewplane.canvasHeight))); sys.stdout.flush()
      
      for x in range(0, scene.camera.viewplane.canvasWidth):
        image.setPixel(x, y, image.getPixel(x, y) + Trace(scene.camera.CastRay(x, y), scene, roulette))
  
    print('')
    
    if i % pass_save == 0:
      print(' * Saving image [{1}]...'.format(i, filename))
      print('')
      image.save(i, filename)
    
  print(' * Done [{0} seconds].'.format(time.time() - begin))
