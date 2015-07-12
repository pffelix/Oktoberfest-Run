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
 * @brief  Die AudioControl-Klasse synchronisiert alle Audioausgabeanweisungen und spielt passende Audioobjekte ab. Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 * @author  Felix Pfreundtner
 */
class AudioControl{

public:

    // Funktionen
    AudioControl();
    ~AudioControl();
    void playInitialize();
    void playTerminate();
    void updatePlayevents(std::list<struct audioStruct> *audioevents);

private:

    /**
     * @var  typedef struct playStruct
     * @brief  playStruct definiert die Struktur eines Playevents
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
     * @var  enum statusFilter
     * @brief  statusFilter definiert alle Audio Filter Status Optionen
     */
    enum statusFilter {
        no,
        alcohol,
        life,
        lifecritical
    };

    // Funktionen
    int instancepaCallback(const void *input, void *output,
                           unsigned long frameCount,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags);

    /**
     * @brief  staticpaCallback ist die Statische Callback Funktion der AudioControl Klasse. Die Funktion wird immer dann aufgerufen, wenn der PortAudio Stream einen neuen Ausgabeblock benötigt, da der letzte abgespielt wurde. Die Funktion ruft die Funktion instancepaCallback auf, welche nicht statisch ist und auf alle instance variablen und Funktionen (des von Game erzeugten AudioControl Ojektes audioOutput) zugreifen kann. Dies ermöglicht einen Einfachen Austasch von Audio Blöcken zwischen Game Thread und Portaudio Wiedergabethread.
 * @param  const void *inputBuffer
 * @param  void *outputBuffer
 * @param  unsigned long framesPerBuffer,
 * @param  const PaStreamCallbackTimeInfo* timeInfo,
 * @param  PaStreamCallbackFlags statusFlags
 * @return  ((AudioControl*)userData)
         ->instancepaCallback(input, output, frameCount, timeInfo, statusFlags)
 * @author  Felix Pfreundtner
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

    // Variablen

    /**
     * @var  std::mutex mtx
     * @brief  mtx ist eine Mutex, welche zwischen dem Game Thread und dem PortAudio Ausgabe Thread die Liste playevents lockt.
     */
    std::mutex mtx;
    /**
     * @var  std::list<playStruct> playevents
     * @brief  playevents beinhaltet eine Liste mit allen im Moment abgespielten playStructs.
     */
    std::list<playStruct> playevents;
    /**
     * @var  std::vector<Audio> audioobjects
     * @brief  audioobjects beinhaltet eine Array mit allen vorhandenen Objekten der Klasse Audio( beispielsweise deren Samples als QVector).
     */
    std::vector<Audio> audioobjects;
    /**
     * @var  int waitinms
     * @brief  waitinms speichert die wartezeit bis zum Beenden von PortAudio in Millisekunden.
     */
    int waitinms;
    /**
     * @var  PaError playinitializeerror
     * @brief  playinitializeerror speichert eventuell auftretende Error beim Öffenen und Schließen des PortAudio Streams.
     */
    PaError playinitializeerror;
    /**
     * @var  std::list<playStruct>::iterator callback_pe
     * @brief  callback_pe ist ein Iterator über die Audioevents Liste, welcher in der PortAudio Callback Funktion Verwendung findet.
     */
    std::list<playStruct>::iterator callback_pe;
    /**
     * @var int max_playevents
     * @brief  max_playevents definiert die maximale Anzahl an abgespielten playEvents ohne Clipping Effekte.
     */
    int max_playevents;
    /**
     * @var  int blockcounter
     * @brief  blockcounter zählt die bereits abgespielten Audio Ausgabe Blöcke.
     */    
    int blockcounter;
    /**
     * @var  float mixed_sample
     * @brief  mixed_sample beinhaltet das aktuell von mixSample() gemixte Sample aller audioEvents.
     */
    float mixed_sample;
    /**
     * @var  int playeventsnumber
     * @brief  playeventsnumber beinhaltet die Anzahl an aktuelle abzuspielenden audioEvents. Float Format da mit diesem Wert in mixsamples effizient gerechnet werden muss ohne Castumwandlung Integer in Float.
     */
    int playeventsnumber;
    /**
     * @var  PaStream *pastream
     * @brief  pastream ist ein Zeiger auf den PortAudio Stream.
     */
    PaStream *pastream;
    /**
     * @var  PaError paerror
     * @brief  paerror speichert einen eventuellen PortAudio Error.
     */
    PaError paerror;
    /**
     * @var  status_filter
     * @brief  status_filter gibt den Filterstatus an. Wenn kein Audioevent in der audiovents List den Type status_alcohol hat -> enum none-> 0. Wenn mindestens ein Audioevent in der audiovents List den Type status_alcohol hat -> enum alcohol-> 1. Wenn mindestens ein Audioevent in der audiovents List den Type status_life hat -> enum alcohol-> 2. Wenn mindestens ein Audioevent in der audiovents List den Type status_lifecritical hat -> enum alcohol-> 3.
     */
    int status_filter;

};

#endif // AUDIOCONTROL_H
