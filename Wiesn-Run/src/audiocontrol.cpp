#include "audiocontrol.h"

/**
 * @brief  AudioControl::AudioControl
 *         Konstruktor instanziert ein Objekt der Klasse AudioControl.
 * @author  Felix Pfreundtner
 */
AudioControl::AudioControl() {
    Audio* audio_object = new Audio ("sine_1kHz_(44.1,1,8)");
}

/**
 * @brief  AudioControl::~AudioControl
 *         Destruktor löscht ein Objekt der Klasse AudioControl
 * @author  Felix Pfreundtner
 */
AudioControl::~AudioControl() {
}
