CONFIG -= qt

TEMPLATE = lib
DEFINES += LIBACR_LIBRARY

CONFIG += strict_c warn_on

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += ACR_PLATFORM_LINUX ACR_IDE_QTCREATOR ACR_COMPILER_GCC

SOURCES += \
    ../../src/ACR/alignedbuffer.c \
    ../../src/ACR/buffer.c \
    ../../src/ACR/common.c \
    ../../src/ACR/file.c \
    ../../src/ACR/heap.c \
    ../../src/ACR/string.c \
    ../../src/ACR/varbuffer.c

HEADERS += \
    ../../include/ACR/alignedbuffer.h \
    ../../include/ACR/buffer.h \
    ../../include/ACR/common.h \
    ../../include/ACR/csv.h \
    ../../include/ACR/file.h \
    ../../include/ACR/filesystem.h \
    ../../include/ACR/heap.h \
    ../../include/ACR/json.h \
    ../../include/ACR/private/private_buffer.h \
    ../../include/ACR/private/private_heap.h \
    ../../include/ACR/public.h \
    ../../include/ACR/public/public_alignedbuffer.h \
    ../../include/ACR/public/public_blocks.h \
    ../../include/ACR/public/public_bool.h \
    ../../include/ACR/public/public_buffer.h \
    ../../include/ACR/public/public_byte_order.h \
    ../../include/ACR/public/public_bytes_and_flags.h \
    ../../include/ACR/public/public_clock.h \
    ../../include/ACR/public/public_config.h \
    ../../include/ACR/public/public_count.h \
    ../../include/ACR/public/public_dates_and_times.h \
    ../../include/ACR/public/public_debug.h \
    ../../include/ACR/public/public_decimal.h \
    ../../include/ACR/public/public_file.h \
    ../../include/ACR/public/public_filesystem.h \
    ../../include/ACR/public/public_functions.h \
    ../../include/ACR/public/public_heap.h \
    ../../include/ACR/public/public_info.h \
    ../../include/ACR/public/public_math.h \
    ../../include/ACR/public/public_memory.h \
    ../../include/ACR/public/public_string.h \
    ../../include/ACR/public/public_timer.h \
    ../../include/ACR/public/public_unique_strings.h \
    ../../include/ACR/public/public_units.h \
    ../../include/ACR/public/public_varbuffer.h \
    ../../include/ACR/string.h \
    ../../include/ACR/varbuffer.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += \
    $$PWD/../../include
