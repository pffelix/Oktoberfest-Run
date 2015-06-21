#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <vector>

/**
 * @brief  Audio-Klasse
 *         Die Audio-Klasse erzeugt Soundobjekte, liest die zugehörigen
 *         Audiosamples ein und übergibt diese an die Kontrollklasse
 *         Audiocontrol, welche die Samples aller Objekte mischt und abspielt.
 *         Die einzelnen Methoden werden in der audio.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class Audio{

public:
    Audio(std::string state_name);
    ~Audio();

    std::string getSource();
    std::vector<int> getSamples();

private:
    /**
     * @brief  source
     *         source speichert den namen des aktuellen objekts als string
     *         welcher dem namen im ressourcenpfad entspricht.
     * @author  Felix Pfreundtner
     */
    std::string source;
    /**
     * @brief  samples
     *         samples speichert die normalisierten samples des audio
     *         objekts als std vector.
     * @author  Felix Pfreundtner
     */
    std::vector<int> samples;

    void readSamples();
    void to16bitnormSamples();

protected:
};

#endif // INPUT_H
