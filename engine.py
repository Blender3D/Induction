#!/usr/bin/env python

from PyQt4 import QtCore, QtGui
from numpy import *
import random, sys, time
from xml.dom.minidom import parse

epsilon = 0.00001

class Vector:
  def __init__(self, x = 0.0, y = 0.0, z = 0.0):
    self.x = x
    self.y = y
    self.z = z
  
  def __abs__(self):
    return sqrt(self.x**2 + self.y**2 + self.z**2)
  
  def __eq__(self, other):
    return self.x == other.x and self.y == other.y and self.z == other.z
  
  def __ne__(self, other):
    return self.x != other.x or self.y != other.y or self.z != other.z
  
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
    return self.__mul__(1.0 / other)
  
  def __neg__(self):
    return Vector(-self.x, -self.y, -self.z)
  
  def angle(self, other):
    return arccos(self.norm().dot(other.norm()))
  
  def norm(self):
    return self * (1.0 / abs(self))
  
  def dot(self, other):
    return self.x * other.x + self.y * other.y + self.z * other.z
  
  def cross(self, other):
    return Vector(self.y * other.z - self.z * other.y, self.z * other.x - self.x * other.z, self.x * other.y - self.y * other.x)
  
  def point(self):
    return Point(self.x, self.y, self.z)
  
  def vector(self):
    return self



class Point(Vector):  pass
class Color(Vector):  pass



class Ray:
  def __init__(self, origin = Point(), direction = Vector()):
    self.origin = origin
    self.direction = direction.norm()
  
  def position(self, time):
    return (self.origin + self.direction * time).point()
  
  def vector(self):
    return Vector(self.direction.x, self.direction.y, self.direction.z)
  
  def __str__(self):
    return '<<{0}, {1}, {2}>, <{3}, {4}, {5}>>'.format(self.origin.x, self.origin.y, self.origin.z, self.direction.x, self.direction.y, self.direction.z)



class CellImage:
  def __init__(self, width, height):
    self.width = width
    self.height = height
    self.image = [[Color() for w in range(width)] for h in range(height)]
  
  def getPixel(self, x, y):
    return self.image[x][y]
  
  def setPixel(self, x, y, color):
    self.image[x][y] = color
  
  def toQImage(self):
    canvas = QtGui.QImage(self.width, self.height, QtGui.QImage.Format_RGB32)
    
    for x in range(self.width):
      for y in range(self.height):
        pixel = Clamp(self.image[x][y])
        
        canvas.setPixel(x, y, QtGui.qRgb(pixel.x * 255, pixel.y * 255, pixel.z * 255))
    
    return canvas


class FocalPlane:
  def __init__(self, width, height, offset, pixelDensity):
    self.pixelDensity = float(pixelDensity)
    self.offset = float(offset)
    self.width = float(width)
    self.height = float(height)
    self.canvasWidth = int(self.width * self.pixelDensity)
    self.canvasHeight = int(self.height * self.pixelDensity)



class Camera:
  def __init__(self, position, direction, focalplane):
    self.pos = position
    self.dir = direction
    self.focalplane = focalplane
  
  def castRay(self, x, y):
    return Ray(self.pos, (Point(self.pos.x - self.focalplane.width / 2.0, self.pos.y + self.focalplane.offset, self.pos.z - self.focalplane.height / 2.0) + self.focalplane.width * x + self.focalplane.height * y - self.pos).norm())


class Sphere:
  def __init__(self, position = Point(0, 0, 0), radius = 1):
    self.pos = position
    self.radius = float(radius)
    self.diffuse = Color()
    self.emittance = 0
  
  def intersection(self, ray):
    distance = (ray.origin - self.pos).vector()
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

  if v2.dot(v) < 0.0:
    return -v2
  else:
    return v2



def Trace(ray, scene, n):
  if n > 10:# or random.uniform(0, 1) > 0.5:  # Russian Roulette
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
  
  normal = hit.normal(point)
  direction = RandomNormalInHemisphere(normal)
  
  newray = Ray(point, direction)
  
  return Trace(newray, scene, n + 1) * hit.diffuse + Color(hit.emittance, hit.emittance, hit.emittance)



class Scene:
  def __init__(self):
    self.objects = []
  
  def addObject(self, object):
    self.objects.append(object)
  
  def addCamera(self, object):
    self.camera = object
    
  def save(self, filename):
    return self.image.save(filename)
  
  def load(self, filename):
    document = parse(filename)
    
    camera = document.getElementsByTagName('camera')[0]
    
    self.camera = Camera(Point(camera.getElementsByTagName('position')[0].getAttribute('x'), 
                               camera.getElementsByTagName('position')[0].getAttribute('y'), 
                               camera.getElementsByTagName('position')[0].getAttribute('z')), 
                         Vector(camera.getElementsByTagName('direction')[0].getAttribute('x'), 
                                camera.getElementsByTagName('direction')[0].getAttribute('y'), 
                                camera.getElementsByTagName('direction')[0].getAttribute('z')), 
                         FocalPlane(camera.getElementsByTagName('focalplane')[0].getAttribute('width'), 
                                    camera.getElementsByTagName('focalplane')[0].getAttribute('height'), 
                                    camera.getElementsByTagName('focalplane')[0].getAttribute('offset'), 
                                    camera.getElementsByTagName('focalplane')[0].getAttribute('pixeldensity'))) 
    
    for object in document.getElementsByTagName('objects')[0].childNodes:
      try:
        if object.tagName == 'sphere':
          sphere = Sphere()
          sphere.radius = float(eval(object.getAttribute('radius')))
          sphere.pos = Point(eval(object.getElementsByTagName('position')[0].getAttribute('x')), 
                             eval(object.getElementsByTagName('position')[0].getAttribute('y')), 
                             eval(object.getElementsByTagName('position')[0].getAttribute('z')))
          sphere.emittance = float(eval(object.getElementsByTagName('material')[0].getAttribute('emittance')))
          sphere.reflectance = float(eval(object.getElementsByTagName('material')[0].getAttribute('reflectance')))
          sphere.diffuse = Color(eval(object.getElementsByTagName('material')[0].getElementsByTagName('diffuse')[0].getAttribute('r')), 
                                 eval(object.getElementsByTagName('material')[0].getElementsByTagName('diffuse')[0].getAttribute('g')), 
                                 eval(object.getElementsByTagName('material')[0].getElementsByTagName('diffuse')[0].getAttribute('b')))
          self.objects.append(sphere)
      except AttributeError as error:
        pass
    
    return self
