# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'gui.ui'
#
# Created: Sun Apr 10 14:06:47 2011
#      by: PyQt4 UI code generator 4.7.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_MainWindow(object):
  def setupUi(self, MainWindow):
    MainWindow.setObjectName("MainWindow")
    MainWindow.resize(582, 433)
    self.centralwidget = QtGui.QWidget(MainWindow)
    self.centralwidget.setObjectName("centralwidget")
    self.gridLayout = QtGui.QGridLayout(self.centralwidget)
    self.gridLayout.setObjectName("gridLayout")
    self.label = QtGui.QLabel(self.centralwidget)
    self.label.setObjectName("label")
    self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
    spacerItem = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
    self.gridLayout.addItem(spacerItem, 1, 0, 1, 1)
    self.horizontalLayout_2 = QtGui.QHBoxLayout()
    self.horizontalLayout_2.setObjectName("horizontalLayout_2")
    spacerItem1 = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
    self.horizontalLayout_2.addItem(spacerItem1)
    self.canvas = QtGui.QLabel(self.centralwidget)
    self.canvas.setText("")
    self.canvas.setObjectName("canvas")
    self.horizontalLayout_2.addWidget(self.canvas)
    spacerItem2 = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
    self.horizontalLayout_2.addItem(spacerItem2)
    self.gridLayout.addLayout(self.horizontalLayout_2, 2, 0, 1, 1)
    spacerItem3 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
    self.gridLayout.addItem(spacerItem3, 3, 0, 1, 1)
    self.horizontalLayout = QtGui.QHBoxLayout()
    self.horizontalLayout.setObjectName("horizontalLayout")
    self.startButton = QtGui.QPushButton(self.centralwidget)
    self.startButton.setObjectName("startButton")
    self.horizontalLayout.addWidget(self.startButton)
    self.progressBar = QtGui.QProgressBar(self.centralwidget)
    self.progressBar.setProperty("value", 0)
    self.progressBar.setObjectName("progressBar")
    self.horizontalLayout.addWidget(self.progressBar)
    self.gridLayout.addLayout(self.horizontalLayout, 4, 0, 1, 1)
    MainWindow.setCentralWidget(self.centralwidget)

    self.retranslateUi(MainWindow)
    QtCore.QMetaObject.connectSlotsByName(MainWindow)

  def retranslateUi(self, MainWindow):
    MainWindow.setWindowTitle(QtGui.QApplication.translate("MainWindow", "Python Rendering Engine 0.0.1a", None, QtGui.QApplication.UnicodeUTF8))
    self.label.setText(QtGui.QApplication.translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">Python Rendering Engine 0.0.1a</span></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
    self.startButton.setText(QtGui.QApplication.translate("MainWindow", "Start", None, QtGui.QApplication.UnicodeUTF8))

