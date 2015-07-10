#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H
#define _USE_MATH_DEFINES
#define BLOCKSIZE (1024) /// Blockgröße eines Audio Ausgabe Blocks in Samples.
#define SAMPLERATE (44100) ///Samplerate des Audio Ausgabe Signals.

#include "audio.h"
#include <QtGlobal>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QList>
#include "definitions.h"
#include <algorithm>
#include <math.h>
#include "portaudio.h"
#include <cmath>
#include <mutex>

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
    paData;

    typedef struct {
        /// id des playStruct
        int id;
        /// type des playStruct
        audioType type;
        /// Lautstärke des playStruct
        float volume;
        /// variable welche angibt ob sound im moment abgespielt wird
        bool playnext;
        /// Zeiger auf das (Audio-)object des playStruct, welches Eventgruppe "type" zugeordnet ist.
        Audio* audioobject;
        /// aktuelle Abspielposition in Audiobjekt in Samples (Beginn des Abspielblockes mit Länge 1024 Samples
        int position;

    } playStruct;

    enum statusFilter {
        no,
        alcohol,
        life,
        lifecritical
    };

    AudioControl();
    ~AudioControl();
    void playInitialize();
    void update(std::list<struct audioStruct> *audioevents);

    private:
    /**
     * @brief  mtx
     *         mtx ist eine Mutex für playevents.
     * @author  Felix Pfreundtner
     */
    std::mutex mtx;
    /**
     * @brief  playevents
     *         playevents beinhaltet eine Liste mit allen im Moment abgespielten playStructs.
     * @author  Felix Pfreundtner
     */
    std::list<playStruct> playevents;
    /**
     * @brief  audioobjects
     *         audioobjects beinhaltet eine Array mit allen vorhandenen Objekten der Klasse Audio( beispielsweise deren Samples als QVector).
     * @author  Felix Pfreundtner
     */
    std::vector<Audio> audioobjects;
    /**
     * @brief  waitinms
     *         Wartezeit bis zum Beenden von PortAudio in Millisekunden.
     * @author  Felix Pfreundtner
     */
    int waitinms;
    /**
     * @brief  playinitializeerror
     *         playinitializeerror speichert eventuell auftretende Error beim Öffenen und Schließen des PortAudio Streams.
     * @author  Felix Pfreundtner
     */
    PaError playinitializeerror;
    /**
     * @brief  callback_pe
     *         Iterator über Audioevents Liste in PortAudio Callback Funktion. Zur höheren Perfomance bereits hier deklariert.
     * @author  Felix Pfreundtner
     */
    std::list<playStruct>::iterator callback_pe;
    /**
     * @brief  max_playevents
     *         Maximum Number of Playevents without Clipping.
     * @author  Felix Pfreundtner
     */
    int max_playevents;
    /** @brief  blockcontinue
     *         Audio Ausgabe blockcontinue mit gemischen Samples aller während der Programmlaufzeit abgespielten block's.
     * @author  Felix Pfreundtner
     */
    std::vector<float> blockcontinue;
    /**
     * @brief  blockcounter
     *         blockcounter zählt die bereits abgespielten Audio Ausgabe Blöcke.
     * @author  Felix Pfreundtner
     */    
    int blockcounter;
    /**
     * @brief  mixed_sample
     *         mixed_sample beinhaltet das aktuell von mixSample() gemixte Sample aller audioEvents.
     * @author  Felix Pfreundtner
     */
    float mixed_sample;
    /**
     * @brief  playeventsnumber
     *         playeventsnumber beinhaltet die Anzahl an aktuelle abzuspielenden audioEvents.
     *         Float Format da mit diesem Wert in mixsamples effizient gerechnet werden muss ohne Castumwandlung Integer in Float.
     * @author  Felix Pfreundtner
     */
    int playeventsnumber;
    /**
     * @brief  pastream
     *         Erstelle Zeiger auf PortAudio Stream pastream.
     * @author  Felix Pfreundtner
     */
    PaStream *pastream;
    /**
     * @brief  paerror
     *         Erstelle Variable um PortAudio Errors zu speichern.
     * @author  Felix Pfreundtner
     */
    PaError paerror;
    /**
     * @brief  status_alcohol_active
     *         Erstelle Variable welche den aktuellen Filterstatus angibt
     *         wenn kein Audioevent in der audiovents List den Type status_alcohol hat -> enum none-> 0.
     *         wenn mindestens ein Audioevent in der audiovents List den Type status_alcohol hat -> enum alcohol-> 1.
     *         wenn mindestens ein Audioevent in der audiovents List den Type status_life hat -> enum alcohol-> 2.
     *         wenn mindestens ein Audioevent in der audiovents List den Type status_lifecritical hat -> enum alcohol-> 3.

     * @author  Felix Pfreundtner
     */
    int status_filter;

    /// Instanz Callbackfunktion (des von Game.cpp erstellten AudioControl Objekts audioOutput)
    /// hier kann auf alle gesetzten Instanzvariablen zurückgegriffen werden.
    int instancepaCallback(const void *input, void *output,
                               unsigned long frameCount,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags);

    /// Statische Callback Funktion der AudioControl Klasse
    static int staticpaCallback(
                              const void *input, void *output,
                              unsigned long frameCount,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData )
    /// gebe einen Function Pointer auf Instanz Callback Funktion zurück
    {
      return ((AudioControl*)userData)
         ->instancepaCallback(input, output, frameCount, timeInfo, statusFlags);
    }

    void play();

protected:
};

#endif // AUDIOCONTROL_H
