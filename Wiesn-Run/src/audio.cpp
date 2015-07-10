#include "audio.h"

/**
 * @brief  Audio::Audio
 *         Konstruktor instanziert ein Objekt der Klasse Audio.
 * @author  Felix Pfreundtner
 */
Audio::Audio(std::string state_name) {
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
 * @brief  Audio::getSource
 *         "getSource" gibt bei Aufruf den Namen des Objektes zurück welcher
 *         welcher dem Pfad in der Ressourcendatenbank entspricht.
 * @return std::string source
 * @author Felix Pfreundtner
 */
std::string Audio::getSource() {
    return source;
}

/**
 * @brief  Audio::getSample
 *         "getSample" gibt bei Aufruf das Sample an Position = pos der zu Audioobjekt
 *         gehörigen Wave Datei mit Bittiefe 16 bit zurück.
 * @return float sample
 * @author Felix Pfreundtner
 */
float Audio::getSample(int pos) {
        /// gebe Sample des Audioobjekts an der Stelle pos zurück
        return samples[pos];
}

/**
 * @brief  Audio::getSamplenumber
 *         "getSamplenumber" gibt bei Aufruf die Anzahl an Samples der zu Audioobjekt
 *         gehörigen Wave Datei zurück.
 * @return int samplenumber
 * @author Felix Pfreundtner
 */
int Audio::getSamplenumber() {
    return samplenumber;
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
    std::string sourcepath; /// Pfad zur Wave Datei in den Ressourcendateien
    QDir buildpath; /// Pfad zum Ordner der Build (Exe Datei)
    int folderchanges; /// Anzahl gewechselter Ordner
    std::string errormessage; /// Error Nachricht wenn Ordner mit Audiodateien nicht gefunden werden kann
    int channels; /// Anzahl an Kanälen
    int bitdepth; /// Anzahl an Bits pro Sample
    int bytedepth; /// Anzahl an Bytes pro Sample
    char tempbytes[5]; /// variable aktuell ausgelesene Bytes der Wave Datei zwischenzuspeichern
    int offset; /// Variab um aktuelle Byte Position in Wave Datei zu speichern

    /// Installationspfad des Audioordners über make install ist Betriebssystem abhängig
    /// wenn installierte Audio Dateiein nicht in Build Verzeichnis auffindar sind wechsel ein Verzeichnis höher und suche dort erneut
    buildpath = QDir(QCoreApplication::applicationDirPath());
    folderchanges = 0;
    while(buildpath.cd(QString("audios")) == false) {
        buildpath.cdUp();
        folderchanges += 1;
        if (folderchanges > 2) {
        errormessage = "Folder with audio files could not be found in: \n" + QCoreApplication::applicationDirPath().toStdString() + "/audios" + "\n 1. please add commando param 'install' to qmake.exe and compile again \n 2. please delete build folder and compile again \n 3. please use just alphabetic letters in path name of build folder and sources folder \n 4. if this is not working copy audio files manually from sources to the above named folder and compile again" ;
        qFatal(errormessage.c_str());
        }
    }

    /// Öffne zum Audio Objekt gehörige Wave Datei
    sourcepath = buildpath.absolutePath().toStdString() + "/" + source + ".wav";
    QFile file(QString::fromStdString(sourcepath));
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Audio::readsamples: Cannot open File" << QString::fromStdString(source);
        return;
    }
    else {
        qWarning() << "Audio::readsamples: loaded File" << QString::fromStdString(source);
    }

    /// Lese relevante Informationen aus dem fmt chunk

    /// lese Anzahl an Kanälen ein (Offset 22 Byte)
    file.seek(22);
    file.read(tempbytes, 2);        // ERROR unter Linux (Segmentation Fault)
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

     /// lese die Größe des data chunks in Bytes aus
    file.read(tempbytes, 4);
    /// berechene die Gesamtanzahl an Samples in der Datei
    samplenumber = (qFromLittleEndian<quint32>((uchar*)tempbytes)) * 8 / bitdepth / channels;
    /// lese Sample für Sample aus dem data chunk aus
    while(!file.atEnd()){
        file.read(tempbytes, 2);
        /// lese 16 bit integer Samples in float QVector ein
        if (bytedepth == 2) {
            samples.push_back(qFromLittleEndian<qint16>((uchar*)tempbytes));
        }
        /// lese 8 bit integer Samples in float QVector ein
        else {
            samples.push_back(to16bitSample(qFromLittleEndian<quint8>((uchar*)tempbytes)));
        }
    }
    /// schließe Audiodatei
    file.close();
    /// normalisiere QVector samples auf die maximalen 16 bit signed integer Grenzen (hier: -32767...32767)
    normalize();

}

/**
 * @brief  Audio::to16bitSample
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
 * @todo controll whether working
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
    if (maxabs != 0) {
        for (int pos = 0; pos < samples.size(); pos++) {
            samples[pos] = samples[pos] / maxabs * 32767;
        }
    }
}
