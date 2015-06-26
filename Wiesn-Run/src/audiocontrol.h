#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H
#define WAITMS   (4)
#define SAMPLERATE   (44100)
#define BLOCKSIZE (1024)

#include "audio.h"
#include <QtGlobal>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QList>
#include "definitions.h"
#include <algorithm>
#include "portaudio.h"

/**
 * @brief  AudioControl-Klasse
 *         Die AudioControl-Klasse synchronisiert alle Audioausgabeanweisungen und spielt passende Audioobjekte ab.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der audiocontrol.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class AudioControl{

public:
    typedef struct
    {
        float left_phase;
        float right_phase;
    }
    paTestData;

    typedef struct {
        /// id des playstruct Objekts
        int id;
        /// name der playstruct Objektgruppe
        audio name;
        /// Lautstärke des playstruct
        float volume;
        /// variable welche angibt ob sound im moment abgespielt wird
        bool playnext;
        /// Zeiger auf das (Audio-)object des playStruct, welches Eventgruppe "name" zugeordnet ist.
        Audio* objectref;
        /// aktuelle Abspielposition in Audiobjekt in Samples (Beginn des Abspielblockes mit Länge 1024 Samples
        int position;
        /// Gesamtanzahl an Samples des Audioobjekts

    } playStruct;

    AudioControl();
    ~AudioControl();

    void update(std::list<struct audioStruct> *audioevents);

    private:
    /**
     * @brief  playevents
     *         playevents beinhaltet eine Liste mit allen im Moment abgespielten playStructs.
     * @author  Felix Pfreundtner
     */
    std::list<playStruct> playevents;
    /**
     * @brief  audioobjects
     *         audioobjects beinhaltet eine Liste mit allen vorhandenen Objekten der Klasse Audio( und deren Samples).
     * @author  Felix Pfreundtner
     */
    std::list<Audio> audioobjects;
    /**
     * @brief  blocksize
     *         blocksize gibt an wie viele Samples jeweils Blockweise zusammen als Audioausgabe mit PortAudio ausgegeben werden.
     * @author  Felix Pfreundtner
     */
    unsigned long blocksize;
    /**
     * @brief  playinitializeerror
     *         playinitializeerror speichert eventuell auftretende Error beim Öffenen und Schließen des PortAudio Streams.
     * @author  Felix Pfreundtner
     */
    PaError playinitializeerror;

    PaError playInitialize();
    static int patestCallback( const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData );
    void play();

protected:
};

#endif // AUDIOCONTROL_H
