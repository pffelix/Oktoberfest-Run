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
    struct audioStruct currentevent;

    if (playevents.empty() == true) {
        playevents = *audioevents;
    }
    else {
        while (!(audioevents->empty())) {
            currentevent = *audioevents->begin();

            audioevents->pop_front();
           qDebug("worked") ;
        }

    }
//            // Kopiere erstes Objekt in der Liste nach currentSound

//            // Entferne Element aus Liste.
//
//
//            /// @todo Verarbeite Sound.
//        }
//
//        /// @todo Sound-Aufräumarbeiten
//
//    }
}
