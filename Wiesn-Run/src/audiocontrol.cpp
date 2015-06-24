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
    /// erstelle Variable welche true ist wenn der name von newplaystruct bereits in playevents vorhanden ist
    bool nasnameexistinpe;    
    /// erstelle einen Iterator für playevents Liste
    std::list<playStruct>::iterator pe;
    /// erstelle einen Iterator für playevents.volume Liste
    std::list<float>::iterator pev;
    /// erstelle einen Iterator für newplaystruct.volume Liste
    std::list<float>::iterator npsv;
    /// setze alle die Abspielinformation aller playstructs in playevents auf false (verhindere weiteres abspielen)
    for (std::list<playStruct>::iterator pe = playevents.begin(); pe != playevents.end(); pe++) {
        pe->play = false;
    }

    /// aktualisiere die Abspielinformation und Distanzwerte aller playstructs aus playevents mit aktuellen GameLogik Werten
    /// iteriere über alle audioStructs der audioevents Liste
    while (!(audioevents->empty())) {
        /// entnehme neues audioStruct aus audioevents Liste
        newaudiostruct = *audioevents->begin();
        /// setzte Variable nasnameexistinpe auf false, da newaudiostruct bisher nicht in playevents gefunden wurde
        nasnameexistinpe = false;
        /// iteriere über alle bereits bestehenden playStructs in Liste playevents
        for (pe = playevents.begin(); pe != playevents.end(); pe++) {
            /// falls der name eines neuen audiostruct bereits in playevents vorhanden ist (also bereits abgespielt wird)
            if (newaudiostruct.name.compare(pe->name) == 0) {
                /// übernehmen die aktuellen Distanzwerte des neuen audiostructs
                pe->volume = newaudiostruct.distance;
                /// Wandle die distance Liste in eine Volume Liste um (volume = 1 - distance).
                for (pev = pe->volume.begin(); pev != pe->volume.end(); pev++) {
                    *pev = 1.0 - *pev;
                }
                /// setzte play auf true, da das playstruct weiter abgespielt werden soll
                pe->play = true;
                /// setzte Variable nasnameexistinpe auf true, da newaudiostruct bisher in playevents gefunden wurde
                nasnameexistinpe = true;    
            }
        }
        /// wenn der name von newaudiostruct noch nicht in audioevents vorhanden ist
        if (nasnameexistinpe == false) {
            /// schreibe Namen des neuen audioStruct in ein neues playStruct
            newplaystruct.name = newaudiostruct.name;
            /// schreibe Distanz Liste des neuen audioStruct in die Volume Liste des playStruct
            newplaystruct.volume = newaudiostruct.distance;
            /// Wandle die distance Liste in eine Volume Liste um (volume = 1 - distance).
            for (npsv = newplaystruct.volume.begin(); npsv != newplaystruct.volume.end(); npsv++) {
                *npsv = 1.0 - *npsv;
            }
            /// setzte play auf true, da das playstruct abgespielt werden soll
            newplaystruct.play = true;
            /// füge das neue playstruct der Liste playevents hinzu
            playevents.push_back(newplaystruct);
        }
        /// Lösche audioStruct aus audioevents Liste da alle Werte in playevents übernommen wurden
        audioevents->pop_front();
    }
    /// lösche alle playstructs aus der events Liste welche nicht mehr abgespielt werden sollen
    pe = playevents.begin();
    while(pe != playevents.end()) {
        if(pe->play == false) {
            pe = playevents.erase(pe);
        }
        else {
            pe++;
        }
    }
}
