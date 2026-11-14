CONFIG -= qt

TEMPLATE = lib
TARGET = ACR
CONFIG += strict_c warn_on

DEFINES += LIBACR_LIBRARY

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
    $$PWD/../../src/ACR/alignedbuffer.c \
    $$PWD/../../src/ACR/buffer.c \
    $$PWD/../../src/ACR/counter.c \
    $$PWD/../../src/ACR/datetime.c \
    $$PWD/../../src/ACR/file.c \
    $$PWD/../../src/ACR/heap.c \
    $$PWD/../../src/ACR/info.c \
    $$PWD/../../src/ACR/string.c \
    $$PWD/../../src/ACR/timer.c \
    $$PWD/../../src/ACR/unicode.c \
    $$PWD/../../src/ACR/varbuffer.c

HEADERS += \
    $$files($$PWD/../../include/ACR/*.h) \
    $$files($$PWD/../../include/ACR/private/*.h) \
    $$files($$PWD/../../include/ACR/public/*.h)

INCLUDEPATH += $$PWD/../../include

CONFIG(debug, debug|release) {
    ACR_BUILD_CONFIGURATION = debug
} else {
    ACR_BUILD_CONFIGURATION = release
}
DESTDIR = $$PWD/build/$$[QT_VERSION]/$$ACR_BUILD_CONFIGURATION

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
