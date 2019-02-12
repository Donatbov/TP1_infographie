# Ceci est un fichier de configuration pour une application Qt
# Il faut peut-etre legerement l adapter pour votre ordinateur.

# nom de votre executable
TARGET  = viewer
# config de l executable
CONFIG *= qt opengl release
CONFIG += c++11
# config de Qt
QT     *= opengl xml

# Noms de vos fichiers entete
HEADERS = Viewer.h
# Noms de vos fichiers source
SOURCES = Viewer.cpp main.cpp

###########################################################
# Commentez/decommentez selon votre config/systeme
# (Une config windows est possible)
###########################################################

# Exemple de configuration Linux de Qt et libQGLViewer
## INCLUDEPATH *= /usr/include
## LIBS *= -L/usr/lib/x86_64-linux-gnu -lqglviewer-qt4

# Exemple de configuration Linux de Qt et libQGLViewer Qt5
# Ubuntu 16.04
INCLUDEPATH *= /usr/include
LIBS *= -L/usr/lib/x86_64-linux-gnu -lQGLViewer

# Exemple de configuration MacOSX avec macports
INCLUDEPATH *= /opt/local/include
LIBS *= -L/opt/local/lib -lQGLViewer 

# Exemple de configuration MacOSX avec frameworks
##  INCLUDEPATH *= /Users/login/libQGLViewer-2.6.4
##  LIBS *= -F/Users/login/Library/Frameworks -framework QGLViewer
