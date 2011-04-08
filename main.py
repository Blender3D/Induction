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
    #scene = Scene().load('scene.xml')
    
    scene = Scene()
    
    scene.addCamera(Camera(Point(0, -5, 0), Vector(0, 1, 0), FocalPlane(0.5, 0.5, 1, 800)))
    scene.addObject(Sphere(Point(0, 0, 0), 1))
    
    #light = Sphere(Point(-2, 0, 0), 1)
    #light.emittance = 0.9
    #scene.addObject(light)
    
    self.image = QtGui.QImage(QtCore.QSize(scene.camera.focalplane.canvasWidth, scene.camera.focalplane.canvasHeight), QtGui.QImage.Format_RGB32)
    self.image.fill(QtGui.qRgb(255, 255, 255))
    
    samples = 1
    
    for y in range(0, scene.camera.focalplane.canvasHeight):
      self.emit(QtCore.SIGNAL('updateProgress(int)'), (100.0 * y) / scene.camera.focalplane.canvasHeight)
      
      for x in range(0, scene.camera.focalplane.canvasWidth):
        accumilated = Color(0, 0, 0)
        
        #ray = scene.camera.castRay(x, y)
        ray = Ray(scene.camera.pos, scene.camera.pos - Point((float(x) / float(scene.camera.focalplane.canvasWidth)) * scene.camera.focalplane.width, (float(y) / float(scene.camera.focalplane.canvasHeight)) * scene.camera.focalplane.height, scene.camera.focalplane.offset))
        
        for sample in range(samples):
          accumilated += Trace(ray, scene, 0) / float(samples)
        
        self.image.setPixel(x, y, QtGui.qRgb(accumilated.x * 255, accumilated.y * 255, accumilated.z * 255))
      self.emit(QtCore.SIGNAL('updateImage(QImage)'), self.image)

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
