#!/usr/bin/env python

from numpy import *
import random, sys, time
import Image, ImageDraw

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
    return acos(self.norm().dot(other.norm()))
  
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
  def __init__(self, origin, direction):
    self.origin = origin
    self.direction = direction.norm()
  
  def position(self, time):
    return self.origin + self.direction * time
  
  def vector(self):
    return Vector(self.direction.x, self.direction.y, self.direction.z)
  
  def __str__(self):
    return '<<{0}, {1}, {2}>, <{3}, {4}, {5}>>'.format(self.origin.x, self.origin.y, self.origin.z, self.direction.x, self.direction.y, self.direction.z)



class Color:
  def __init__(self, r = 0, g = 0, b = 0):
    self.r = r
    self.g = g
    self.b = b
  
  def random(self):
    return Color(random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1))
  
  def rgb(self):
    return 'rgb({0}, {1}, {2})'.format(self.r, self.g, self.b)
  
  def __str__(self):
    return 'rgb({0}, {1}, {2})'.format(self.r, self.g, self.b)
  
  def __add__(self, other):
    return Color(self.r + other.r, self.g + other.g, self.b + other.b)
  
  def __sub__(self, other):
    return Color(self.r - other.r, self.g - other.g, self.b - other.b)
  
  def __mul__(self, other):
    if self.__class__ == other.__class__:
      return Color(self.r * other.r, self.g * other.g, self.b * other.b)
    else:
      return Color(self.r * other, self.g * other, self.b * other)



class FocalPlane:
  def __init__(self, width, height, offset, canvasWidth, canvasHeight):
    self.offset = offset
    self.width = width
    self.height = height
    self.canvasWidth = canvasWidth
    self.canvasHeight = canvasHeight



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
    self.emission = 0
  
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
    self.radius = radius
    self.diffuse = Color().random()
    self.emission = 0
  
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
    self.emission = 0
  
  def intersection(self, ray):
    d = (self.pos - ray.origin).dot(self.normal.norm()) / (ray.vector().dot(self.normal.norm()))
    
    if d > 0:
      return d
  
  def normal(self, position):
    return self.normal.norm()



def Radiance(ray, depth, scene):
  total_color = Color(0, 0, 0)
  total_reflectance = Color(1, 1, 1)
  total_depth = 1
  
  while True:
    result = False
    hit = False
    
    for object in scene.objects:
      test = object.intersection(ray)
      
      if test > result:
        result = test
        hit = object
    
    if not result or total_depth > depth:
      return total_color
    else:
      intersection = ray.position(result)
      color = hit.diffuse
      normal = hit.normal(intersection)
      nl = normal * (2 * (normal.dot(ray.direction) < 0) - 1)
      
      max_reflectance = max([hit.diffuse.r, hit.diffuse.g, hit.diffuse.b])
      
      total_color = total_color + total_reflectance * hit.emission
      
      if depth > 4:
        if random.uniform(0, 1) < max_reflectance:
          color = color * (1 / max_reflectance)
        else:
          return total_color
      
      total_reflectance = total_reflectance * color
      
      random1 = 2 * pi * random.uniform(0, 1)
      random2 = random.uniform(0, 1)
      
      if abs(nl.dot(ray.direction)) > 0.1:
        u = Vector(0, 1, 0).cross(nl).norm()
      else:
        u = Vector(1, 0, 0).cross(nl).norm()
      
      v = nl.cross(u)
      d = (u * cos(random1) * sqrt(random2) + v * sin(random1) * sqrt(random2) + nl * sqrt(1 - random2)).norm()
      r = Ray(intersection, d)
    
    reflectedRay = Ray(intersection, r.direction - normal * 2 * normal.dot(ray.direction))
    into = normal.dot(nl) > 0
    nc = 1
    nt = 1.5
    
    if into:
      nnt = nc / nt
    else:
      nnt = nt / nc
    
    ddn = r.direction.dot(nl)
    cos2t = 1 - nnt * nnt * (1 - ddn * ddn)
    
    if cos2t < 0:
      r = reflectedRay
    
    tdir = (r.direction * nnt - normal * ((2 * into - 1) * (ddn * nnt + sqrt(cos2t)))).norm()
    a = nt - nc
    b = nt + nc
    R0 = (a / b)**2
    
    if into:
      c = 1 + ddn
    else:
      c = 1 - tdir.dot(normal)
    
    if isnan(c):
      c = 0
    
    Re = R0 + (1 - R0) * c**5
    Tr = 1 - Re
    P = 0.25 + 0.5 * Re
    RP = Re / P
    TP = Tr / (1 - P)
    
    if random.uniform(0, 1) < P:
      total_reflectance = total_reflectance * RP
      r = reflectedRay
    else:
      total_reflectance = total_reflectance * TP
      r = Ray(intersection, tdir)
    
    total_depth += 1
    
class Scene:
  def __init__(self):
    self.objects = []
  
  def addObject(self, object):
    self.objects.append(object)
  
  def addCamera(self, object):
    self.camera = object
    
  def save(self, filename):
    return self.image.save(filename)
