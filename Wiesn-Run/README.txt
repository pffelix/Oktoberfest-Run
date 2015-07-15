Wiesn-Run Readme

Hinweise zum Kompilieren unter Linux
+Unter Linux muss zum Kompilieren die Audiobibliothek PortAudio vorhanden sein. Genau genommen sollte es die Version 19+svn20111121-1 sein. Unter Debian/Ubuntu genügt es, das Paket portaudio19-dev zu installieren. Dann sollte sich unter dem Pfad /usr/lib/x86_64-linux-gnu die Datei libportaudiocpp.so befinden.
+Im Release-Mode gelten striktere Laufzeitregeln als im Debug-Mode. Durch einen Bug in der Linux-Version der portaudio-Bibliothek kann das Spiel unter einigen Linux-Varianten nicht ausgeführt werden, wenn es im Release-Modus kompiliert wurde. In diesem Fall muss das Spiel im Debug-Modus kompiliert werden.

Da die verwendeten Audio-Dateien zum Programmstart in den build-Ordner kopiert werden müssen, bedarf es einer kleinen Änderung des build-Schritts "Make". Bitte im QTCreator beim build-Schritt "Make" das Kommandozeilenargument "install" hinzufügen.

Getestet wurde das Spiel auf Ubuntu und Debian mit QT Version 5.4.1
