QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = DesktopLive2D
RC_ICONS = leaf.ico


MOC_DIR = temp/moc
RCC_DIR = temp/rcc
UI_DIR = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR = temp/bin
CONFIG(release, debug|release): DESTDIR = build_release

#QMAKE_CXXFLAGS += /utf-8
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += live2dwidget.cpp \
    control/LAppAllocator.cpp \
    control/LAppDefine.cpp \
    control/LAppDelegate.cpp \
    control/LAppLive2DManager.cpp \
    control/LAppModel.cpp \
    control/LAppPal.cpp \
    control/LAppSprite.cpp \
    control/LAppTextureManager.cpp \
    control/LAppView.cpp \
    control/LAppWavFileHandler.cpp \
    control/TouchManager.cpp \
    main.cpp \
    mainwindow.cpp \
    subwin.cpp

HEADERS += live2dwidget.h \
        control/LAppAllocator.hpp \
        control/LAppDefine.hpp \
        control/LAppDelegate.hpp \
        control/LAppLive2DManager.hpp \
        control/LAppModel.hpp \
        control/LAppPal.hpp \
        control/LAppSprite.hpp \
        control/LAppTextureManager.hpp \
        control/LAppView.hpp \
        control/LAppWavFileHandler.hpp \
        control/TouchManager.hpp \
        mainwindow.h \
        preDefine.h \
        subwin.h

FORMS += \
    mainwindow.ui \
    subwin.ui


#Qt HotKey
include($$PWD/QHotkey/qhotkey.pri)


INCLUDEPATH += $$PWD/live2d/glew/include
INCLUDEPATH += $$PWD/live2d/glfw/include
INCLUDEPATH += $$PWD/live2d/framework/src
INCLUDEPATH += $$PWD/live2d/Core/include
INCLUDEPATH += $$PWD/live2d/stb



LIBS += $$PWD/live2d/Core/lib/windows/x86_64/142/Live2DCubismCore_MD.lib
LIBS += $$PWD/live2d/framework/lib/Framework.lib
LIBS += $$PWD/live2d/glfw/lib/glfw3.lib
LIBS += $$PWD/live2d/glew/lib/libglew32.lib


DEFINES += CSM_TARGET_WIN_GL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assert.qrc
