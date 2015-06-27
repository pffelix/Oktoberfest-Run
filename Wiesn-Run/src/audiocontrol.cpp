#include "audiocontrol.h"
#include "portaudio.h"

/**
 * @brief  AudioControl::AudioControl
 *         Konstruktor instanziert ein Objekt der Klasse AudioControl.
 * @author  Felix Pfreundtner
 */
AudioControl::AudioControl() {

    /// erstelle für jede objektgruppe "type" ein audio Objekt welches unter anderem die Samples beinhaltet
    audioobjects.reserve(23);
    audioobjects.insert(audioobjects.begin() + audioType::scene_flyingbeer, Audio("scene_flyingbeer")); // 16bit

    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_tourist, Audio("scene_enemy_tourist")); // 16bit
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_security, Audio("scene_enemy_security")); // 16bit
    //source: http://soundbible.com/1501-Buzzer.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_boss, Audio("scene_enemy_boss")); // 16bit
    //source: http://soundbible.com/1522-Balloon-Popping.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_obstacle, Audio("scene_collision_obstacle")); // 16bit
    //source: http://soundbible.com/1773-Strong-Punch.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_enemy, Audio("scene_collision_enemy")); // 16bit
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_player, Audio("scene_collision_player")); // 16bit
    //source: http://helios.augustana.edu/~dr/105/wav/glasbk.wav
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_flyingbeer, Audio("scene_collision_flyingbeer")); // 16bit
    //source: http://soundbible.com/1858-Metroid-Door.html
    audioobjects.insert(audioobjects.begin() + audioType::powerup_beer, Audio("powerup_beer")); // 16bit
    //source: http://soundbible.com/1639-Power-Up.html
    audioobjects.insert(audioobjects.begin() + audioType::powerup_food, Audio("powerup_food")); // 16bit
    audioobjects.insert(audioobjects.begin() + audioType::status_alcohol, Audio("status_alcohol")); // 16bit
    // source: http://soundbible.com/1612-Slow-HeartBeat.html
    audioobjects.insert(audioobjects.begin() + audioType::status_life, Audio("status_life")); // 16bit
    http://soundbible.com/1707-Hearbeat-2.html
    audioobjects.insert(audioobjects.begin() + audioType::status_lifecritical, Audio("status_lifecritical")); // 16bit
    //source: http://soundbible.com/1266-City-Ambiance.html
    audioobjects.insert(audioobjects.begin() + audioType::status_dead, Audio("status_dead")); // 16bit
    //source: http://www.arts.rpi.edu/public_html/ruiz/VES01/sebram/final/walk_crop.wav
    audioobjects.insert(audioobjects.begin() + audioType::player_walk, Audio("player_walk")); // 16bit
    //source: http://soundbible.com/1343-Jump.html
    audioobjects.insert(audioobjects.begin() + audioType::player_jump, Audio("player_jump")); // 16bit
    //source: http://soundbible.com/1563-Pacman-Introduction-Music.html
    audioobjects.insert(audioobjects.begin() + audioType::background_menu, Audio("background_menu")); // 16bit

    audioobjects.insert(audioobjects.begin() + audioType::background_highscore, Audio("background_highscore")); // 16bit
    audioobjects.insert(audioobjects.begin() + audioType::background_level1, Audio("background_level1")); // 16bit
    //source: http://soundbible.com/1763-Ambience-Casino.html
    audioobjects.insert(audioobjects.begin() + audioType::background_level2, Audio("background_level2")); // 16bit
    audioobjects.insert(audioobjects.begin() + audioType::background_level3, Audio("background_level3")); // 16bit
    audioobjects.insert(audioobjects.begin() + audioType::background_startgame, Audio("background_startgame")); // 16bit
    //source: http://soundbible.com/1823-Winning-Triumphal-Fanfare.html
    audioobjects.insert(audioobjects.begin() + audioType::background_levelfinished, Audio("background_levelfinished")); // 16bit


    /// fülle Block Ausgabe mit Nullen
    std::fill_n(block, BLOCKSIZE, 0);
    /// setzte blockcounter auf 0 Blöcke
    blockcounter = 0;
    /// setzte Wartezeit von Portaudio auf 100 ms
    waitinms = 100;
    /// setzte maximale Anzahl an Playevents auf 10
    /// Wird der Wert höher gesetzt wird die Lautstärke geringer.
    /// Wird der Wert geringer gesetzt steigt die Gefahr des Clippings des Ausgabesignals
    /// Ein Normalisieren aller Ausgabeblöcke wäre möglich, würde jedoch 2D Audio nicht erlauben,
    /// da auch die Dynamik zwischen zwei Blöcken normalisiert wird
    /// -> Distanz- und somit Lautstärkeänderungen von Objekten werden mit normalisiert.
    max_playevents = 4;

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
    playStruct newplaystruct;
    /// erstelle Variable welche true ist wenn die id von newplaystruct bereits in playevents vorhanden ist
    bool nasidexistinpe;
    /// erstelle einen Iterator für playevents Liste
    std::list<playStruct>::iterator pe;

    /// initialisiere die Abspielinformation aller playstructs in playevents auf false (verhindere weiteres abspielen im nächsten Step)
    for (std::list<playStruct>::iterator pe = playevents.begin(); pe != playevents.end(); pe++) {
        pe->playnext = false;
    }

    /// aktualisiere die Abspielinformation und Distanzwerte aller playstructs aus playevents mit aktuellen GameLogik Werten
    /// iteriere über alle audioStructs der audioevents Liste
    while (!(audioevents->empty())) {
        /// entnehme neues audioStruct aus audioevents Liste
        newaudiostruct = *audioevents->begin();
        /// setzte Variable nasidexistinpe auf false, da newaudiostruct bisher nicht in playevents gefunden wurde
        nasidexistinpe = false;
        /// iteriere über alle bereits bestehenden playStructs in Liste playevents
        for (pe = playevents.begin(); pe != playevents.end(); pe++) {
            /// falls die id eines neuen audiostruct bereits in diesem playStruct von playevents vorhanden ist (also bereits abgespielt wird)
            if (newaudiostruct.id == pe->id) {
                /// übernehmen die aktuellen Distanzwerte des neuen audiostructs und wandle sie in eine Volumen Information um (volume = 1 - distance).
                pe->volume = 1.0f - newaudiostruct.distance;
                /// setzte playnext auf true, da das playstruct auch im nächsten Step abgespielt werden soll
                pe->playnext = true;
                /// setzte Variable nasidexistinpe auf true, da newaudiostruct bisher in playevents gefunden wurde
                nasidexistinpe = true;
            }
        }
        /// wenn die id von newaudiostruct noch nicht in audioevents vorhanden ist (struct noch nicht abgespielt wird)
        if (nasidexistinpe == false) {
            /// schreibe ID des neuen audioStruct in ein neues playStruct
            newplaystruct.id = newaudiostruct.id;
            /// schreibe Gruppen Type des neuen audioStruct in ein neues playStruct
            newplaystruct.type = newaudiostruct.type;
            /// übernehmen die aktuellen Distanzwerte des neuen audiostructs und wandle sie in eine Volumen Information um (volume = 1 - distance).
            newplaystruct.volume = 1.0f - newaudiostruct.distance;
            /// speichere einen Zeiger auf das (Audio-)Objekt in audioobjects in newplaystruct
            newplaystruct.objectref = &audioobjects[newaudiostruct.type];
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
    /// lösche alle playstructs aus der events Liste welche im nächsten Step nicht mehr abgespielt werden sollen (playnext = false).
    pe = playevents.begin();
    while(pe != playevents.end()) {
        if(pe->playnext == false) {
            pe = playevents.erase(pe);
        }
        else {
            pe++;
        }
    }
    playeventsnumber = playevents.size();

}




/**
 * @brief  playInitialize
 *         playInitialize initialisiert die Abspielbibliothek Portaudio
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
void AudioControl::playInitialize(){
    /// initialisiere Port Audio
    paerror = Pa_Initialize();
    if( paerror != paNoError ) {
        goto error;
    }

    /// Öffene einen Ausgabe Stream
    paerror = Pa_OpenDefaultStream (&pastream,
                                    0,          /// erstelle keine Eingangskänale
                                    2,          /// erstelle Mono Audio Ausgabe
                                    paInt16,  /// setze Bittiefe der Audioausgabe 16 bit Integer
                                    SAMPLERATE, /// setze Samplerate der Audioausgabe zu 44100 Hz
                                    BLOCKSIZE, /// setze Anzahl an Samples per Bufferblock auf 1024
                                    &AudioControl::staticpaCallback, /// verweise auf Static Callback Funktion
                                    this); /// übergebe User-Data
    if( paerror != paNoError ) {
        goto error;
    }

    paerror = Pa_StartStream( pastream );
    if( paerror != paNoError ) {
        goto error;
    }

    /// Pausiere Funktion wenn Audiostream gerade aktiv ist
    while (Pa_IsStreamActive(pastream) == 1) {
        Pa_Sleep(waitinms);
    }

    paerror = Pa_StopStream( pastream );
    if( paerror != paNoError ) {
        goto error;
    }
    paerror = Pa_CloseStream( pastream );
    if( paerror != paNoError ) {
        goto error;
    }
    Pa_Terminate();
error:
    Pa_Terminate();
    fprintf( stderr, "Ein Meldung trat während der Benutzung der PortAudio Ausgabe auf\n" );
    fprintf( stderr, "Error Nummer: %d\n", paerror );
    fprintf( stderr, "Error Nachricht: %s\n", Pa_GetErrorText( paerror ) );
}


/**
 * @brief  playCallback
 *         playCallback wird von Portaudio aufgerufen wenn nahezu alle
 *         Audiosamples abgespielt sind und neu Audiosamples benötigt werden.
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
int AudioControl::instancepaCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags ) {
    /* Cast data passed through stream to our structure. */
    /// erstelle Zeiger *out auf outputBuffer
    int *out = (int*)outputBuffer;
    /// kein Input aktiviert, verhindere Warnmeldung "unbenutzter Parameter inputBuffer"
    (void) inputBuffer;
    /// keine timeInfo nötig, verhindere Warnmeldung "unbenutzter Parameter inputBuffer"
    (void) timeInfo;
    /// keine statusFlags nötig, verhindere Warnmeldung "unbenutzter Parameter statusFlags"
    (void) statusFlags;


    for(unsigned int block_pos=0; block_pos<framesPerBuffer; block_pos++ ) {

        /// Mix Samples
        mixed_sample = 0;
        for (callback_pe = playevents.begin(); callback_pe != playevents.end(); callback_pe++) {
            mixed_sample += callback_pe->objectref->getSample(callback_pe->position)*callback_pe->volume/max_playevents;
            callback_pe->position += 1;
        }
        // block[block_pos] = mixSample();
        *out++ = mixed_sample;

        //data->mono = audioobjects[0].getSample(i);
        //*out++ = data->left_phase;  /* left */
        //*out++ = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        //data->left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        //if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        //data->right_phase += 0.03f;
        //if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
    }
    blockcounter += 1;
    //std::copy ( block, block + BLOCKSIZE, std::back_inserter ( blockcontinue ) );
    return 0;
}



/**
 * @brief  play
 *         play spielt alle in playevents gespeicherten playStructs ab.
 * @author  Felix Pfreundtner
 */
void AudioControl::play(){
}


/**
 * @brief  getPastream
 *         getPastream gibt einen Zeiger auf den PortAudio Stream pastream zurück
 * @author  Felix Pfreundtner
 */
PaStream* AudioControl::getPastream() {
    return &pastream;
}
