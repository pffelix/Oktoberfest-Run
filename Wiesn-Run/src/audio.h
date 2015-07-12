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
 * @brief  Die Audio-Klasse erzeugt Audioobjekte. Für jeden Audioobjekt Typ mit Name type_name wird zu Beginn eine Instanz der Klasse erstellt und in AudioControl an die Liste audioobjects angehängt. Jedes Audioobjekt liest die zum Objekt Typ gehörigen Audiosamples aus einer WAVE Datei ein und übergibt das Sample an Position pos per Aufruf mit getSample(int pos) an den Aufrufer.
 * @author  Felix Pfreundtner
 */
class Audio{

public:

    // Funktionen
    Audio(std::string type_name);
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
     * @var  std::string source
     * @brief  source speichert den Namen des Audioobjekts als string welcher dem Dateinamen der zugehörigen Wave Datei entspricht.
     */
    std::string source;

    /**
     * @var std::vector<float> samples
     * @brief samples speichert die normalisierten samples des Audio Objekts als QVektor mit 32 bit float Werten.
     */
    std::vector<float> samples;
    /**
     * @var  int samplenumber
     * @brief samplenumber speichert die Anzahl an Samples in der gesamten Audio Datei des Audio Objekts als Integer.
     */    
    int samplenumber;

};

#endif // AUDIO_H
