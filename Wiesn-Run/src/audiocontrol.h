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
 * @brief  Die AudioControl Klasse synchronisiert alle aktuellen Audioausgabeanweisungen des Game Objekt mit dem PortAudio Wiedergabe Thread und ermöglicht das blockweise Abspielen von Samples unter Einbezug der Distanzinformationen Spieler zum audioEvent (2D Audio). Dine Instanz der Klasse AudioControl audioOutput wird zum Spielstart im game Objekt erstellt. Beim Erstellen wird über den Konstruktor für alle im Audio Ordner gespeicherten WAVE Dateien (WAVE Datei -> audioEventgruppe audioType) ein Objekt der Klasse Audio erstellt und an die Liste audioobjects angehängt. Der Datentyp eines audioEvents ist ein audioStruct, welches eine ID, einen audioType und eine Distanzinformation besitzt, genaueres siehe Definitions.h. Der Datentyp der zugehörigen Abspielinformation ist ein playStruct, welches eine id, einen audioType, eine Lautstärkeinformation, einen Zeiger auf das passende Audio Objekt mit den Samples und eine aktuelle Abspielpostion in Samples besitzt. In jedem Spiel-Step erzeugt das Game Objekt alle im Moment abzuspielenden audioEvents über die Funktion updateaudioEvents() und übergibt die Liste audioEvents der updatePlayevents() Methode. Jedes audioStruct wird aus der Liste entnommen und dessen id mit allen ids, der im Moment in der Liste playEvents stehenden playStructs, verglichen. Die Distanzinformation "|Spieler - Ort audioEvent|" des audioStruct wird linear in eine Volumeninformation umgerechnet. Ist das zum audioStruct zugehörige playStruct bereits vorhanden, so wird nur die Distanzinformation aktualisiert. Ist kein passendes playStruct vorhanden wird ein neues playStruct aus der audioStruct Information erzeugt und der Liste playevents angehängt. Wird ein vorher abgespieltes playStruct nun nicht mehr vom Game Objekt als audioStruct gesendet, wird das playStruct aus der Liste playevents entfernt und das audioEvent nicht weiter abgespielt.
 *
 * Für die Audio Wiedergabe wurde die Bibliothek PortAudio gewählt. Sie ermöglicht eine Low Level Audioausgabe auf Sampleebene. PortAudio wird zum Programmstart über die Methode playInitialize als Thread gestartet, was eine gleichzeitige Erstellung von audioEvents im Spielablauf durch das Game Objekt und Rückgriff auf die aktuellen, in der Instanzvariable playevents, stehenden Ausgabeinformationen über eine Instanz Callbackfunktion instancepaCallback() ermöglicht. Das Abspielen erfolgt unabhängig vom Step Takt des Game Objekts, was die Stabilität der Wiedergabe garantiert. Die Audioausgabe wird hierbei blockweise mit Blöckgröße 1024 Samples (44100 Hz Samplingfrequenz) erstellt. Die statische Callback Methode der Klasse staticpaCallback() wird von PortAudio autoamtisch immer dann aufgerufen, wenn der PortAudio Stream einen neuen Ausgabeblock benötigt, da der letzte abgespielt wurde. Die Methode ruft im Anschluss die Instanz Callback Funktion instancepaCallback() des AudioControl Objekt audioOutput auf, welche über eine Mutex auf die Instanzvariable playevents zugreift. Bei jedem Aufruf wird in instancepaCallback() die Liste playevents ausgewertet und für jedes playStruct über den Zeiger auf das zugehörige Audio Objekt mit getSample() ein Sample eingelesen. Durch Multiplikation mit der aktuellen im playStruct stehenden Volumeninformation wird die Distanz des audioEvents zum Spieler in jedem Block neu berücksichtigt. Nach Auswerten eines Samples wird im playStruct der Positionswert um 1 erhöht. Ist der Positionswert größer als getSamplenumber() wird die Position auf 0 gesetzt und das audioEvent wieder von Beginn an abgespielt (Loop). Das Gleiche wird für die anderen playStructs in der Liste playevents durchgeführt. Durch Summation aller Samples wird der aktuelle Ausgabeblock gemischt, welcher von PortAudio wiedergeben wird. Es wurden zudem zwei Filter Effekte programmiert, welche auftreten wenn der Spieler betrunken ist (Audiowiedergabe ausgewählter audioTypes wird pro Sample um ein Sample verzögert) und der Spieler nur noch einen Lebenspunkt hat (Audiowiedergabe ausgewählter audioTypes wird pro Sample um ein Sample erhöht).
 *
 * @author  Felix Pfreundtner
 */
class AudioControl{

public:

    // Methoden
    AudioControl();
    ~AudioControl();
    void playInitialize();
    void playTerminate();
    void updatePlayevents(std::list<struct audioStruct> *audioevents);

private:

    /**
     * @brief  playStruct definiert die Struktur eines playEvents
     */
    struct playStruct{
        /// id des playStruct
        int id;
        /// audioType des playStruct
        audioType type;
        /// Lautstärke des playStruct
        float volume;
        /// variable welche angibt ob das playEvent im Moment abgespielt wird
        bool playnext;
        /// Zeiger auf das Audio Object des playEvents, welches der audioEventgruppe type zugeordnet ist
        Audio* audioobject;
        /// aktuelle Abspielposition des Audiobjekt in Samples
        int position;

    };

    /**
     * @var  enum statusFilter
     * @brief  statusFilter definiert alle Audio Filter Status Optionen
     */
    enum statusFilter {
        no,
        alcohol,
        lifecritical
    };

    // Methoden
    int instancepaCallback(const void *input, void *output,
                           unsigned long frameCount,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags);

    /**
     * @brief  staticpaCallback ist die statische Callback Methode der AudioControl Klasse. Die Methode wird immer dann aufgerufen, wenn der PortAudio Stream einen neuen Ausgabeblock benötigt, da der letzte abgespielt wurde. Die Methode ruft die Methode instancepaCallback auf, welche nicht statisch ist und auf alle Instanz Variablen und Methoden (des von Game erzeugten AudioControl Ojektes audioOutput) zugreifen kann. Dies ermöglicht einen einfachen Austausch von audiobezogenen Informationen zwischen Game Thread und Portaudio Wiedergabethread.
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
     * @brief  mtx ist eine Mutex, welche zwischen dem Game Thread und dem PortAudio Ausgabe Thread vermittelt. Es muss die gleichzeitig von Game über updatePlayevents() beschriebene und PortAudio über instancepaCallback() gelesene Liste playevents gelockt werden.
     */
    std::mutex mtx;
    /**
     * @var  std::list<playStruct> playevents
     * @brief  playevents beinhaltet eine Liste mit allen im Moment abgespielten playStructs.
     */
    std::list<playStruct> playevents;
    /**
     * @var  std::vector<Audio> audioobjects
     * @brief  audioobjects beinhaltet eine vector mit allen vorhandenen Objekten der Klasse Audio.
     */
    std::vector<Audio> audioobjects;
    /**
     * @var  int waitinms
     * @brief  waitinms speichert die Wartezeit bis zum Beenden von PortAudio in Millisekunden.
     */
    int waitinms;
    /**
     * @var  PaError playinitializeerror
     * @brief  playinitializeerror speichert eventuell auftretende Error beim Öffenen und Schließen des PortAudio Streams.
     */
    int max_playevents;
    /**
     * @var  int blockcounter
     * @brief  blockcounter zählt die bereits abgespielten Audio Ausgabe Blöcke.
     */    
    int blockcounter;
    /**
     * @var  float mixed_sample
     * @brief  mixed_sample beinhaltet das aktuell gemischte Sample aller audioEvents.
     */
    float mixed_sample;
    /**
     * @var  int playeventsnumber
     * @brief  playeventsnumber beinhaltet die Anzahl an aktuelle abzuspielenden audioEvents.
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
     * @brief  status_filter gibt den Filterstatus an. Wenn kein Audioevent in der audiovents List den Type status_alcohol hat -> enum statusFilter no-> 0. Wenn mindestens ein Audioevent in der audiovents List den Type status_alcohol hat -> enum statusFilter alcohol-> 1. Wenn mindestens ein Audioevent in der audiovents Liste den Type status_lifecritical hat -> enum statusFilter lifecritical-> 2.
     */
    int status_filter;

};

#endif // AUDIOCONTROL_H
