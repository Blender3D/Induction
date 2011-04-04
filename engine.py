#!/usr/bin/env python

from numpy import *
import random, sys, time
import Image, ImageDraw
from xml.dom.minidom import parse

epsilon = 0.00001

class Vector:
  def __init__(self, x = 0, y = 0, z = 0):
    self.x = float(x)
    self.y = float(y)
    self.z = float(z)
  
  def __abs__(self):
    return sqrt(self.x**2 + self.y**2 + self.z**2)
  
  def __eq__(self, other):
    return self.x == other.x and self.y == other.y and self.z == other.z
  
  def __ne__(self, other):
    return self.x != other.x or self.y != other.y or self.z != other.z
  
  def __str__(self):
    return '<{0}, {1}, {2}>'.format(self.x, self.y, self.z)
  
  def __add__(self, other):
    if self.__class__ == other.__class__:
      return Vector(self.x + other.x, self.y + other.y, self.z + other.z)
    else:
      return Point(self.x + other.x, self.y + other.y, self.z + other.z)
  
  def __sub__(self, other):
    if self.__class__ == other.__class__:
      return Vector(self.x - other.x, self.y - other.y, self.z - other.z)
    else:
      return Point(self.x - other.x, self.y - other.y, self.z - other.z)
  
  def __mul__(self, other):
    return Vector(self.x * other, self.y * other, self.z * other)
  
  def __div__(self, other):
    return Vector(self.x / other, self.y / other, self.z / other)
  
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



class Point:
  def __init__(self, x = 0, y = 0, z = 0):
    self.x = float(x)
    self.y = float(y)
    self.z = float(z)
  
  def __str__(self):
    return '({0}, {1}, {2})'.format(self.x, self.y, self.z)
  
  def __add__(self, other):
    return Vector(self.x + other.x, self.y + other.y, self.z + other.z)
  
  def __sub__(self, other):
    return Vector(self.x - other.x, self.y - other.y, self.z - other.z)
  
  def __mul__(self, other):
    return Point(self.x * other, self.y * other, self.z * other)
  
  def __neg__(self):
    return self.__mul__(-1)
  
  def __div__(self, other):
    return self.__div__(1.0 / other)
  
  def distance(self, other):
    return sqrt((self.x - other.x)**2 + (self.y - other.y)**2 + (self.z - other.z)**2)
  
  def vector(self):
    return Vector(self.x, self.y, self.z)



class Ray:
  def __init__(self, origin = Point(), direction = Vector()):
    self.origin = origin
    self.direction = direction.norm()
  
  def position(self, time):
    return self.origin + self.direction * time
  
  def vector(self):
    return Vector(self.direction.x, self.direction.y, self.direction.z)
  
  def __str__(self):
    return '<<{0}, {1}, {2}>, <{3}, {4}, {5}>>'.format(self.origin.x, self.origin.y, self.origin.z, self.direction.x, self.direction.y, self.direction.z)



class Color:
  def __init__(self, r = 0.0, g = 0.0, b = 0.0):
    self.r = float(r)
    self.g = float(g)
    self.b = float(b)
  
  def random(self):
    return Color(random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1))
  
  def list(self):
    return [self.r, self.g, self.b]
  
  def rgb(self):
    return 'rgb({0}, {1}, {2})'.format(self.r, self.g, self.b)
  
  def __str__(self):
    return 'rgb({0}, {1}, {2})'.format(self.r, self.g, self.b)
  
  def __add__(self, other):
    return Color(self.r + other.r, self.g + other.g, self.b + other.b)
  
  def __sub__(self, other):
    return Color(self.r - other.r, self.g - other.g, self.b - other.b)
  
  def __mul__(self, other):
    try:
      return Color(self.r * other.r, self.g * other.g, self.b * other.b)
    except AttributeError:
      return Color(self.r * other, self.g * other, self.b * other)



class FocalPlane:
  def __init__(self, width, height, offset, pixelDensity):
    self.pixelDensity = float(pixelDensity)
    self.offset = float(offset)
    self.width = float(width)
    self.height = float(height)
    self.canvasWidth = self.width * self.pixelDensity
    self.canvasHeight = self.height * self.pixelDensity



class Camera:
  def __init__(self, position, direction, focalplane):
    self.pos = position
    self.dir = direction
    self.focalplane = focalplane


class Object:
  def __init__(self, faces, color = Color(1, 1, 1)):
    self.faces = faces
    self.diffuse = color
    self.reflection = 0
    self.emittance = 0
  
  def triangulate(self):
    new = []
    
    for face in self.faces:
      if len(face) == 3:
        new.append(face)
      else:
        new.append([face[0], face[1], face[2]])
        new.append([face[2], face[0], face[1]])
    
    return Object(new, self.diffuse)
  
  def intersection(self, ray):
    output = True
    
    for triangle in self.triangulate().faces:
      pairs = sorted([[(triangle[2] - triangle[0]).angle(triangle[2] - triangle[1]), triangle[2]], [(triangle[1] - triangle[2]).angle(triangle[1] - triangle[0]), triangle[1]], [(triangle[0] - triangle[1]).angle(triangle[0] - triangle[2]), triangle[0]]], key = lambda pair: pair[0])
      triangle = [i[1] for i in pairs]
      
      u = triangle[1] - triangle[0]
      v = triangle[2] - triangle[0]
      n = u.cross(v)

      if n == Vector(0, 0, 0):  output = False

      w0 = ray.origin - triangle[0]
      a = -n.dot(w0)
      b = n.dot(ray.direction)

      if fabs(b) < epsilon:  output = False

      r = a / b
      if (r < 0):  output = False

      intersection = ray.origin + ray.direction * r

      uu = u.dot(u)
      uv = u.dot(v)
      vv = v.dot(v)
      w = intersection - triangle[0]
      wu = w.vector().dot(u)
      wv = w.vector().dot(v)
      D = uv * uv - uu * vv

      s = (uv * wv - vv * wu) / D
      t = (uv * wu - uu * wv) / D

      if s < 0 or s > 1:  output = False
      if t < 0 or (s + t) > 1:  output = False
      
      if output:
        return r
    
    return False


class Sphere(Object):
  def __init__(self, position = Point(0, 0, 0), radius = 1):
    self.pos = position
    self.radius = float(radius)
    self.diffuse = Color().random()
    self.emittance = 0
  
  def __str__(self):
    print self.pos
  
  def intersection(self, ray):
    cp = self.pos - ray.origin
    v = cp.dot(ray.direction)
    discriminant = self.radius**2  - cp.dot(cp) + v * v
    
    if discriminant < 0:
      return False
    elif v - sqrt(discriminant) < epsilon:
      return v - sqrt(discriminant)
    else:
      return v + sqrt(discriminant)
  
  def normal(self, position):
    return (self.pos + position).norm()



class Plane(Object):
  def __init__(self, position):
    self.pos = position
    self.emittance = 0
  
  def intersection(self, ray):
    d = (self.pos - ray.origin).dot(self.normal.norm()) / (ray.vector().dot(self.normal.norm()))
    
    if d > 0:
      return d
  
  def normal(self, position):
    return self.normal.norm()



def RandomDirectionInHemisphere(normal):
  n1 = random.uniform(0, 1)
  n2 = random.uniform(0, 1)
  theta = 2.0 * pi * n1
  phi = arccos(1.0 - n2)
  
  w = normal.norm()
  t = w.norm()
  
  if abs(t.x) <= abs(t.y) and abs(t.x) <= abs(t.z):
    t.x = 1.0
  elif abs(t.y) <= abs(t.x) and abs(t.y) <= abs(t.z):
    t.y = 1.0
  else:
    t.z = 1.0
  
  u = t.cross(w).norm()
  v = w.cross(u)
  direction = u * cos(theta) * sin(phi) + v * sin(theta) * sin(phi) + w * cos(phi)
  
  return direction.norm()



def TracePath2(ray, scene, depth):
  result = 1000000.0
  hit = False
  
  for object in scene.objects:
    test = object.intersection(ray)
    
    if test and test < result:
      result = test
      hit = object
  
  if not hit or depth > 5:
    return Color(0.0, 0.0, 0.0)
  
  if hit.emittance > 0:
    return hit.diffuse * hit.emittance
  
  newDir = RandomDirectionInHemisphere(hit.normal(ray.position(result)))
  newRay = Ray(ray.position(result), newDir)
  cos_omega = newDir.dot(hit.normal(ray.position(result)))
  
  BRDF = hit.reflectance * cos_omega
  
  return hit.diffuse * hit.emittance + (TracePath2(newRay, scene, depth + 1) * (BRDF * cos_omega))



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
          sphere.radius = float(object.getAttribute('radius'))
          sphere.pos = Point(object.getElementsByTagName('position')[0].getAttribute('x'), 
                             object.getElementsByTagName('position')[0].getAttribute('y'), 
                             object.getElementsByTagName('position')[0].getAttribute('z'))
          sphere.emittance = float(object.getElementsByTagName('material')[0].getAttribute('emittance'))
          sphere.reflectance = float(object.getElementsByTagName('material')[0].getAttribute('reflectance'))
          sphere.diffuse = Color(object.getElementsByTagName('material')[0].getElementsByTagName('diffuse')[0].getAttribute('r'), 
                                 object.getElementsByTagName('material')[0].getElementsByTagName('diffuse')[0].getAttribute('g'), 
                                 object.getElementsByTagName('material')[0].getElementsByTagName('diffuse')[0].getAttribute('b'))
          self.objects.append(sphere)
      except AttributeError:
        pass
    
    return self
