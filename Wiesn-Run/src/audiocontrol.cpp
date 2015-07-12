#include "audiocontrol.h"
#include "portaudio.h"

/**
 * @brief  Konstruktor instanziert ein Objekt der Klasse AudioControl.
 * @author  Felix Pfreundtner
 */
AudioControl::AudioControl() {

    // erstelle für jede objektgruppe "type" ein audio Objekt welches unter anderem die Samples beinhaltet
    audioobjects.reserve(23);
    //source: http://soundbible.com/1247-Wind.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_flyingbeer, Audio("scene_flyingbeer")); // 16bit
    //source: http://www.freesound.org/people/Reitanna/sounds/241215/
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_tourist, Audio("scene_enemy_tourist")); // 16bit
    //source: http://www.freesound.org/people/Robinhood76/sounds/195414/
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_security, Audio("scene_enemy_security")); // 16bit
    //source: http://soundbible.com/1501-Buzzer.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_enemy_boss, Audio("scene_enemy_boss")); // 16bit
    //source: http://soundbible.com/1522-Balloon-Popping.html
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_obstacle, Audio("scene_collision_obstacle")); // 16bit
    //source: http://www.freesound.org/people/qubodup/sounds/169725/
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_enemy, Audio("scene_collision_enemy")); // 16bit
    //source: http://www.freesound.org/people/thecheeseman/sounds/44430/
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_player, Audio("scene_collision_player")); // 16bit
    //source: http://helios.augustana.edu/~dr/105/wav/glasbk.wav
    audioobjects.insert(audioobjects.begin() + audioType::scene_collision_flyingbeer, Audio("scene_collision_flyingbeer")); // 16bit
    //source: http://www.freesound.org/people/edhutschek/sounds/215634/
    audioobjects.insert(audioobjects.begin() + audioType::powerup_beer, Audio("powerup_beer")); // 16bit
    //source: https://www.freesound.org/people/bassboybg/sounds/264544/
    audioobjects.insert(audioobjects.begin() + audioType::powerup_food, Audio("powerup_food")); // 16bit
    //source: http://www.freesound.org/people/afleetingspeck/sounds/151180/
    audioobjects.insert(audioobjects.begin() + audioType::status_alcohol, Audio("status_alcohol")); // 16bit
    // source: http://soundbible.com/1612-Slow-HeartBeat.html
    audioobjects.insert(audioobjects.begin() + audioType::status_life, Audio("status_life")); // 16bit
    //source: http://soundbible.com/1707-Hearbeat-2.html
    audioobjects.insert(audioobjects.begin() + audioType::status_lifecritical, Audio("status_lifecritical")); // 16bit
    //source: http://www.freesound.org/people/Robinhood76/sounds/256469/
    audioobjects.insert(audioobjects.begin() + audioType::status_dead, Audio("status_dead")); // 16bit
    //source: http://www.arts.rpi.edu/public_html/ruiz/VES01/sebram/final/walk_crop.wav
    audioobjects.insert(audioobjects.begin() + audioType::player_walk, Audio("player_walk")); // 16bit
    //source: http://soundbible.com/266-Boing-Cartoonish.html
    audioobjects.insert(audioobjects.begin() + audioType::player_jump, Audio("player_jump")); // 16bit
    //source: http://www.theholidayspot.com/oktoberfest/music/Octoberfest%20--%20Beerdrinking%20song%28Bavarian%29.wma
    audioobjects.insert(audioobjects.begin() + audioType::background_menu, Audio("background_menu")); // 16bit
    //source: http://soundbible.com/1563-Pacman-Introduction-Music.html
    audioobjects.insert(audioobjects.begin() + audioType::background_highscore, Audio("background_highscore")); // 16bit
    //source: http://soundbible.com/1763-Ambience-Casino.html
    audioobjects.insert(audioobjects.begin() + audioType::background_level1, Audio("background_level1")); // 16bit
    //source: http://www.freesound.org/people/Kyster/sounds/122789/
    audioobjects.insert(audioobjects.begin() + audioType::background_level2, Audio("background_level2")); // 16bit
    //source: http://www.freesound.org/people/Westmed/sounds/239538/
    audioobjects.insert(audioobjects.begin() + audioType::background_level3, Audio("background_level3")); // 16bit
    //source: http://www.freesound.org/people/Harbour11/sounds/194625/
    audioobjects.insert(audioobjects.begin() + audioType::background_startgame, Audio("background_startgame")); // 16bit
    //source: http://soundbible.com/1823-Winning-Triumphal-Fanfare.html
    audioobjects.insert(audioobjects.begin() + audioType::background_levelfinished, Audio("background_levelfinished")); // 16bit

    // setzte Status Filter auf kein Filter
    status_filter = statusFilter::no;
    // setzte blockcounter auf 0 Blöcke
    blockcounter = 0;
    // setzte Wartezeit von Portaudio auf 100 ms
    waitinms = 100;
    // setzte maximale Anzahl an Playevents auf 5
    // Wird der Wert höher gesetzt wird die Lautstärke geringer.
    // Wird der Wert geringer gesetzt steigt die Gefahr des Clippings des Ausgabesignals
    // Ein Normalisieren aller Ausgabeblöcke wäre möglich, würde jedoch 2D Audio nicht erlauben,
    // da auch die Dynamik zwischen zwei Blöcken normalisiert wird
    // -> Distanz- und somit Lautstärkeänderungen von Objekten werden mit normalisiert.
    max_playevents = 5;

}


/**
 * @brief  Destruktor löscht ein Objekt der Klasse AudioControl
 * @author  Felix Pfreundtner
 */
AudioControl::~AudioControl() {

}

/**
 * @brief  updatePlayevents aktualsiert nach Aufruf über Game::step alle im Moment abgespielten, in der Liste "playevents" gespeicherten playStruct's mit aktuellen audioStruct's aus der übergebenen Liste audioevents.
 * @param  Qlist audioevents
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
    // lock audioevents
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
            // falls Type des aktuellen playevents status_alcohol ist (niedrige Priorität)
            if (pe->type == status_alcohol) {
                // setze Alkohol Status auf aktiv
                status_filter = statusFilter::alcohol;
            }
            // falls Type des aktuellen playevents status_life ist (mittlere Priorität)
            if (pe->type == status_life) {
                // setze Alkohol Status auf aktiv
                status_filter = statusFilter::life;;
            }
            // falls Type des aktuellen playevents status_lifecritical ist (höchste Priorität)
            if (pe->type == status_lifecritical) {
                // setze Alkohol Status auf aktiv
                status_filter = statusFilter::lifecritical;
            }
            pe++;
        }
    }
    playeventsnumber = playevents.size();
    //qDebug() << QString("Filter Status: ") << QString::number(status_filter);
    for (pe = playevents.begin(); pe != playevents.end(); pe++) {
        //qDebug() << QString("Audio played: ") << QString::fromStdString(pe->audioobject->getSource());
    }
    // unlock audioevents
    mtx.unlock();
}


/**
 * @brief  playInitialize initialisiert die Abspielbibliothek Portaudio, öffenet den PortAudio Stream pastream und startet eine Callback Audiowiedergabe
 * @param  Qlist audioevents
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
                                    &AudioControl::staticpaCallback, // verweise auf Static Callback Funktion
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

    // Pausiere Funktion wenn Audiostream gerade aktiv ist (Audiowiedergabe übernimmt Callback Funktion)
    while (Pa_IsStreamActive(pastream) == 1) {
        Pa_Sleep(waitinms);
        // std::this_thread::sleep_for(std::chrono::milliseconds(waitnms)); Ersatz für sleep() ?
    }
}


/**
 * @brief  playCallback wird von Portaudio aufgerufen wenn nahezu alle Audiosamples abgespielt sind und neu Audiosamples benötigt werden.
 * @param  Qlist audioevents
 * @author  Felix Pfreundtner
 */
int AudioControl::instancepaCallback( const void *inputBuffer, void *outputBuffer,
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

    // lock audioevents
    mtx.lock();
    for(unsigned int block_pos=0; block_pos<framesPerBuffer; block_pos++ ) {

        // Berechne Sample Ausgabe für aktuellen Block Zeitschritt aus Samples aller Audiovents
        mixed_sample = 0;
        // für alle aktuell abzuspielenden Audioevents
        for (std::list<playStruct>::iterator callback_pe = playevents.begin(); callback_pe != playevents.end(); callback_pe++) {
            // lese Sample für aktuelles Audioevent and aktuell iterierter Position ein
            // mixed:sample_keinfilter = sample(aktuell Position Audioevent)*aktuelle_relative_lautstärke_audioevent/anzahl_maximaler_playevents
            mixed_sample += callback_pe->audioobject->getSample(callback_pe->position) * callback_pe->volume / max_playevents;
            // wähle aktuell anzuwenden Filter aus
            // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
            callback_pe->position += 1;
            /**
            switch (status_filter) {
                // kein Filter anwenden
                case 9:

                    break;

                // Alkohol Filter anwenden
                // Verzögere das Audiosignal im Zeitbereich um 1 Sample in jedem Schritt
                case 10:
                    // falls Blockposition gerade ist
                    if(block_pos % 2 == 0) {
                        // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                        callback_pe->position += 1;
                    }
                    break;

                // Wenig Leben Filter anwenden
                // Schwanke die Lautstärke im Zeitbereich mit 1Hz Cosinus Schwingung
                // mixed_sample = mixed:sample_keinfilter * 1Hz_Lautstärke_Cosinus_Filter
                // 1Hz_Lautstärke_Cosinus_Filter = Betrag [cos(2 * pi * 1 / 44100 * (Anzahl bisher abgespielte Blöcke * 1024 + Position im Callback Block))]
                case 11:
                    mixed_sample += mixed_sample*std::abs(std::cos(2 * M_PI * 1 /44100 *(blockcounter * BLOCKSIZE + block_pos)));
                    // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                    callback_pe->position += 1;
                    break;

                // Sehr wenig Leben Filter anwenden
                // Schwanke die Lautstärke im Zeitbereich mit 5Hz Cosinus Schwingung
                // mixed_sample = mixed:sample_keinfilter * 5Hz_Lautstärke_Cosinus_Filter
                // 5Hz_Lautstärke_Cosinus_Filter = |cos(2 * pi * 0 / 44100 * (Anzahl bereitsabgespielte Blöcke * 1024 + aktuelle Position Callback Block))|
                case 12:
                    mixed_sample += mixed_sample * std::cos(2 * M_PI * 5 /44100 *(blockcounter * BLOCKSIZE + block_pos));
                    // erhöhe Abspielposition des aktuell iterierten Audiovents um ein Sample
                    callback_pe->position += 1;
                    break;
            }
             */
            // falls Samples Position des aktuell iterierten Audiovents Anzahl an Samples in Audioobject überschreitet
            if (callback_pe->position >= callback_pe->audioobject->getSamplenumber()) {
                // Loope Audiosignal -> setzte Samples Position auf Anfang zurück (pos = position-samplenumber)
                callback_pe->position = callback_pe->position - callback_pe->audioobject->getSamplenumber();
            }
        }
        // Füge gemischtes Samples aller Audiovents dem PortAudio Outputbuffer hinzu und Erhöhe Zeiger auf den Outputbuffer um 16bit
        *out++ = mixed_sample;
    }

    // unlock audioevents
    mtx.unlock();
    blockcounter += 1;
    //std::copy ( block, block + BLOCKSIZE, std::back_inserter ( blockcontinue ) );
    return 0;
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

