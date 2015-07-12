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
 * @brief  Die AudioControl-Klasse synchronisiert alle Audioausgabeanweisungen und spielt passende Audioobjekte ab. Eine Instanz dieser Klasse wir innerhalb der game.h angelegt. Die einzelnen Methoden werden in der audiocontrol.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class AudioControl{

public:
    AudioControl();
    ~AudioControl();
    void playInitialize();
    void playTerminate();
    void updatePlayevents(std::list<struct audioStruct> *audioevents);

private:

    /**
     * typedef playStruct definiert die Struktur eines Playevents
     */
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

    /**
     * status Filter enum, welches alle Filter Status Möglichkeiten beinhaltet
     */
    enum statusFilter {
        no,
        alcohol,
        life,
        lifecritical
    };

    int instancepaCallback(const void *input, void *output,
                               unsigned long frameCount,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags);

    /**
     * @brief staticpaCallback ist die Statische Callback Funktion der AudioControl Klasse. Die Funktion wird immer dann aufgerufen, wenn der PortAudio Stream einen neuen Ausgabeblock benötigt, da der letzte abgespielt wurde. Die Funktion ruft die Funktion instancepaCallback auf, welche nicht statisch ist und auf alle instance variablen und Funktionen (des von Game erzeugten AudioControl Ojektes audioOutput) zugreifen kann. Dies ermöglicht einen Einfachen Austasch von Audio Blöcken zwischen Game Thread und Portaudio Wiedergabethread.
    */
    static int staticpaCallback(
                              const void *input, void *output,
                              unsigned long frameCount,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData )
    {
      return ((AudioControl*)userData)
         ->instancepaCallback(input, output, frameCount, timeInfo, statusFlags);
    }

    /**
     * mtx ist eine Mutex, welche zwischen dem Game Thread und dem PortAudio Ausgabe Thread die Liste playevents lockt.
     */
    std::mutex mtx;
    /**
     * playevents beinhaltet eine Liste mit allen im Moment abgespielten playStructs.
     */
    std::list<playStruct> playevents;
    /**
     * audioobjects beinhaltet eine Array mit allen vorhandenen Objekten der Klasse Audio( beispielsweise deren Samples als QVector).
     */
    std::vector<Audio> audioobjects;
    /**
     * Wartezeit bis zum Beenden von PortAudio in Millisekunden.
     */
    int waitinms;
    /**
     * playinitializeerror speichert eventuell auftretende Error beim Öffenen und Schließen des PortAudio Streams.
     */
    PaError playinitializeerror;
    /**
     * Iterator über Audioevents Liste in PortAudio Callback Funktion. Zur höheren Perfomance bereits hier deklariert.
     * @author  Felix Pfreundtner
     */
    std::list<playStruct>::iterator callback_pe;
    /**
     * Maximum Number of Playevents without Clipping.
     */
    int max_playevents;
    /**
     * Audio Ausgabe blockcontinue mit gemischen Samples aller während der Programmlaufzeit abgespielten block's.
     */
    std::vector<float> blockcontinue;
    /**
     * blockcounter zählt die bereits abgespielten Audio Ausgabe Blöcke.
     */    
    int blockcounter;
    /**
     * mixed_sample beinhaltet das aktuell von mixSample() gemixte Sample aller audioEvents.
     */
    float mixed_sample;
    /**
     * playeventsnumber beinhaltet die Anzahl an aktuelle abzuspielenden audioEvents. Float Format da mit diesem Wert in mixsamples effizient gerechnet werden muss ohne Castumwandlung Integer in Float.
     */
    int playeventsnumber;
    /**
     * Erstelle Zeiger auf PortAudio Stream pastream.
     */
    PaStream *pastream;
    /**
     * Erstelle Variable um PortAudio Errors zu speichern.
     */
    PaError paerror;
    /**
     * Erstelle Variable welche den aktuellen Filterstatus angibt wenn kein Audioevent in der audiovents List den Type status_alcohol hat -> enum none-> 0. wenn mindestens ein Audioevent in der audiovents List den Type status_alcohol hat -> enum alcohol-> 1. wenn mindestens ein Audioevent in der audiovents List den Type status_life hat -> enum alcohol-> 2. wenn mindestens ein Audioevent in der audiovents List den Type status_lifecritical hat -> enum alcohol-> 3.
     */
    int status_filter;

};

#endif // AUDIOCONTROL_H
