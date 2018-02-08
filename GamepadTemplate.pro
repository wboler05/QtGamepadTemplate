#-------------------------------------------------
#
# Project created by QtCreator 2018-02-08T02:19:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GamepadTemplate
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

win32 {

## Link to Xinput
message(Using Win32)

contains(QT_ARCH, i386) {
 BIT_BUILD = x86
}else{
 BIT_BUILD = x64
}

message(Bit build: $$BIT_BUILD)

# Find the lib path
XinputPath = $$(WindowsSdkDir)\\Lib\\$$(WindowsSdkLibVersion)\\um\\$$BIT_BUILD
exists($$XinputPath) {
    message(Found that Lib path: $$XinputPath)
    LIBS += -L$$XinputPath \
            -lxinput \
            -lXinput9_1_0
    message(THE LIBS ARE: $$LIBS)
}else{
    message(Missing XinputPath: $$XinputPath)
}


XinputIncludePath = $$(WindowsSdkDir)\\Include\\$$(WindowsSDKLibVersion)\\um
# Find the include path
exists($$XinputIncludePath) {
    message(Found Xinput Include: $$XinputIncludePath)
    INCLUDEPATH += $$XinputIncludePath
}else{
    message(Missing XInputIncludePath: $$XinputIncludePath)
}

}

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gamepadserver.cpp \
    gamepadstate.cpp

HEADERS += \
        mainwindow.h \
    gamepadserver.h \
    gamepadstate.h

FORMS += \
        mainwindow.ui
