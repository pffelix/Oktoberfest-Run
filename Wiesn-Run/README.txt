Wiesn-Run Readme

Hinweise zum Kompilieren unter Linux
Unter Linux muss zum Kompilieren die Audiobibliothek Portaudio vorhanden sein. Genau genommen sollte es die Version 19+svn20111121-1 sein. Unter Debian/Ubuntu genügt es, das Paket portaudio19-dev zu installieren.

Da die verwendeten Audiodateien in den build-Ordner kopiert werden müssen, bedarf es einer kleinen Änderung des build-Schritts "Make". Bitte im QTCreator beim build-Schritt "Make" das Argument "install" hinzufügen.

Getestet wurde das Spiel auf Ubuntu und Debian mit QT Version 5.
