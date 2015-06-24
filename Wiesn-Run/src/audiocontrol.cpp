#include "audiocontrol.h"

/**
 * @brief  AudioControl::AudioControl
 *         Konstruktor instanziert ein Objekt der Klasse AudioControl.
 * @author  Felix Pfreundtner
 */
AudioControl::AudioControl() {
    Audio* audio_object = new Audio ("sine_1kHz_(44.1,1,16)");
}

/**
 * @brief  AudioControl::~AudioControl
 *         Destruktor löscht ein Objekt der Klasse AudioControl
 * @author  Felix Pfreundtner
 */
AudioControl::~AudioControl() {
}

/**
 * @brief  update
 *         update aktualisiert die intern gespeicherten audioStruct's des letzen Steps mit aktuellen audioStruct's der GameLogik.
 *         Hierfür wird die liste audioevents ausgewertet.
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
void AudioControl::update(std::list<struct audioStruct> *audioevents){
    struct audioStruct newaudiostruct;
    struct playStruct newplaystruct;
    playevents.clear();
    while (!(audioevents->empty())) {
        newaudiostruct = *audioevents->begin();

        newplaystruct.name = newaudiostruct.name;
        newplaystruct.volume = newaudiostruct.distance;
        for (std::list<float>::iterator it = newplaystruct.volume.begin(); it != newplaystruct.volume.end(); it++) {
            *it = 1 - *it;
        }
        audioevents->pop_front();
        playevents.push_back(newplaystruct);
        qDebug("stop");
    }
}
