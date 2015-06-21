#include "audio.h"

/**
 * @brief  Audio::Audio
 *         Konstruktor instanziert ein Objekt der Klasse Audio.
 * @author  Felix Pfreundtner
 */
Audio::Audio(QString state_name) {
    source = state_name;
    readSamples();

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
 * @return QVector<int> samples
 * @author Felix Pfreundtner
 */
QVector<int> Audio::getSamples() {
    return samples;
}

/**
 * @brief  Audio::getSource
 *         "getSource" gibt bei Aufruf den Namen des Objektes zurück welcher
 *         welcher dem Pfad in der Ressourcendatenbank entspricht.
 * @return QString source
 * @author Felix Pfreundtner
 */
QString Audio::getSource() {
    return source;
}

/**
 * @brief  Audio::readSamples
 *         "readSamples" liest bei Aufruf alle Samples der zu Audioobjekt
 *         gehörigen Wave Datei in die Variable "samples" ein.
 *         Eingelesen werden sollen RIFF Mono Wave Dateien mit 44100Hz Samplerate.
 *         Es greift hierfür auf die zum Objekt gehörige, in der
 *         Ressourcendatenbank gespeicherte Wave Datei mit Pfadnamen
 *         "source" zurück.
 *         Die Funktion wertet den Format Header des Wave File aus und liest im
 *         Anschluss den file Chunk ein.
 *         Bittiefe und Dynamik entsprechen der orginalen Wave Datei.
 * @author Felix Pfreundtner
 */
void Audio::readSamples() {
    QString sourcepath;
    sourcepath = ":/audios/audios/" + source + ".wav";
    QFile file(sourcepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "unable to open audio " << source;
    }
    else {
        qDebug() << "open audio " << source;
    }


    int channels; //number of channels
    int bitdepth; // number of bits per sample
    int samplenr; // number of samples of audio file
    int bytedepth; // number of bytes per sample
    char* tempbytes; // variable to save unused bytes
    int offset; // variable to save current offset position in file
    QVector<int> sampledata;

    // read relevant info from fmt chunk
    file.seek(22);
    file.read(tempbytes, 2);// read number of channels (offset 22 byte)
    channels = qFromLittleEndian<quint16>((uchar*)tempbytes);

    file.seek(34);
    file.read(tempbytes, 2);// read number of bits per sample (offset 34 byte)
    bitdepth = qFromLittleEndian<quint16>((uchar*)tempbytes);

    // end of fmt header - searching for data header
    offset = 36; // set current offset
    file.read(tempbytes, 4); // read header of subchunk at offset 36 byte

    // check whether data header doesn't follow directly to fmt header
    while (tempbytes[0]!='d' && tempbytes[1]!='a' && tempbytes[2]!='t' && tempbytes[3]!='a') {
        // read size of subchunk
        file.read(tempbytes, 4);
        // skip to next subchunk
        offset += qFromLittleEndian<quint32>((uchar*)tempbytes)+8;
        file.seek(offset);
        qDebug() << QString::number(offset);
        // read name of subchunk
        file.read(tempbytes, 4);
    }
    qDebug() << QString::fromStdString(std::string(tempbytes));
    // read samples from data chunk
    file.read(tempbytes, 4); // read size of data chunk
    samplenr = (qFromLittleEndian<quint32>((uchar*)tempbytes)) * 8 / bitdepth / channels; // calculate number of samples
    bytedepth = bitdepth / 8; // calculate number of bytes per sample
    while(file.atEnd() != true){
        file.read(tempbytes, bytedepth);
        sampledata << (qFromLittleEndian<qint16>((uchar*)tempbytes));
    }
    qDebug ("stop");
}

/**
 * @brief  Audio::readSamples
 *         "readSamples" konvertiert die eingelesen Samples auf das Audioformat
 *         Kanäle: 1, Samplerate: 44100 Hz, Bittiefe: 16 bit um eine gemeinsame
 *         Bearbeitung der Samples verschiedener Audioobjekte in der Klasse
 *         Audiocontrol vornehmen zu können.
 * @author Felix Pfreundtner
 */
void Audio::to16bitnormSamples() {

}
