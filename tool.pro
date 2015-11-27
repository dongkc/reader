TEMPLATE = app

QT += qml quick widgets
QT += network

SOURCES += main.cpp \
    uidata.cpp \
    reader.cpp \
    message.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    uidata.h \
    reader.h \
    message.h


LIBS += -L"../../poco-1.6.0/lib" -lPocoFoundation
INCPATH += ../../poco-1.6.0/Foundation/include
