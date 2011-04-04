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
    scene = Scene().load('scene.xml')
    
    self.image = QtGui.QImage(QtCore.QSize(scene.camera.focalplane.canvasWidth, scene.camera.focalplane.canvasHeight), QtGui.QImage.Format_RGB32)
    rays = 0
    
    while not self.dead:
      x = random.uniform(-scene.camera.focalplane.width / 2.0, scene.camera.focalplane.width / 2.0)
      z = random.uniform(-scene.camera.focalplane.height / 2.0, scene.camera.focalplane.height / 2.0)
      
      pixel = [int(scene.camera.focalplane.width * scene.camera.focalplane.canvasWidth) * (scene.camera.focalplane.width / 2 + x) / scene.camera.focalplane.width, int(scene.camera.focalplane.height * scene.camera.focalplane.canvasHeight) * (scene.camera.focalplane.height / 2 + z) / scene.camera.focalplane.height]
      ray = Ray(scene.camera.pos, Vector(x, 1, z).norm())
      
      '''
      result = False
      hit = False
    
      for object in scene.objects:
        test = object.intersection(ray)
        
        if test > result:
          result = test
          hit = object
      
      if hit:
        c = -(hit.pos - ray.position(result)).norm().dot(ray.direction.norm())
        
        #if c * max(hit.diffuse.list()) > 1:
        #  c = 1.0 / (max(hit.diffuse.list()) + 0.0000001)
        
        #test = Radiance(ray, 5, scene)
        #newColor = QtGui.qRgb(test.r * 255, test.g * 255, test.b * 255)
        newColor = QtGui.qRgb(hit.diffuse.r * c * 255, hit.diffuse.g * c * 255, hit.diffuse.b * c * 255)
        
        self.image.setPixel(2 * pixel[0], 2 * pixel[1], newColor)
      else:
        self.image.setPixel(2 * pixel[0], 2 * pixel[1], QtGui.qRgb(0, 0, 0))
      '''
      
      pathtrace = TracePath2(ray, scene, 0)
      
      self.image.setPixel(2 * pixel[0], 2 * pixel[1], QtGui.qRgb(pathtrace.r * 255, pathtrace.g * 255, pathtrace.b * 255))
      
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
