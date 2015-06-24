#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H

#include "audio.h"
#include <QString>
#include <QDebug>
#include <iostream>
#include <QList>
#include "definitions.h"


/**
 * @brief  AudioControl-Klasse
 *         Die AudioControl-Klasse synchronisiert alle Audioausgabeanweisungen und spielt passende Audioobjekte ab.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der audiocontrol.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class AudioControl{

public:
    AudioControl();
    ~AudioControl();

    void update(std::list<struct audioStruct> *audiostructs);
private:
    Audio *audio_object;

protected:
};

#endif // INPUT_H
