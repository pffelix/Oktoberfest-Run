#include "audio.h"

/**
 * @brief  Audio::Audio
 *         Konstruktor instanziert ein Objekt der Klasse Audio.
 * @author  Felix Pfreundtner
 */
Audio::Audio(QString state_name) {
    source = state_name;
    readSamples();
    qDebug("Audio object created");

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
 * @return QVector<float> samples
 * @author Felix Pfreundtner
 */
QVector<float> Audio::getSamples() {
    return samples;
}

/**
 * @brief  Audio::getSamplenr
 *         "getSamplenr" gibt bei Aufruf die Anzahl an Samples der zu Audioobjekt
 *         gehörigen Wave Datei zurück.
 * @return int samplenr
 * @author Felix Pfreundtner
 */
int Audio::getSamplenr() {
    return samplenr;
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
 *         Die Bittiefe ist hierbei variabel 8 oder 16bit.
 *         Es greift hierfür auf die zum Objekt gehörige, in der
 *         Ressourcendatenbank gespeicherte Wave Datei mit Pfadnamen
 *         "source" zurück.
 *         Die Funktion wertet den fmt Header des Wave File aus und liest im
 *         Anschluss den data Chunk ein.
 *         Die Bittiefe wird in float konvertiert um eine Weiterbearbeitung der Samples ohne Dynamikverlust durchführen zu können.
 * @author Felix Pfreundtner
 */
void Audio::readSamples() {

    QString sourcepath; /// Pfad zur Wave Datei in den Ressourcendateien
    int channels; /// Anzahl an Kanälen
    int bitdepth; /// Anzahl an Bits pro Sample
    int bytedepth; /// Anzahl an Bytes pro Sample
    char* tempbytes; /// variable to save unused bytes
    int offset; /// variable to save current offset position in file

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
        //// lese den Namen des Headers des nächsten Chunks aus
        file.read(tempbytes, 4);
    }

    /// Data chunk erreicht

    //qDebug() << QString::fromStdString(std::string(tempbytes));
     /// lese die Größe des data chunks in Bytes aus
    file.read(tempbytes, 4);
    /// berechene die Gesamtanzahl an Samples in der Datei
    samplenr = (qFromLittleEndian<quint32>((uchar*)tempbytes)) * 8 / bitdepth / channels;
    /// lese Sample für Sample aus dem data chunk aus
    while(!file.atEnd()){
        file.read(tempbytes, bytedepth);
        /// lese 16 bit integer Samples in float QVector ein
        if (bytedepth == 2) {
            samples << qFromLittleEndian<qint16>((uchar*)tempbytes);
        }
        /// lese 8 bit integer Samples in float QVector ein
        else {
            samples << to16bitSample(qFromLittleEndian<quint8>((uchar*)tempbytes));
        }
    }
    // normalisiere QVector samples auf die maximalen 16 bit signed integer Grenzen (hier: -32767...32767)
    normalize();
}


/**
 * @brief  Audio::readSamples
 *         "readSamples" konvertiert einen 8 bit integer Sample in einen 16 bit Integer Sample.
 *         Ziel ist eine einheitlich Bearbeitung der Samples verschiedener Audioobjekte vornehmen zu können.
 * @author Felix Pfreundtner
 */
qint16 Audio::to16bitSample(quint8 sample8bit) {
    qint16 sample16bit;
    // rechne unsigend integer 8 bit in signed integer 16 bit um und skaliere in an die 16bit signed integer grenzen
    sample16bit = (sample8bit - 128) * 256;
    return sample16bit;
}

/**
 * @brief  Audio::normalize
 *         "normalize" normalisiert den 16 bit Integer QVector samples.
 *         Es wird hierfür die größte Betrag-Amplitude eines Sample in samples bestimmt.
 *         Diese Amplitude wird auf den maximalen signed Integer 16 Bit Wert gesetzt (hier: -32767 oder 32767).
 *         Alle anderen Samples werden entsprechend ihres Verhältnises zur größten Betrag-Amplitude skaliert.
 * @author Felix Pfreundtner
 */
void Audio::normalize() {
    // maxabs speichert die großte Betrag-Amplitude eines Samples aus sample
    int maxabs;
    // maxabs speichert die Betrag-Amplitude des aktuell iterierten Samples aus sample
    int maxabspos;

    maxabs = 0;
    // iteriere über alle Samples in samples
    for (int pos = 0; pos < samples.size(); pos++) {
        maxabspos = abs(samples[pos]);
        // ween die Betrag-Amplitude an pos größer ist als die voherigen Betrag-Amplituden speichere sie in maxabs
        if (maxabspos > maxabs) {
            maxabs = maxabspos;
        }
    }
    // normalisiere den QVector samples auf maximale signed Integer 16bit Grenzen
    // iteriere über alle Samples in samples
    for (int pos = 0; pos < samples.size(); pos++) {
        samples[pos] = samples[pos] / maxabs * 32767;
    }
}
