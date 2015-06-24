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
        std::string name;
        std::list<float> volume;

    };

    AudioControl();
    ~AudioControl();

    void update(std::list<struct audioStruct> *audioevents);
private:
    Audio *audio_object;
    /**
     * @brief  played
     *         played beinhaltet eine Liste mit allen im Moment abgespielten audioStruct Informationen.
     * @author  Felix Pfreundtner
     */
    std::list<struct playStruct> playevents;

protected:
};

#endif // INPUT_H
