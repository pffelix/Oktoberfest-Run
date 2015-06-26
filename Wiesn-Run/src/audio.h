#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <vector>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QtEndian>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <string>
#include <QVector>


/**
 * @brief  Audio-Klasse
 *         Die Audio-Klasse erzeugt Audioobjekte.
 *         Mehrere Instanzen dieser Klasse werden in der Klasse AudioControl erstellt.
 *         Jedes Audioobjekt liest die zum Ojekt gehörigen Audiosamples ein und übergibt diese an die Kontrollklasse
 *         Audiocontrol, welche im Anschluss die Samples aller Objekte mischt und abspielt.
 *         Die einzelnen Methoden werden in der audio.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class Audio{

public:
    Audio(std::string state_name);
    ~Audio();

    std::string getSource();
    float getSample(int pos);
    int getSamplenbr();
    short getVolume();
    void setVolume(short volume_audio_obj);

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
     *         samples speichert die normalisierten samples des Audio
     *         Objekts als QVektor mit 32 bit float Werten.
     * @author  Felix Pfreundtner
     */
    QVector<float> samples;
    /**
     * @brief  samplenbr
     *         samplenbr speichert die Anzahl an Samples in der gesamten Audio Datei
     *         des Audio Objekts als Integer.
     * @author  Felix Pfreundtner
     */    
    int samplenbr;
    /**
     * @brief  volume
     *         volume speichert die Lautstärkeinformation des Audioobjektes (Bereich 0...1).
     * @author  Felix Pfreundtner
     */
    short volume;

    void readSamples();
    qint16 to16bitSample(quint8 sample8bit);
    void normalize();    
protected:
};

#endif // AUDIO_H
