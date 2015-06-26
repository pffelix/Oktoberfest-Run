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
        float mono;
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
     *         audioobjects beinhaltet eine QVector mit allen vorhandenen Objekten der Klasse Audio( beispielsweise deren Samples als QVector).
     * @author  Felix Pfreundtner
     */
    std::vector<Audio> audioobjects;
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

    // Instanzfunktion Callback des aktuellen AudioControl Objekts
    int myMemberpatestCallback(const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags);

    // Statische Funktion Callback der AudioControl Klasse
    static int patestCallback(
      const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags,
      void *userData )
    // gebe Instanzfunktion Callback zurück
    {
      return ((AudioControl*)userData)
         ->myMemberpatestCallback(input, output, frameCount, timeInfo, statusFlags);
    }


    void play();

protected:
};

#endif // AUDIOCONTROL_H
