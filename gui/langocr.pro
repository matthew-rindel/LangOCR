######################################################################
# Automatically generated by qmake (3.1) Sun May 24 16:19:53 2020
######################################################################

TEMPLATE = app
TARGET = langocr
INCLUDEPATH += .
QT += widgets gui
LIBS += -llept -ltesseract 

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += draw_overlay.h screen_overlay.h langocr_app.h 
SOURCES += main.cpp screen_overlay.cpp langocr_app.cpp draw_overlay.cpp
