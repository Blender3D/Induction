#!/usr/bin/env python

import sys, os

from PyQt4 import QtCore, QtGui
from gui import *
from engine import *
from numpy import *

class Baker(QtCore.QThread):
  def __init__(self, parent = None):
    super(Baker, self).__init__(parent)
    self.image = None
    self.dead = False
  
  def run(self):
    #scene = Scene().load('scene.xml')
    
    scene = Scene()
    sphere = Sphere(Point(0, 0, 0), 1)
    sphere.diffuse = Color(1.0, 1.0, 1.0)
    
    scene.addCamera(Camera(Point(0, -5, 0), Vector(0, 1, 0), FocalPlane(0.5, 0.5, 1, 400)))
    scene.addObject(sphere)
    
    light = Sphere(Point(-1.8, 0, 0), 0.6)
    light.emittance = 0.9
    light.diffuse = Color(1.0, 1.0, 1.0)
    scene.addObject(light)
    
    constantX = scene.camera.focalplane.width / scene.camera.focalplane.canvasWidth - scene.camera.focalplane.width / 2.0
    constantY = scene.camera.focalplane.height / scene.camera.focalplane.canvasHeight - scene.camera.focalplane.height / 2.0
    
    self.image = CellImage(scene.camera.focalplane.canvasWidth, scene.camera.focalplane.canvasHeight)
    
    for i in range(50):
      print i
      
      for y in range(0, scene.camera.focalplane.canvasHeight):
        self.emit(QtCore.SIGNAL('updateProgress(int)'), (100.0 * float(y) / scene.camera.focalplane.canvasHeight))
        
        for x in range(0, scene.camera.focalplane.canvasWidth):
          self.image.setPixel(x, y, self.image.getPixel(x, y) + Trace(Ray(scene.camera.pos, Point(x * constantX, 1, y * constantY)), scene, 0) / float(50))
        
        self.emit(QtCore.SIGNAL('updateImage(QImage)'), self.image.toQImage())

class StartQT4(QtGui.QMainWindow):
  def __init__(self, parent = None):
    QtGui.QWidget.__init__(self, parent)
    
    self.ui = Ui_MainWindow()
    self.ui.setupUi(self)
    
    self.baker = Baker()
    
    self.connect(self.ui.startButton, QtCore.SIGNAL('clicked()'), self.startBaking)
    self.connect(self.baker, QtCore.SIGNAL('updateImage(QImage)'), self.updateImage)
    self.connect(self.baker, QtCore.SIGNAL('updateProgress(int)'), self.updateProgress)
  
  def startBaking(self):
    self.baker.start()
  
  def updateImage(self, image):
    self.ui.canvas.setPixmap(QtGui.QPixmap.fromImage(image))
  
  def updateProgress(self, progress):
    self.ui.progressBar.setValue(progress)

if __name__ == '__main__':
  app = QtGui.QApplication(sys.argv)
  gui = StartQT4()
  gui.show()
  sys.exit(app.exec_())
