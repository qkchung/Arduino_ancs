Arduino_ancs
============

Arduino Source for Ancs Dongle 

This sample code use SoftwareSerial Library <br>
using pin10 as Rx , pin11 as Tx


Steps :<br>
1. Connect Arduino pin10 with dongle 5V Tx, Arduino pin11 with dongle 5V Rx <br>
2. On Iphone , go to bluetooth settings, remove any previous pairing with Ancs Dongle<br>
3. Connect Arduino 5V output to Dongle 5V input<br>
4. On Iphone Bluetooth Settings, pair up with "Ancs Dongle" device<br>
5. Enter "111111" as password<br>
6. open provided arduino source "arduino_ancs.ino" and upload to arduio<br>
7. open serial monitor<br>
8. Serial monitor will show status<br>
9. For problem connecting, power off arduino, redo 2 to 5<br>
10. Wait for incoming message or call <br>


