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

    QString sourcepath; /// Pfad zur Wave Datei in den Ressourcendateien
    int channels; /// Anzahl an Kanälen
    int bitdepth; /// Anzahl an Bits pro Sample
    int bytedepth; /// Anzahl an Bytes pro Sample
    int samplenr; /// Anzahl an Samples in der gesamten Audio Datei
    char* tempbytes; /// variable to save unused bytes
    int offset; /// variable to save current offset position in file
    QVector<int> sampledata;

    /// Öffne zum Audio Objekt gehörige Wave Datei
    sourcepath = ":/audios/audios/" + source + ".wav";
    QFile file(sourcepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    /// Lese relevante Informationen aus dem fmt chunk

    /// lese Anzahl an Kanälen ein (Offset 22 Byte)
    file.seek(22);
    file.read(tempbytes, 2);
    channels = qFromLittleEndian<quint16>((uchar*)tempbytes);
    /// lese die Anzahl an Bits pro Sample ein (Offset 34 Byte)
    file.seek(34);
    file.read(tempbytes, 2);
    bitdepth = qFromLittleEndian<quint16>((uchar*)tempbytes);
     /// Berechne die Anzahl an Bytes pro Sample
    bytedepth = bitdepth / 8;

    /// Bei Offset 36 Ende des ftm chunks erreicht
    /// Suche nun nach dem data Header

    offset = 36; /// aktueller Offset
     /// Lese den Header des chunks am Offset 36 Byte
    file.read(tempbytes, 4);
    /// Prüfer ob der header des aktuellen chunks bereits dem header des data chunks entspricht
    while (tempbytes[0]!='d' && tempbytes[1]!='a' && tempbytes[2]!='t' && tempbytes[3]!='a') {
        /// falls nicht:
        /// lese die Größe in Bytes des Chunks
        file.read(tempbytes, 4);
        /// springe zum nächsten Chunk
        offset += qFromLittleEndian<quint32>((uchar*)tempbytes)+8;
        file.seek(offset);
        //qDebug() << QString::number(offset);
        //// lese den Namen des Headers des nächsten Chunks aus
        file.read(tempbytes, 4);
    }

    /// Data chunk erreicht

    //qDebug() << QString::fromStdString(std::string(tempbytes));
     /// lese die Größe des data chunks in Bytes aus
    file.read(tempbytes, 4);
    /// berechene die Gesamtanzahl an Samples in der Datei
    samplenr = (qFromLittleEndian<quint32>((uchar*)tempbytes)) * 8 / bitdepth / channels;
    /// lese die Samples aus dem data chunk aus
    while(file.atEnd() != true){
        file.read(tempbytes, bytedepth);
        sampledata << (qFromLittleEndian<qint16>((uchar*)tempbytes));
    }
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
