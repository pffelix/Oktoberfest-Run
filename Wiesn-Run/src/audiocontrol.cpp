#include "audiocontrol.h"
#include "portaudio.h"

/**
 * @brief  Konstruktor instanziiert ein Objekt der Klasse AudioControl. Es wird für jede audioEventgruppe type ein audio Objekt erstellt, welches unter anderem die Samples der zugehörigen WAVE Datei beinhaltet.
 * @author  Felix Pfreundtner
 */
AudioControl::AudioControl() {
    ///
    audioobjects.reserve(23);
    /// Quelle scene_flyingbeer: http://soundbible.com/1247-Wind.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_flyingbeer, Audio("scene_flyingbeer")); // 16bit
    /// Quelle scene_enemy_tourist: http://www.freesound.org/people/Reitanna/sounds/241215/
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_tourist, Audio("scene_enemy_tourist")); // 16bit
    /// Quelle scene_enemy_security: http://www.freesound.org/people/Robinhood76/sounds/195414/
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_security, Audio("scene_enemy_security")); // 16bit
    /// Quelle scene_enemy_boss: http://soundbible.com/1501-Buzzer.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_boss, Audio("scene_enemy_boss")); // 16bit
    /// Quelle scene_collision_obstacle: http://soundbible.com/1522-Balloon-Popping.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_obstacle, Audio("scene_collision_obstacle")); // 16bit
    /// Quelle scene_collision_enemy: http://www.freesound.org/people/qubodup/sounds/169725/
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_enemy, Audio("scene_collision_enemy")); // 16bit
    /// Quelle scene_collision_player: http://www.freesound.org/people/thecheeseman/sounds/44430/
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_player, Audio("scene_collision_player")); // 16bit
    /// Quelle scene_collision_flyingbeer: http://helios.augustana.edu/~dr/105/wav/glasbk.wav
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_flyingbeer, Audio("scene_collision_flyingbeer")); // 16bit
    /// Quelle powerup_beer: http://www.freesound.org/people/edhutschek/sounds/215634/
    audioobjects.insert(audioobjects.begin() + audioType::powerup_beer, Audio("powerup_beer")); // 16bit
    /// Quelle powerup_food: https://www.freesound.org/people/bassboybg/sounds/264544/
    audioobjects.insert(audioobjects.begin() + audioType::powerup_food, Audio("powerup_food")); // 16bit
    /// Quelle status_alcohol: http://www.freesound.org/people/afleetingspeck/sounds/151180/
    audioobjects.insert(audioobjects.begin() + audioType::status_alcohol, Audio("status_alcohol")); // 16bit
    /// Quelle status_life: http://soundbible.com/1612-Slow-HeartBeat.html
    audioobjects.insert(audioobjects.begin() + audioType::status_life, Audio("status_life")); // 16bit
    /// Quelle status_lifecritical: http://soundbible.com/1612-Slow-HeartBeat.html
    audioobjects.insert(audioobjects.begin() + audioType::status_lifecritical, Audio("status_lifecritical")); // 16bit
    /// Quelle status_dead: http://www.freesound.org/people/Robinhood76/sounds/256469/
    audioobjects.insert(audioobjects.begin() + audioType::status_dead, Audio("status_dead")); // 16bit
    /// Quelle player_walk: http://www.arts.rpi.edu/public_html/ruiz/VES01/sebram/final/walk_crop.wav
    audioobjects.insert(audioobjects.begin() + audioType::player_walk, Audio("player_walk")); // 16bit
    /// Quelle player_jump: http://soundbible.com/266-Boing-Cartoonish.html
    audioobjects.insert(audioobjects.begin() + audioType::player_jump, Audio("player_jump")); // 16bit
    /// Quelle background_menu: http://www.theholidayspot.com/oktoberfest/music/Octoberfest%20--%20Beerdrinking%20song%28Bavarian%29.wma
    audioobjects.insert(audioobjects.begin() + audioType::background_menu, Audio("background_menu")); // 16bit
    /// Quelle background_highscore: http://soundbible.com/1563-Pacman-Introduction-Music.html
    audioobjects.insert(audioobjects.begin() + audioType::background_highscore, Audio("background_highscore")); // 16bit
    /// Quelle background_level1: http://soundbible.com/1763-Ambience-Casino.html
    audioobjects.insert(audioobjects.begin() + audioType::background_level1, Audio("background_level1")); // 16bit
    /// Quelle background_level2: http://www.freesound.org/people/Kyster/sounds/122789/
    audioobjects.insert(audioobjects.begin() + audioType::background_level2, Audio("background_level2")); // 16bit
    /// Quelle background_level3: http://www.freesound.org/people/Westmed/sounds/239538/
    audioobjects.insert(audioobjects.begin() + audioType::background_level3, Audio("background_level3")); // 16bit
    /// Quelle background_startgame: http://www.freesound.org/people/Harbour11/sounds/194625/
    audioobjects.insert(audioobjects.begin() + audioType::background_startgame, Audio("background_startgame")); // 16bit
    /// Quelle background_levelfinished: http://soundbible.com/1823-Winning-Triumphal-Fanfare.html
    audioobjects.insert(audioobjects.begin() + audioType::background_levelfinished, Audio("background_levelfinished")); // 16bit

    // setzte Status Filter auf kein Filter
    status_filter = statusFilter::no;
    // setzte blockcounter auf 0 Blöcke
    blockcounter = 0;
    // setzte Wartezeit von Portaudio auf 100 ms
    waitinms = 100;
    // setzte maximale Anzahl an Playevents auf 7
    // Wird der Wert höher gesetzt wird die Lautstärke geringer.
    // Wird der Wert geringer gesetzt steigt die Gefahr des Clippings des Ausgabesignals
    // Ein Normalisieren aller Ausgabeblöcke wäre möglich, würde jedoch 2D Audio nicht erlauben,
    // da auch die Dynamik zwischen zwei Blöcken normalisiert wird
    // -> Distanz- und somit Lautstärkeänderungen von Objekten würden mit normalisiert werden.
    max_playevents = 7;

}


/**
 * @brief  Destruktor löscht ein Objekt der Klasse AudioControl
 * @author  Felix Pfreundtner
 */
AudioControl::~AudioControl() {

}

/**
 * @brief  updatePlayevents aktualisiert nach Aufruf über Game::step alle im Moment abgespielten, in der Liste "playevents" gespeicherten playStruct's mit aktuellen audioStruct's aus der übergebenen Liste audioevents.
 * @param  std::list<struct audioStruct> *audioevents
 * @author  Felix Pfreundtner
 */
void AudioControl::updatePlayevents(std::list<struct audioStruct> *audioevents){
    // erstelle neues temporäres audioStruct, welches stets das aktuelle audioStruct Element der Liste audioevents beinhaltet.
    struct audioStruct newaudiostruct;
    // erstelle neues temporäres audioStruct, welches stets das aktuelle playStruct Element der Liste playevents beinhaltet.
    playStruct newplaystruct;
    // erstelle Variable welche true ist wenn die id von newplaystruct bereits in playevents vorhanden ist
    bool nasidexistinpe;
    // erstelle einen Iterator für playevents Liste
    std::list<playStruct>::iterator pe;
    // intialsiere status_filter mit no (Annahme kein Audioevent mit type status_alcohol / status_life / status_lifecritical in audioevents Liste)
    status_filter = statusFilter::no;
    // lock mutex
    mtx.lock();

    // initialisiere die Abspielinformation aller playstructs in playevents auf false (verhindere weiteres abspielen im nächsten Step)
    for (std::list<playStruct>::iterator pe = playevents.begin(); pe != playevents.end(); pe++) {
        pe->playnext = false;
    }

    // aktualisiere die Abspielinformation und Distanzwerte aller playstructs aus playevents mit aktuellen GameLogik Werten
    // iteriere über alle audioStructs der audioevents Liste
    while (!(audioevents->empty())) {
        // entnehme neues audioStruct aus audioevents Liste
        newaudiostruct = *audioevents->begin();
        // setzte Variable nasidexistinpe auf false, da newaudiostruct bisher nicht in playevents gefunden wurde
        nasidexistinpe = false;
        // iteriere über alle bereits bestehenden playStructs in Liste playevents
        for (pe = playevents.begin(); pe != playevents.end(); pe++) {
            // falls die id eines neuen audiostruct bereits in diesem playStruct von playevents vorhanden ist (also bereits abgespielt wird)
            if (newaudiostruct.id == pe->id) {
                // übernehmen die aktuellen Distanzwerte des neuen audiostructs und wandle sie in eine Volumen Information um (volume = 1 - distance).
                pe->volume = 1.0f - newaudiostruct.distance;
                // setzte playnext auf true, da das playstruct auch im nächsten Step abgespielt werden soll
                pe->playnext = true;
                // setzte Variable nasidexistinpe auf true, da newaudiostruct bisher in playevents gefunden wurde
                nasidexistinpe = true;
            }
        }
        // wenn die id von newaudiostruct noch nicht in audioevents vorhanden ist (struct noch nicht abgespielt wird)
        if (nasidexistinpe == false) {
            // schreibe ID des neuen audioStruct in ein neues playStruct
            newplaystruct.id = newaudiostruct.id;
            // schreibe Gruppen Type des neuen audioStruct in ein neues playStruct
            newplaystruct.type = newaudiostruct.type;
            // übernehmen die aktuellen Distanzwerte des neuen audiostructs und wandle sie in eine Volumen Information um (volume = 1 - distance).
            newplaystruct.volume = 1.0f - newaudiostruct.distance;
            // speichere einen Zeiger auf das (Audio-)Objekt in audioobjects in newplaystruct
            newplaystruct.audioobject = &audioobjects[newaudiostruct.type];
            // setzte Abspielposition auf 0 Samples (Beginne Abspielen)
            newplaystruct.position = 0;
            // setzte playnext auf true, da das playstruct auch im nächsten Step abgespielt werden soll
            newplaystruct.playnext = true;
            // füge das neue playstruct der Liste playevents hinzu
            playevents.push_back(newplaystruct);
        }
        // Lösche audioStruct aus audioevents Liste da alle Werte in playevents übernommen wurden
        audioevents->pop_front();
    }
    // für alle Playevents in der playevents liste
    pe = playevents.begin();
    while(pe != playevents.end()) {

        // falls Playevent im nächsten Step nicht mehr abgespielt werden sollen (playnext = false).
        if(pe->playnext == false) {
            // lösche playevent aus playevents List
            pe = playevents.erase(pe);
        }
        // falls playevent im nächsten Step abgespielt werden soll
        else {
            // falls Type des aktuellen playevents status_lifecritical ist (niedrigste Filter Priorität)
            if (pe->type == status_lifecritical) {
                // setze Alkohol Status auf aktiv
                status_filter = statusFilter::lifecritical;
            }
            // falls Type des aktuellen playevents status_alcohol ist (höchste Filter Priorität)
            if (pe->type == status_alcohol) {
                // setze Alkohol Status auf aktiv
                status_filter = statusFilter::alcohol;
            }
            pe++;
        }
    }
    playeventsnumber = playevents.size();

    // unlock mutex
    mtx.unlock();
}


/**
 * @brief  playInitialize initialisiert die Abspielbibliothek Portaudio, öffnet einen PortAudio Stream und startet eine Callback Audiowiedergabe
 * @author  Felix Pfreundtner
 */
void AudioControl::playInitialize(){
    // initialisiere Port Audio
    paerror = Pa_Initialize();
    if(paerror != paNoError && paerror !=0) {
       fprintf(stderr, "Ein Error trat während der Benutzung der PortAudio Ausgabe auf\n" );
       fprintf(stderr, "Error Nummer: %d\n", paerror);
       fprintf(stderr, "Error Nachricht: %s\n", Pa_GetErrorText(paerror));
    }

    // Öffene Ausgabe Stream pastream
    paerror = Pa_OpenDefaultStream (&pastream,
                                    0,          // erstelle keine Eingangskänale
                                    1,          // erstelle Mono Audio Ausgabe
                                    paInt16,  // setze Bittiefe der Audioausgabe 16 bit Integer
                                    SAMPLERATE, // setze Samplerate der Audioausgabe zu 44100 Hz
                                    BLOCKSIZE, // setze Anzahl an Samples per Bufferblock auf 1024
                                    &AudioControl::staticpaCallback, // verweise auf Statistische Callback Methode
                                    this); // übergebe User-Data
    if(paerror != paNoError && paerror != 0) {
       fprintf(stderr, "Ein Error trat während der Benutzung der PortAudio Ausgabe auf\n" );
       fprintf(stderr, "Error Nummer: %d\n", paerror);
       fprintf(stderr, "Error Nachricht: %s\n", Pa_GetErrorText(paerror));
    }

    // Starte PortAudio Stream pastream
    paerror = Pa_StartStream(pastream);
    if(paerror != paNoError && paerror != 0) {
       fprintf(stderr, "Ein Error trat während der Benutzung der PortAudio Ausgabe auf\n" );
       fprintf(stderr, "Error Nummer: %d\n", paerror);
       fprintf(stderr, "Error Nachricht: %s\n", Pa_GetErrorText(paerror));
    }

    // Pausiere Methode wenn Audiostream gerade aktiv ist (Audiowiedergabe übernimmt Callback Methode)
    while (Pa_IsStreamActive(pastream) == 1) {
        Pa_Sleep(waitinms);
        // std::this_thread::sleep_for(std::chrono::milliseconds(waitnms)); Ersatz für sleep() ?
    }
}


/**
 * @brief  instancepaCallback wird von Portaudio aufgerufen wenn der letze Audioblock abgespielt wurde und ein neuer Ausgabe Audioblock geniert werden muss.
 * @param  const void *inputBuffer
 * @param  void *outputBuffer
 * @param  unsigned long framesPerBuffer,
 * @param  const PaStreamCallbackTimeInfo* timeInfo,
 * @param  PaStreamCallbackFlags statusFlags
 * @return  int returncode
 * @author  Felix Pfreundtner
 */
int AudioControl::instancepaCallback(
                           const void *inputBuffer,
                           void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags ) {
    /* Cast data passed through stream to our structure. */
    // erstelle Zeiger *out auf outputBuffer
    short *out = (short*)outputBuffer;
    // kein Input aktiviert, verhindere Warnmeldung "unbenutzter Parameter inputBuffer"
    (void) inputBuffer;
    // keine timeInfo nötig, verhindere Warnmeldung "unbenutzter Parameter inputBuffer"
    (void) timeInfo;
    // keine statusFlags nötig, verhindere Warnmeldung "unbenutzter Parameter statusFlags"
    (void) statusFlags;

    // lock mutex
    mtx.lock();
    for(unsigned int block_pos=0; block_pos<framesPerBuffer; block_pos++ ) {

        // Berechne Sample Ausgabe für aktuellen Blockwert aus Samples aller Audiovents
        mixed_sample = 0;
        // für alle aktuell abzuspielenden Audioevents
        for (std::list<playStruct>::iterator pe = playevents.begin(); pe != playevents.end(); pe++) {
            // mixed:sample_keinfilter = sample(aktuell Position Audioevent)*aktuelle_relative_lautstärke_audioevent/anzahl_maximaler_playevents
            mixed_sample += pe->audioobject->getSample(pe->position) * pe->volume / max_playevents;

            // wähle aktuell anzuwenden Filter aus
            switch (status_filter) {
                // keinen Filter anwenden
                case statusFilter::no:
                // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                    pe->position += 1;
                    break;

                // Alkohol Filter anwenden
                // Verzögere den Spielsound im Zeitbereich um 1 Sample pro Schritt (50% Verzögerung)
               // für alle Audio Typen außgenommen status_alcohol
                case statusFilter::alcohol:
                    if (pe->type == status_alcohol) {
                        // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                        pe->position += 1;
                        }
                    else {
                        // falls Blockposition gerade ist
                        if(block_pos % 2 != 0) {
                            // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                            pe->position += 1;
                         }
                    }
                    break;

                // Wenig Leben Filter anwenden
                // Erhöhe den Spielsound im Zeitbereich um 1 Sample pro Schritt (50% Geschwindigkeitszunahme)
                // für Audio Typen player_walk, scene_enemy_boss und status_lifecritical
                case statusFilter::lifecritical:
                    if (pe->type == player_walk || pe->type == scene_enemy_boss || pe->type == status_lifecritical) {
                        // erhöhe Abspielposition des aktuell iterierten Audiovents um zwei Samples
                        pe->position += 2;
                        }
                    else {
                        // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                        pe->position += 1;
                         }
                    break;
            }

            // falls Samples Position des aktuell iterierten Audiovents Anzahl an Samples in Audioobject überschreitet
            if (pe->position >= pe->audioobject->getSamplenumber()) {
                // Loope Audiosignal -> setzte Samples Position auf Anfang zurück (pos = position-samplenumber)
                pe->position = pe->position - pe->audioobject->getSamplenumber();
            }
        }
        // Füge gemischtes Samples aller Audiovents dem PortAudio Outputbuffer hinzu und Erhöhe Zeiger auf den Outputbuffer um 16bit
        *out++ = mixed_sample;
    }

    // unlock mutex
    mtx.unlock();
    blockcounter += 1;    
    int returncode = 0;
    return returncode;
}

/**
 * @brief  playTerminate stoppt bei Aufruf die PortAudio Audioausgabe, beendet im Anschluss den Portaudio Stream und beendet zuletzt PortAudio.
 * @author  Felix Pfreundtner
 */
void AudioControl::playTerminate(){

    // Stoppe den Portaudio Stream
    paerror = Pa_StopStream(pastream);
    if(paerror != paNoError && paerror != 0) {
        fprintf(stderr, "Ein Error trat während der Benutzung der PortAudio Ausgabe auf\n" );
        fprintf(stderr, "Error Nummer: %d\n", paerror);
        fprintf(stderr, "Error Nachricht: %s\n", Pa_GetErrorText(paerror));
    }
    // Schließe den Portaudio Stream
    paerror = Pa_CloseStream(pastream);
    if(paerror != paNoError && paerror != 0) {
        fprintf(stderr, "Ein Error trat während der Benutzung der PortAudio Ausgabe auf\n" );
        fprintf(stderr, "Error Nummer: %d\n", paerror);
        fprintf(stderr, "Error Nachricht: %s\n", Pa_GetErrorText(paerror));
    }
    // Beende PortAudio
    paerror = Pa_Terminate();
    if(paerror != paNoError && paerror != 0) {
        fprintf(stderr, "Ein Error trat während der Benutzung der PortAudio Ausgabe auf\n" );
        fprintf(stderr, "Error Nummer: %d\n", paerror);
        fprintf(stderr, "Error Nachricht: %s\n", Pa_GetErrorText(paerror));
    }
}

