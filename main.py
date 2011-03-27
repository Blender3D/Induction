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
    sphere.emission = 1
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
    
    
    
    for y in range(scene.camera.focalplane.canvasHeight):
      self.emit(QtCore.SIGNAL('updateImage(QImage)'), self.image)
      
      for x in range(scene.camera.focalplane.canvasWidth):
        ray = Ray(scene.camera.pos, scene.camera.pos - Point((float(x) / float(scene.camera.focalplane.canvasWidth)) * scene.camera.focalplane.width, (float(y) / float(scene.camera.focalplane.canvasHeight)) * scene.camera.focalplane.height, scene.camera.focalplane.offset))
        print ray
        result = False
        hit = False
      
        for object in scene.objects:
          test = object.intersection(ray)
          
          if test > result:
            result = test
            hit = object
        
        if hit:
          color = hit.diffuse
        else:
          color = Color(1, 1, 1)
        
        newColor = QtGui.qRgb(color.r * 255, color.g * 255, color.b * 255)
        
        self.image.setPixel(x, y, newColor)

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
