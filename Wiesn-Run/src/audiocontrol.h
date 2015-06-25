#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H
#define WAITSECONDS   (4)
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

    struct playStruct {
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

    };

    /**
     * @brief  playCallback
     *         playCallback wird von Portaudio aufgerufen wenn nahezu alle
     *         Audiosamples abgespielt sind und neu Audiosamples benötigt werden.
     * @param  Qlist audioevents
     * @author  Felix Pfreundtner
     */
    static int patestCallback( const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData )
    {
        /* Cast data passed through stream to our structure. */
        paTestData *data = (paTestData*)userData;
        float *out = (float*)outputBuffer;
        unsigned int i;
        (void) inputBuffer; /* Prevent unused variable warning. */

        for( i=0; i<framesPerBuffer; i++ )
        {
            *out++ = data->left_phase;  /* left */
            *out++ = data->right_phase;  /* right */
            /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
            data->left_phase += 0.01f;
            /* When signal reaches top, drop back down. */
            if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
            /* higher pitch so we can distinguish left and right. */
            data->right_phase += 0.03f;
            if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
        }
        return 0;
    }


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
    unsigned long blocksize;

    PaError playInitialize();
    void play();

protected:
};

#endif // AUDIOCONTROL_H
