QT += widgets core

INCLUDEPATH  += include
INCLUDEPATH  += /home/hsherief/boost/include
SOURCES       = src/z_qpoint.cpp \
                src/z_qline.cpp \
                src/z_qtri.cpp \
                src/z_qrect.cpp \
                src/z_qellipse.cpp \
                tests/test_z_qtshapes.cpp
TARGET        = test_zqtshapes
LIBS += -L/home/hsherief/boost/lib/ -lboost_system-mt
