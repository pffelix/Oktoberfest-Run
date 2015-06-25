#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H

#include "audio.h"
#include <QString>
#include <QDebug>
#include <iostream>
#include <QList>
#include "definitions.h"
#include <algorithm>

/**
 * @brief  AudioControl-Klasse
 *         Die AudioControl-Klasse synchronisiert alle Audioausgabeanweisungen und spielt passende Audioobjekte ab.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der audiocontrol.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class AudioControl{

public:

    struct playStruct {
        /// id des playstruct Objekts
        int id;
        /// name der playstruct Objektgruppe
        audio name;
        /// Lautstärke des playstruct
        float volume;
        /// variable welche angibt ob sound im moment abgespielt wird
        bool playnext;
        /// Audiobjekt des playStruct mit Samples
        Audio* object;
        /// aktuelle Abspielposition in Audiobjekt in Samples (Beginn des Abspielblockes mit Länge 1024 Samples
        int position;
        /// Gesamtanzahl an Samples des Audioobjekts

    };

    AudioControl();
    ~AudioControl();

    void update(std::list<struct audioStruct> *audioevents);
private:
    /**
     * @brief  playevents
     *         playevents beinhaltet eine Liste mit allen im Moment abgespielten playStructs.
     * @author  Felix Pfreundtner
     */
    std::list<struct playStruct> playevents;
    /**
     * @brief  audioobjects
     *         audioobjects beinhaltet eine Liste mit allen vorhandenen Objekten der Klasse Audio( und deren Samples).
     * @author  Felix Pfreundtner
     */
    std::list<Audio> audioobjects;
    /**
     * @brief  blocksize
     *         blocksize gibt an wie viele Samples jeweils Blockweise zusammen als Audioausgabe mit Portaudio ausgegeben werden.
     * @author  Felix Pfreundtner
     */
    int blocksize;

    void initializeplay();
    void play();


protected:
};

#endif // INPUT_H
