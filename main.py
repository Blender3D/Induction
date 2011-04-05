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
    #self.image.fill(QtGui.qRgb(255, 255, 255))
    
    sample = 10
    
    while sample > 1:
      sample -= 1
      
      for y in range(-scene.camera.focalplane.canvasHeight / 2, scene.camera.focalplane.canvasHeight / 2, sample):
        self.emit(QtCore.SIGNAL('updateProgress(int)'), (100.0 * (y + scene.camera.focalplane.canvasHeight / 2)) / scene.camera.focalplane.canvasHeight)
        
        for x in range(-scene.camera.focalplane.canvasWidth / 2, scene.camera.focalplane.canvasWidth / 2, sample):
          accumilated = Color(0, 0, 0)
          
          for sx in range(0, 3):
            for sy in range(0, 3):
              ray = Ray(scene.camera.pos, (scene.camera.pos - Point(scene.camera.focalplane.width - (x + sx / 4.0) * (2 * scene.camera.focalplane.width / scene.camera.focalplane.canvasWidth), scene.camera.pos.y - scene.camera.focalplane.offset, scene.camera.focalplane.height - (y + sy / 4.0) * (2 * scene.camera.focalplane.height / scene.camera.focalplane.canvasHeight))).norm())
              accumilated = accumilated + Trace(ray, scene, 0)
              
          self.image.setPixel(x + scene.camera.focalplane.canvasWidth / 2, y + scene.camera.focalplane.canvasHeight / 2, QtGui.qRgb(accumilated.r * 255, accumilated.g * 255, accumilated.b * 255))
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
