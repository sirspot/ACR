QT += core gui widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    DEFINES += ACR_PLATFORM_WIN ACR_IDE_QTCREATOR ACR_COMPILER_MINGW
}
unix:!macx {
    DEFINES += ACR_PLATFORM_LINUX ACR_IDE_QTCREATOR ACR_COMPILER_GCC
}
macx {
    DEFINES += ACR_PLATFORM_MAC ACR_IDE_QTCREATOR ACR_COMPILER_CLANG
}

SOURCES += \
    main.cpp \
    acr_testqt.cpp

HEADERS += \
    acr_testqt.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../include

CONFIG(debug, debug|release) {
    ACR_BUILD_CONFIGURATION = debug
} else {
    ACR_BUILD_CONFIGURATION = release
}
ACR_LIBRARY_DIR = $$clean_path($$PWD/../libACR/build/$$[QT_VERSION]/$$ACR_BUILD_CONFIGURATION)

DESTDIR = $$OUT_PWD/$$ACR_BUILD_CONFIGURATION
LIBS += -L$$ACR_LIBRARY_DIR -lACR

win32 {
    PRE_TARGETDEPS += $$ACR_LIBRARY_DIR/libACR.a
    QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$system_path($$ACR_LIBRARY_DIR/ACR.dll)) $$quote($$system_path($$DESTDIR))
}
macx {
    PRE_TARGETDEPS += $$ACR_LIBRARY_DIR/libACR.dylib
    QMAKE_POST_LINK += $$QMAKE_COPY $$ACR_LIBRARY_DIR/libACR.dylib $$DESTDIR
}
unix:!macx {
    PRE_TARGETDEPS += $$ACR_LIBRARY_DIR/libACR.so
    QMAKE_POST_LINK += $$QMAKE_COPY $$ACR_LIBRARY_DIR/libACR.so $$DESTDIR
}
