#include "audio.h"

/**
 * @brief  Audio::Audio
 *         Konstruktor instanziert ein Objekt der Klasse Audio.
 * @author  Felix Pfreundtner
 */
Audio::Audio(std::string state_name) {
    qDebug("succesfull created audio object");
}

/**
 * @brief  Audio::~Audio
 *         Destruktor löscht ein Objekt der Klasse Audio
 * @author  Felix Pfreundtner
 */
Audio::~Audio() {
}

/**
 * @brief  Audio::getSamples
 *         "getSamples" gibt bei Aufruf alle Samples der zu Audioobjekt
 *         gehörigen Wave Datei mit Bittiefe 16 bit und 44100 Hz Samplerate
 *         zurück.
 * @return std::vector<int> samples
 * @author Felix Pfreundtner
 */
std::vector<int> Audio::getSamples() {
    return samples;
}

/**
 * @brief  Audio::getSource
 *         "getSource" gibt bei Aufruf den Namen des Objektes zurück welcher
 *         welcher dem Pfad in der Ressourcendatenbank entspricht.
 * @return std::string source
 * @author Felix Pfreundtner
 */
std::string Audio::getSource() {
    return source;
}

/**
 * @brief  Audio::readSamples
 *         "readSamples" liest bei Aufruf alle Samples der zu Audioobjekt
 *         gehörigen Wave Datei in die Variable "samples" ein.
 *         Eingelesen werden Mono Wave Dateien mit 44100Hz Samplerate.
 *         Es greift hierfür auf die zum Objekt gehörige, in der
 *         Ressourcendatenbank gespeicherte Wave Datei mit Pfadnamen
 *         "source" zurück.
 *         Die Funktion wertet den Format Header des Wave File aus und liest im
 *         Anschluss den Data Chunk ein.
 *         Bittiefe und Dynamik entsprechen der orginalen Wave Datei.
 * @author Felix Pfreundtner
 */
void Audio::readSamples() {

}

/**
 * @brief  Audio::readSamples
 *         "readSamples" konvertiert die eingelesen Samples auf das Audioformat
 *         Kanäle 1, Samplerate 44100 Hz, Bittiefe 16 bit um eine gemeinsame
 *         Bearbeitung der Samples verschiedener Audioobjekte in der Klasse
 *         Audiocontrol vornehmen zu können.
 * @author Felix Pfreundtner
 */
void Audio::to16bitnormSamples() {

}
