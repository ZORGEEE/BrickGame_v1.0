QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exit.cpp \
    main.cpp \
    mainwindow.cpp \
    snake.cpp \
    tetris.cpp \
    ../../brick_game/snake/backend_s.cpp \
    ../../brick_game/tetris/backend.c \
    ../cli/frontend_s.cpp \
    ../cli/frontend.c


HEADERS += \
    exit.h \
    mainwindow.h \
    snake.h \
    tetris.h \
    ../../brick_game/snake/backend_s.hpp \
    ../../brick_game/tetris/backend.h \
    ../../brick_game/tetris/defines.h \
    ../cli/frontend.h


FORMS += \
    exit.ui \
    mainwindow.ui \
    snake.ui \
    tetris.ui


LIBS += -lncurses
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
