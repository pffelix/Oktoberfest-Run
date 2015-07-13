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
    # Windows 64 includes
LIBS += "C:\portaudio\libportaudio-2.dll"
}


QT += gui core
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
    src/powerup.cpp \
    src/renderGUI.cpp \
    src/renderbackground.cpp

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
    src/portaudio.h \
    src/renderGUI.h \
    src/renderbackground.h

RESOURCES += \
    src/ressources.qrc


# Kopiere Dateien in Build Verzeichnis (zu große Dateigrößen für Ressources)
# Sources Verzeichnispfad und Build Verzeichnis Pfad darf keine Umlaute oder Sonderzeichen (z.B. ++) enthalten.

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

linux-g++ | linux-g++-64 | linux-g++-32 {
    # Linux includes
portaudio.path = $$DESTDIR
portaudio.files = -L/usr/lib/x86_64-linux-gnu/libportaudiocpp.so -lportaudio
}

win32 {
    # Windows 32 includes
portaudio.path = $$DESTDIR
portaudio.files = C:\portaudio\libportaudio-2.dll
}

win64 {
    # Windows 64 includes
portaudio.path = $$DESTDIR
portaudio.files = C:\portaudio\libportaudio-2.dll
}

audios.path = $$DESTDIR/audios
audios.files = src/audios/*
images.path = $$DESTDIR/images
images.files = src/images/*
levelFiles.path = $$DESTDIR/levelFiles
levelFiles.files = src/levelFiles/*


INSTALLS += \
    portaudio \
    audios \
    images \
    levelFiles
