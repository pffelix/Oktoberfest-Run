Wiesn-Run (Oktoberfest-Run) 

Wiesn-Run is a C++ Game that allows the user to experience the Oktoberfest on his own PC.

Hinweise zum Kompilieren unter Linux
+Unter Linux muss zum Kompilieren die Audiobibliothek PortAudio vorhanden sein. Genau genommen sollte es die Version 19+svn20111121-1 sein. Unter Debian/Ubuntu genügt es, das Paket portaudio19-dev zu installieren. Dann sollte sich unter dem Pfad /usr/lib/x86_64-linux-gnu die Datei libportaudiocpp.so befinden.
+Im Release-Mode gelten striktere Laufzeitregeln als im Debug-Mode. Durch einen Bug in der Linux-Version der portaudio-Bibliothek kann das Spiel unter einigen Linux-Varianten nicht ausgeführt werden, wenn es im Release-Modus kompiliert wurde. In diesem Fall muss das Spiel im Debug-Modus kompiliert werden.
 -> In der audiocontrol.cpp werden Meldungen vor und nach dem Aufruf der Bibliothektsfunktion Pa_Initialize() ausgegeben. Im Debug-Modus werden die Meldungen von und nach dem Aufruf ausgegeben und das Spiel gestartet. Im Release-Modus wird auf einigen Systemen nur die Meldung vor Pa_Initialize() ausgegeben, danach stürzt das Spiel ab.

Da die verwendeten Audio-Dateien zum Programmstart in den build-Ordner kopiert werden müssen, bedarf es einer kleinen Änderung des build-Schritts "Make". Bitte im QTCreator beim build-Schritt "Make" das Kommandozeilenargument "install" hinzufügen.

Getestet wurde das Spiel auf folgenden Umgebungen:
 - Ubuntu mit QT Version 5.2.1
 - Debian mit QT Version 5.3.2
 - Windows mit QT Version 5.4.1
