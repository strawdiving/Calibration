INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

PUBLIC_HEADERS         += $$PWD/qextserialport.h \
                          $$PWD/qextserialenumerator.h \
                          $$PWD/qextserialport_global.h

HEADERS                += $$PUBLIC_HEADERS \
                          $$PWD/qextserialport_p.h \
                          $$PWD/qextserialenumerator_p.h \

SOURCES                += $$PWD/qextserialport.cpp \
                          $$PWD/qextserialenumerator.cpp

win32:SOURCES          += $$PWD/qextserialport_win.cpp \
                          $$PWD/qextserialenumerator_win.cpp
win32:LIBS             += -lsetupapi -ladvapi32 -luser32
