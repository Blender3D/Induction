#!/usr/bin/env python

import Image, ImageDraw

try:
  from PyQt4 import QtCore, QtGui
except:
  pass

from numpy import *
import random, sys, time, argparse

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
    return self * (1.0 / abs(self))
  
  def dot(self, other):
    return self.x * other.x + self.y * other.y + self.z * other.z



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
    self.image = [[Color(0, 0, 0) for w in range(width)] for h in range(height)]
  
  def getPixel(self, x, y):
    return self.image[x][y]
  
  def setPixel(self, x, y, color):
    self.image[x][y] = color
  
  def toPILImage(self, samples):
    samples = float(samples)
    image = Image.new('RGB', [self.width, self.height])
    canvas = ImageDraw.Draw(image)
    
    for x in range(self.width):
      for y in range(self.height):
        canvas.point([x, y], fill = Clamp(self.image[x][y] / float(samples)).list())
        
    del canvas
    return image
  
  def toQImage(self, samples):
    canvas = QtGui.QImage(self.width, self.height, QtGui.QImage.Format_RGB32)
    
    for x in range(self.width):
      for y in range(self.height):
        pixel = Clamp(self.image[x][y] / float(samples))
        
        canvas.setPixel(x, y, QtGui.qRgb(pixel.x * 255, pixel.y * 255, pixel.z * 255))
    
    return canvas


class ViewPlane:
  def __init__(self, width, height, offset, pixelDensity):
    self.pixelDensity = float(pixelDensity)
    self.offset = float(offset)
    self.width = float(width)
    self.height = float(height)
    self.canvasWidth = int(self.width * self.pixelDensity)
    self.canvasHeight = int(self.height * self.pixelDensity)



class Camera:
  def __init__(self, position, direction, viewplane):
    self.pos = position
    self.dir = direction
    self.viewplane = viewplane
    self.cX = viewplane.width / viewplane.canvasWidth
    self.cY = viewplane.height / viewplane.canvasHeight
  
  def CastRay(self, x, y):
    return Ray(self.pos, Point(x * self.cX - self.viewplane.width / 2.0, 1, y * self.cY - self.viewplane.height / 2.0))



class Sphere:
  def __init__(self, position = Point(0, 0, 0), radius = 1):
    self.pos = position
    self.radius = float(radius)
    self.diffuse = Color()
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
  if n > 2 or random.uniform(0, 1) < roulette:
    return Color(0.0, 0.0, 0.0)
  
  result = 1000000.0
  hit = False
  
  for object in scene.objects:
    test = object.intersection(ray)
    
    if test and test < result:
      result = test
      hit = object
  
  if not hit:
    return Color(0.0, 0.0, 0.0)
  
  point = ray.position(result)
  
  return Trace(Ray(point, RandomNormalInHemisphere(hit.normal(point)).norm()), scene, roulette, n + 1) * hit.diffuse + Color(hit.emittance, hit.emittance, hit.emittance)



class Scene:
  def __init__(self):
    self.objects = []
    self.camera = None


if __name__ == '__main__':
  
  try:
    samples = int(sys.argv[1])
  except:
    samples = 200
  
  try:
    roulette = float(sys.argv[2])
  except:
    roulette = 0.1
  
  try:
    filename = sys.argv[3]
  except:
    filename = 'image.png'
  
  begin = time.time()
  
  scene = Scene()
  sphere = Sphere(Point(1, 0, 0), 1)
  sphere.diffuse = Color(1.0, 1.0, 1.0)
  
  scene.camera = Camera(Point(0, -5, 0), Vector(0, 1, 0), ViewPlane(0.5, 0.5, 1, 800))
  scene.objects.append(sphere)
  
  light = Sphere(Point(-1, 0, 0), 1)
  light.emittance = 0.9
  light.diffuse = Color(1.0, 1.0, 1.0)
  scene.objects.append(light)
  
  image = CellImage(scene.camera.viewplane.canvasWidth, scene.camera.viewplane.canvasHeight)
  
  print ' * Using [{0}] samples/pixel...'.format(samples)
  print ' * Using [{0}] as Russian Roulette constant...'.format(roulette)
  
  for y in range(0, scene.camera.viewplane.canvasHeight):
    sys.stdout.write(' * Rendering: [{0}%]... \r'.format(1.0 + 100.0 * float(y) / scene.camera.viewplane.canvasHeight)); sys.stdout.flush()
    
    for x in range(0, scene.camera.viewplane.canvasWidth):
      ray = scene.camera.CastRay(x, y)
      color = Color(0, 0, 0)
      
      for i in range(samples):  color += Trace(ray, scene, roulette)
      
      image.setPixel(x, y, color)
  
  print
  print ' * Saving image [{0}]...'.format(filename)
  image.toPILImage(samples).save(filename)
  print ' * Done [{0} seconds].'.format(time.time() - begin)
