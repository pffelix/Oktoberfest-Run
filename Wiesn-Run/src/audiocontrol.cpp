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
 *         update aktualisiert die im Moment abgespielten, in der Liste "playevents"
 *         gespeicherten playStruct's mit aktuellen audioStruct's aus der Liste audioevents der GameLogik.
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
void AudioControl::update(std::list<struct audioStruct> *audioevents){
    /// erstelle neues temporäres audioStruct, welches stets das aktuelle audioStruct Element der Liste audioevents beinhaltet.
    struct audioStruct newaudiostruct;
    /// erstelle neues temporäres audioStruct, welches stets das aktuelle playStruct Element der Liste playevents beinhaltet.
    struct playStruct newplaystruct;
    /// lösche alte playevents Liste
    playevents.clear();

    /// iteriere über alle audioStructs der audioevents Liste
    while (!(audioevents->empty()))
        /// entnehme neues audioStruct aus audioevents Liste
        newaudiostruct = *audioevents->begin();
        /// schreibe Namen des neuen audioStruct in ein neues playStruct
        newplaystruct.name = newaudiostruct.name;
        /// schreibe Distanz Liste des neuen audioStruct in die Volume Liste des playStruct
        newplaystruct.volume = newaudiostruct.distance;
        /// Wandle die Distanz Liste in eine Volume Liste um (volume = 1- distanz).
        for (std::list<float>::iterator it = newplaystruct.volume.begin(); it != newplaystruct.volume.end(); it++) {
            *it = 1.0 - *it;
        }
        /// Füge neues playStruct der playevents Liste hinzu.
        playevents.push_back(newplaystruct);
        /// Lösche audioStruct aus audioevents Liste da alle Werte in playevents übernommen wurden
        audioevents->pop_front();

    qDebug("stop");
    }
