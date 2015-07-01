TEMPLATE = app
CONFIG += console
CONFIG += c++11

linux-g++ | linux-g++-64 | linux-g++-32 {
    # Linux includes
    # PortAudio Library
    # package name: portaudio19-dev
    # version: 19+svn20111121-1
LIBS += -L/usr/lib/x86_64-linux-gnu/libportaudiocpp.so -lportaudio
}

win32 {
    # Windows 32 includes
LIBS += "C:\portaudio\libportaudio-2.dll"
}

win64 {
    # Windows 32 includes
LIBS += "C:\portaudio\libportaudio-2.dll"
}


QT += core gui
QT += widgets


SOURCES += src/main.cpp \
    src/game.cpp \
    src/gameobject.cpp \
    src/movingobject.cpp \
    src/shoot.cpp \
    src/player.cpp \
    src/enemy.cpp \
    src/input.cpp \
    src/audio.cpp \
    src/audiocontrol.cpp \
    src/menu.cpp \
    src/powerup.cpp

HEADERS += \
    src/game.h \
    src/gameobject.h \
    src/movingobject.h \
    src/shoot.h \
    src/player.h \
    src/enemy.h \
    src/input.h \
    src/audio.h \
    src/audiocontrol.h \
    src/definitions.h \
    src/menu.h \
    src/powerup.h \
    src/portaudio.h

RESOURCES += \
    src/ressources.qrc


# Kopiere Dateien in Build Verzeichnis (zu große Dateigrößen für Ressources)
# Sources Verzeichnispfad und Build Verzeichnis Pfad darf keine Umlaute oder Sonderzeichen (z.B. ++) enthalten.
audios.path = $$OUT_PWD/audios
audios.files = src/audios/*
images.path = $$OUT_PWD/images
images.files = src/images/*
levelFiles.path = $$OUT_PWD/levelFiles
levelFiles.files = src/levelFiles/*


INSTALLS += \
    audios \
    images \
    levelFiles
