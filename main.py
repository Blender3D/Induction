#!/usr/bin/env python

import sys, os

from PyQt4 import QtCore, QtGui
from gui import *
from engine import *
from math import *

RAYDEPTH = 5

class Baker(QtCore.QThread):
  def __init__(self, parent = None):
    super(Baker, self).__init__(parent)
    self.image = None
    self.dead = False
  
  def run(self):
    scene = Scene()
    
    light = Sphere(Point(-1, 2, 1))
    light.radius = 1
    light.emission = 1
    light.diffuse = Color(0.9, 0.9, 0.9)
    
    sphere = Sphere(Point(1, 3, 1))
    sphere.radius = 2
    sphere.emission = 0
    sphere.diffuse = Color(0.9, 0.5, 0.5)
    
    plane = Plane(Point(0, 0, 0))
    plane.diffuse = Color(0.8, 0.8, 0.8)
    plane.normal = Vector(0, 0, 1)
    
    scene.addObject(light)
    scene.addObject(sphere)
    scene.addObject(plane)
    
    scene.addCamera(Camera(Point(0, -5, 0), Vector(0, 1, 0), FocalPlane(0.5, 0.5, 1, 300, 300)))
    
    self.image = QtGui.QImage(QtCore.QSize(scene.camera.focalplane.canvasWidth, scene.camera.focalplane.canvasHeight), QtGui.QImage.Format_RGB32)
    rays = 0
    
    while not self.dead:
      x = random.uniform(-scene.camera.focalplane.width / 2.0, scene.camera.focalplane.width / 2.0)
      z = random.uniform(-scene.camera.focalplane.height / 2.0, scene.camera.focalplane.height / 2.0)
      
      pixel = [int(scene.camera.focalplane.width * scene.camera.focalplane.canvasWidth) * (scene.camera.focalplane.width / 2 + x) / scene.camera.focalplane.width, int(scene.camera.focalplane.height * scene.camera.focalplane.canvasHeight) * (scene.camera.focalplane.height / 2 + z) / scene.camera.focalplane.height]
      ray = Ray(scene.camera.pos, Vector(x, 1, z).norm())
            
      result = False
      hit = False
    
      for object in scene.objects:
        test = object.intersection(ray)
        
        if test > result:
          result = test
          hit = object
      
      if hit:
        color = hit.diffuse
        diffuse = hit.diffuse
        c = hit.normal(ray.position(result)).dot(ray.position(result))
        
        if color.r * c > 1:  color.r = 1 / (c + 0.00001)
        if color.g * c > 1:  color.g = 1 / (c + 0.00001)
        if color.b * c > 1:  color.b = 1 / (c + 0.00001)
        
        newColor = QtGui.qRgb(color.r * diffuse.r * 255 * c, color.g * diffuse.g * 255 * c, color.b * diffuse.b * 255 * c)
        
        self.image.setPixel(2 * pixel[0], 2 * pixel[1], newColor)
      else:
        self.image.setPixel(2 * pixel[0], 2 * pixel[1], QtGui.qRgb(0, 0, 0))
      
      rays += 1
      
      if rays % 500 == 0:  self.emit(QtCore.SIGNAL('updateImage(QImage)'), self.image)

class StartQT4(QtGui.QMainWindow):
  def __init__(self, parent = None):
    QtGui.QWidget.__init__(self, parent)
    
    self.ui = Ui_MainWindow()
    self.ui.setupUi(self)
    
    self.baker = Baker()
    
    self.connect(self.ui.startButton, QtCore.SIGNAL('clicked()'), self.startBaking)
    self.connect(self.ui.stopButton, QtCore.SIGNAL('clicked()'), self.stopBaking)
    self.connect(self.baker, QtCore.SIGNAL('updateImage(QImage)'), self.updateImage)
    self.connect(self.baker, QtCore.SIGNAL('updateRays'), self.updateRays)
  
  def startBaking(self):
    self.baker.dead = False
    self.baker.start()
  
  def stopBaking(self):
    self.baker.dead = True
  
  def updateImage(self, image):
    self.ui.canvas.setPixmap(QtGui.QPixmap.fromImage(image))
  
  def updateRays(self):
    self.ui.raysCounter.setText(str(int(self.ui.raysCounter.text()) + 100))

if __name__ == '__main__':
  app = QtGui.QApplication(sys.argv)
  gui = StartQT4()
  gui.show()
  sys.exit(app.exec_())
