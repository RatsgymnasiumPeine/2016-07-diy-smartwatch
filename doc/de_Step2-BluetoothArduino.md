## Schritt 2 - Verbindung zwischen Arduino und Bluetooth ##

Wenn nun alle Komponenten beisammen sind kann der Bau der eigentlichen Smartwatch beginnen. Dazu beginnen wir bei der Kernkomponente der Uhr: Dem Arduino und dem Bluetooth Modul.
Zunächst beklebt man die Unterseite des Arduinos mit Kaptonband o.ä. um eine ungewollte elektrische Verbindung zwischen Arduino und Bluetooth Modul zu verhindern. Das Bluetooth Modul kann nun wie im Foto gezeigt auf den Arduino befestigt werden (doppelseitiges Klebeband, ineinandergewickeltes Tesa o.ä.). Wichtig ist dabei die genaue Positionierung des Moduls. Die Antennenseite befindet sich gegenüber den Anschlüssen für die serielle Schnittstelle zum Programmer (RX, TX, GND, VCC, CTS, RST). Das Modul wird mit der Antenne Bündig an der Kante des Arduinos geklebt. Die andere Ausrichtung ist Mittig gehalten.


Nun kommt der schwierige Teil: Das Anlöten der Leitungen zwischen Modul und Arduino. Am besten eignen sich dafür Rune Trough-Hole Beinchen von Widerständen/Dioden/LEDs/etc. Diese steckt man durch den Pin des Arduinos und verlötet ihn direkt. Danach kann das Drahtbeinchen an den Pin des Moduls gebogen und darauf verlötet werden. WICHTIG: Die Drahtbeinchen und das Modul dürfen unter keinen Umständen unter einer mechanischen Belastung gestellt werden (Dabei können die Lötpins an dem Modul abreißen).

Danach folgt die Montage der rechtwinkligen Headerleiste am Arduino. Zu beachten ist hierbei, dass der Header auf der Oberseite festgelötet wird bzw. auf der Seite mit dem Modul rausguckt.
