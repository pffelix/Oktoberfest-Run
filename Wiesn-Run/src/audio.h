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
#include <QCoreApplication>
#include <QDir>
#include <QtGlobal>

/**
 * @brief  Die Audio-Klasse erzeugt Audioobjekte. Mehrere Instanzen dieser Klasse werden in der Klasse AudioControl erstellt. Jedes Audioobjekt liest die zum Ojekt gehörigen Audiosamples ein und übergibt diese an die Kontrollklasse. Audiocontrol, welche im Anschluss die Samples aller Objekte mischt und abspielt. Die einzelnen Methoden werden in der audio.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class Audio{

public:

    // Funktionen
    Audio(std::string state_name);
    ~Audio();
    std::string getSource();
    float getSample(int pos);
    int getSamplenumber();

private:

    // Funktionen
    void readSamples();
    qint16 to16bitSample(quint8 sample8bit);
    void normalize();

    // Variablen
    /**
     * source speichert den namen des aktuellen objekts als string welcher dem namen im ressourcenpfad entspricht.
     */
    std::string source;

    /**
     * samples speichert die normalisierten samples des Audio Objekts als QVektor mit 32 bit float Werten.
     */
    std::vector<float> samples;
    /**
     * samplenumber speichert die Anzahl an Samples in der gesamten Audio Datei des Audio Objekts als Integer.
     */    
    int samplenumber;

};

#endif // AUDIO_H
