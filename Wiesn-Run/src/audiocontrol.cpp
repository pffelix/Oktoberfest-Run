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
 *         Hierfür wird die liste audiostructs ausgewertet.
 * @param  Qlist audiostructs
 * @author  Felix Pfreundtner
 */
void AudioControl::update(std::list<struct audioStruct> *audiostructs){
//    /**
//     * @brief Game::playAdudio
//     * @param audioEvents
//     */
//    void Game::playSound(std::list<struct audioStruct> *soundEvents) {

//        /// @todo Sound-Overhead hierher

//        while (!(soundEvents->empty())) {
//            // Kopiere erstes Objekt in der Liste nach currentSound
//            soundStruct currentSound = *soundEvents->begin();
//            // Entferne Element aus Liste.
//            soundEvents->pop_front();
//
//            /// @todo Verarbeite Sound.
//        }
//
//        /// @todo Sound-Aufräumarbeiten
//
//    }
}
