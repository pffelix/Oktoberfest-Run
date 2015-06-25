#include "audiocontrol.h"
#include "portaudio.h"

/**
 * @brief  AudioControl::AudioControl
 *         Konstruktor instanziert ein Objekt der Klasse AudioControl.
 * @author  Felix Pfreundtner
 */
AudioControl::AudioControl() {

    /// erstelle für jede objektgruppe "name" ein audio Objekt welches unter anderem die Samples beinhaltet
    audioobjects.push_back(Audio ("scene_beer"));
    audioobjects.push_back(Audio ("scene_enemy"));
    audioobjects.push_back(Audio ("powerup_chicken"));
    audioobjects.push_back(Audio ("powerup_beer"));
    audioobjects.push_back(Audio ("status_life"));
    audioobjects.push_back(Audio ("status_alcohol"));
    audioobjects.push_back(Audio ("player_walk"));
    audioobjects.push_back(Audio ("player_jump"));
    audioobjects.push_back(Audio ("background_menu"));
    audioobjects.push_back(Audio ("background_highscore"));
    audioobjects.push_back(Audio ("background_level1"));
    audioobjects.push_back(Audio ("background_level2"));
    audioobjects.push_back(Audio ("background_level3"));

    /// setzte die Abspiel Blockgröße auf 1024 Samples
    blocksize = 1024;
    /// initialisere Abspielbibliothek PortAudio
    void playInitialize();


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
    bool nasidexistinpe;
    /// erstelle einen Iterator für playevents Liste
    std::list<playStruct>::iterator pe;
    /// Erstelle einen Iterator auf audioobjects Liste mit Objekten der Klasse Audio
    std::list<Audio>::iterator ao;

    /// initialisiere die Abspielinformation aller playstructs in playevents auf false (verhindere weiteres abspielen im nächsten Step)
    for (std::list<playStruct>::iterator pe = playevents.begin(); pe != playevents.end(); pe++) {
        pe->playnext = false;
    }

    /// aktualisiere die Abspielinformation und Distanzwerte aller playstructs aus playevents mit aktuellen GameLogik Werten
    /// iteriere über alle audioStructs der audioevents Liste
    while (!(audioevents->empty())) {
        /// entnehme neues audioStruct aus audioevents Liste
        newaudiostruct = *audioevents->begin();
        /// setzte Variable nasnameexistinpe auf false, da newaudiostruct bisher nicht in playevents gefunden wurde
        nasidexistinpe = false;
        /// iteriere über alle bereits bestehenden playStructs in Liste playevents
        for (pe = playevents.begin(); pe != playevents.end(); pe++) {
            /// falls die id eines neuen audiostruct bereits in diesem playStruct von playevents vorhanden ist (also bereits abgespielt wird)
            if (newaudiostruct.id == pe->id) {
                /// übernehmen die aktuellen Distanzwerte des neuen audiostructs und wandle sie in eine Volumen Information um (volume = 1 - distance).
                pe->volume = 1.0 - newaudiostruct.distance;
                /// erhöhe Abspielposition um Blocksize, da ein Step vergangen ist
                //pe->position += blocksize;
                /// setzte playnext auf true, da das playstruct auch im nächsten Step abgespielt werden soll
                pe->playnext = true;
                /// setzte Variable nasnameexistinpe auf true, da newaudiostruct bisher in playevents gefunden wurde
                nasidexistinpe = true;
            }
        }
        /// wenn der name von newaudiostruct noch nicht in audioevents vorhanden ist (struct noch nicht abgespielt wird)
        if (nasidexistinpe == false) {
            /// schreibe ID des neuen audioStruct in ein neues playStruct
            newplaystruct.id = newaudiostruct.id;
            /// schreibe Gruppen Namen des neuen audioStruct in ein neues playStruct
            newplaystruct.name = newaudiostruct.name;
            /// übernehmen die aktuellen Distanzwerte des neuen audiostructs und wandle sie in eine Volumen Information um (volume = 1 - distance).
            newplaystruct.volume = 1.0 - newaudiostruct.distance;
            /// setzte Iterator auf das Objekt in audioobjects Liste mit enum "name"
            ao = std::next(audioobjects.begin(), newaudiostruct.name);
            /// speichere einen Zeiger auf das (Audio-)Objekt in audioobjects in newplaystruct
            newplaystruct.objectref = &*ao;
            /// setzte Abspielposition auf 0 Samples (Beginne Abspielen)
            newplaystruct.position = 0;
            /// setzte playnext auf true, da das playstruct auch im nächsten Step abgespielt werden soll
            newplaystruct.playnext = true;
            /// füge das neue playstruct der Liste playevents hinzu
            playevents.push_back(newplaystruct);
        }
        /// Lösche audioStruct aus audioevents Liste da alle Werte in playevents übernommen wurden
        audioevents->pop_front();
    }
    /// lösche alle playstructs aus der events Liste welche nicht mehr abgespielt werden sollen
    pe = playevents.begin();
    while(pe != playevents.end()) {
        if(pe->playnext == false) {
            pe = playevents.erase(pe);
        }
        else {
            pe++;
        }
    }
}


/**
 * @brief  play
 *         play spielt alle in playevents gespeicherten playStructs ab.
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
void AudioControl::play(){
}


/**
 * @brief  initializeplay
 *         initializeplay initialisiert die Abspielbibliothek Portaudio
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
PaError AudioControl::playInitialize(){
    /// erstelle data
    static paTestData data;
    /// Erstelle Zeiger auf Stream pastream
    PaStream *pastream;
    /// Erstelle error Variable
    PaError paerror;
    data.left_phase = data.right_phase = 0.0;
    /// initialisiere Port Audio
    paerror = Pa_Initialize();
    if( paerror != paNoError ) goto error;

    /// Öffene einen Ausgabe Stream
    paerror = Pa_OpenDefaultStream (&pastream,
                                    0,          /// erstelle keine Eingangskänale
                                    1,          /// erstelle Mono Audio Ausgabe
                                    paFloat32,  /// setze Bittiefe der Audioausgabe 16 bit Integer
                                    SAMPLERATE, /// setze Samplerate der Audioausgabe zu 44100 Hz
                                    BLOCKSIZE, /// setze Anzahl an Samples per Bufferblock auf 1024
                                    patestCallback, /// verweise auf Callback Funktion
                                    &data); /// übergebe User-Data
    if( paerror != paNoError ) goto error;

    paerror = Pa_StartStream( pastream );
    if( paerror != paNoError ) goto error;

    /* Sleep for several seconds. */
    Pa_Sleep(WAITSECONDS*1000);

    paerror = Pa_StopStream( pastream );
    if( paerror != paNoError ) goto error;
    paerror = Pa_CloseStream( pastream );
    if( paerror != paNoError ) goto error;
    Pa_Terminate();
    printf("Test finished.\n");
    return paerror;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", paerror );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( paerror ) );
    return paerror;
}




