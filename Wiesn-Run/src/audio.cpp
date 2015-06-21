#include "audio.h"

Audio::Audio(std::string state_name) {
}

Audio::~Audio() {
}

/**
 * @brief  Audio::getSamples
 *         "getSamples" gibt bei Aufruf alle Samples der zu Audioobjekt
 *         gehörigen Wave Datei mit Bittiefe 16 bit und 44100 Hz Samplerate
 *         zurück.
 * @return std::vector<int> Samples
 * @author Felix Pfreundtner
 */
std::vector<int> getSamples(){
}

/**
 * @brief  Audio::readSamples
 *         "readSamples" liest bei Aufruf alle Samples der zu Audioobjekt
 *         gehörigen Wave Datei in die Variable "samples" ein.
 *         Eingelesen werden Mono Wave Dateien mit 44100Hz Samplerate.
 *         Es greift hierfür auf die zum Objekt gehörige, in Ressources
 *         gespeicherte Wave Datei mit Pfadnamen "source" zurück.
 *         Die Funktion wertet den Format Header des Wave File aus und liest im
 *         Anschluss den Data Chunk ein.
 *         Bittiefe und Dynamik entsprechen der orginalen Wave Datei.
 * @author Felix Pfreundtner
 */
readSamples(){
}

/**
 * @brief  Audio::readSamples
 *         "readSamples" konvertiert die eingelesen Samples auf das Audioformat
 *         Kanäle 1, Samplerate 44100 Hz, Bittiefe 16 bit um eine gemeinsame
 *         Bearbeitung der Samples verschiedener Audioobjekte in der Klasse
 *         Audiocontrol vornehmen zu können.
 * @author Felix Pfreundtner
 */
to16bitnormSamples(){

}
